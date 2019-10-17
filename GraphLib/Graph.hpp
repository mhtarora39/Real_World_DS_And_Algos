
#include <iostream>
#include <memory>
#include <vector>
#include <atomic>
#include <map>

namespace AtomicOps
{
int GetID()
{
  static std::atomic<int> id(0);
  return id++;
}

} // namespace AtomicOps

template <typename T>
class Graph;

template <typename T>
class GraphFactory
{

public:
  GraphFactory()
  {
  }

  ~GraphFactory()
  {
    mGraphDataMap.clear();
    mCurrentPath.clear();
    mTotalPath.clear();
  }

  //ID is provided by GETID fuction
  Graph<T> &GetObject(T &data, int id = -1, bool addToPath = false)
  {
    return *GetObjectPTR(data, id, addToPath);
  }

  Graph<T> &GetObject(T &&data, int id = -1, bool addToPath = false)
  {
    //no need to move as we are creating copy of it

    return *GetObjectPTR(data, id, addToPath);
  }

  //*************************************

  //graph like (src node ---W--- dst-node)

  void BuildGraph(T &&src, int weight, T &&dest, int srcID = -1, int dstID = -1, bool srcAddToPath = false, bool dstAddToPath = false)
  {
    BuildGraphHelper(src, weight, dest, srcID, dstID, srcAddToPath, dstAddToPath);
  }

  void BuildGraph(T &src, int weight, T &dest, int srcID = -1, int dstID = -1, bool srcAddToPath = false, bool dstAddToPath = false)
  {
    BuildGraphHelper(src, weight, dest, srcID, dstID, srcAddToPath, dstAddToPath);
  }

  std::vector<std::shared_ptr<Graph<T>>> GetAllNodes()
  {
    return mTotalPath;
  }

  std::vector<std::shared_ptr<Graph<T>>> GetCurrentPath()
  {
    return mCurrentPath;
  }

  void ClearCurrentPath()
  {
    mCurrentPath.clear();
  }

  void AddToCurrentPath(Graph<T> &obj, int id = -1)
  {
    auto pathPTR = GetObjectPTR(obj.mData, id);
    mCurrentPath.push_back(pathPTR);
  }

private:
  std::shared_ptr<Graph<T>> &GetObjectPTR(T &data, int id, bool addToPath)
  {
    auto pair = std::make_pair<T &, int &>(data, id);
    if (mGraphDataMap.find(pair) == mGraphDataMap.end())
    {

      mGraphDataMap[pair] = std::make_shared<Graph<T>>(Graph<T>(std::forward<T>(data)));
      mGraphDataMap[pair]->mID = id;
      mTotalPath.push_back(mGraphDataMap[pair]);
      if (addToPath)
      {
        mCurrentPath.push_back(mGraphDataMap[pair]);
      }
    }

    return (mGraphDataMap[pair]);
  }

  void BuildGraphHelper(T &src, int weight, T &dest, int srcID = -1, int dstID = -1, bool srcAddToPath = false, bool dstAddToPath = false)
  {
    auto &srcNode = (GetObject(src, srcID, srcAddToPath));
    auto &dstNode = (GetObject(dest, dstID, dstAddToPath));
    srcNode.AddEdge(dstNode, weight);
  }
  std::map<std::pair<T, int>, std::shared_ptr<Graph<T>>> mGraphDataMap;
  std::vector<std::shared_ptr<Graph<T>>> mCurrentPath;
  std::vector<std::shared_ptr<Graph<T>>> mTotalPath;
};

template <typename T>
class GraphAlgo
{

  typedef std::shared_ptr<Graph<T>> GraphPTR;

public:
  GraphAlgo(std::vector<GraphPTR> &path) : mPath(path)
  {
  }

  void Clear()
  {
    for (auto item : mPath)
    {
      item->ClearMeta();
    }
  }

  const GraphPTR findMin()
  {

    int dist = INT32_MAX;
    GraphPTR minNode;
    int index = -1;
    int last_index = 0;
    for (auto &node : mPath)
    {
      if (dist > node->mDist && !node->mVisited)
      {
        dist = node->mDist;
        minNode = node;
      }
    }

    //nodes[last_index].mVisited= true;
    minNode->mVisited = true;
    return minNode;
  }

  //This node consider to be shortest node
  std::vector<Graph<T>>
  DijkstraShortestPath()
  {

    std::vector<GraphPTR> tmp;
    std::vector<Graph<T>> pathToParent;
    if (mPath.empty())
    {
      pathToParent;
    }

    //we should be knowing in advance which nodes are going to participate
    //mPath variable should be static varable
    mPath[0]->mDist = 0;
    // or we can find all pair shortest path
    for (int j = 0; j < mPath.size(); j++)
    {
      auto minNode = findMin();

      int size = minNode->mEdges.size();

      for (int i = 0; i < size; i++)
      {

        if (minNode->mEdges[i].weight < 0)
        {
          return pathToParent;
        }

        if (minNode->mEdges[i].edge->mDist > minNode->mDist + minNode->mEdges[i].weight)
        {

          minNode->mEdges[i].edge->mDist = minNode->mDist + minNode->mEdges[i].weight;
          //std::swap(minNode->mEdges[i].edge->mParent, nullptr);
          minNode->mEdges[i].edge->mParent = minNode;

          // Front
        }
      }
    }

    GraphPTR graph = mPath[mPath.size() - 1];

    while (graph)
    {
      pathToParent.push_back(*graph);
      graph = graph->mParent;
    }

    return pathToParent;
  }

private:
  std::vector<GraphPTR> mPath;
};

template <typename T>
class Graph;

template <typename T>
void no_op(Graph<T> *)
{
}

template <typename T>
class Graph
{
  typedef std::shared_ptr<Graph<T>> GraphPTR;

public:
  T &GetData()
  {
    return mData;
  }

  ~Graph()
  {
    mPath.clear();
  }

  void AddEdge(Graph<T> &edge, int weight = 1)
  {

    // Don't copy we need ref
    // As client function is going
    // to manage memory of obj we shouldn't be
    // deleting obj;
    // TODO : use instead raw pointer here

    GraphPTR oPtr(&edge, no_op<T>);
    GraphPTR iPtr(this, no_op<T>);
    mEdges.push_back(GraphMeta(oPtr, iPtr, weight));
  }

  void SetPath(std::vector<GraphPTR> &gPtr)
  {
    mPath = gPtr;
  }

  void ClearPath()
  {
    mPath.clear();
  }

  void AddToPath(Graph<T> &edge)
  {
    //TODO : use insted raw pointer here
    GraphPTR ptr(&edge, no_op<T>);
    mPath.push_back(ptr);
  }

  Graph(const Graph<T> &&copy) : mID(copy.mID),
                                 mData(std::move(copy.mData)),
                                 mEdges(std::move(copy.mEdges)),
                                 mDist(std::move(copy.mDist)),
                                 mVisited(copy.mVisited)

  {
    //   mParent(nullptr);
  }

  Graph(const Graph<T> &copy) : mID(copy.mID),
                                mData(copy.mData),
                                mEdges(copy.mEdges),
                                mDist(copy.mDist),
                                mVisited(copy.mVisited)

  {
    //   mParent(nullptr);
  }

  Graph<T> &operator=(const Graph<T> &&copy)
  {
    mID = copy.mID;
    mData = std::move(copy.mData);
    mEdges = std::move(copy.mEdges);
    mDist = std::move(copy.mDist);
    mVisited = copy.mVisited;
    mParent = std::move(mParent);
  }

  Graph<T> &operator=(const Graph<T> &copy)
  {
    mID = copy.mID;
    mData = (copy.mData);
    mEdges = (copy.mEdges);
    mDist = (copy.mDist);
    mVisited = copy.mVisited;
    mParent = (mParent);
  }

private:
  Graph()
  {
  }
  void clearMeta()
  {

    mParent = nullptr;
    mVisited = false;
    mDist = INT32_MAX;
  }

  Graph(T &data, int id = -1) : mData(data)
  {
    mDist = INT32_MAX;
    mVisited = false;
    mID = id;
  }

  Graph(T &&data, int id = -1) : mData(std::move(data))
  {
    mDist = INT32_MAX;
    mVisited = false;
    mID = id;
  }

  struct GraphMeta
  {
    GraphMeta(GraphPTR ptr, GraphPTR input, int wt) : edge(ptr), weight(wt), inputs(input)
    {
    }

    GraphMeta(const GraphMeta &other) : weight(other.weight),
                                        edge(other.edge),
                                        inputs(other.inputs)
    {
    }

    GraphMeta &operator=(const GraphMeta &other)
    {
      //TODO : change Edge name
      //Output
      weight = other.weight;
      edge = other.edge;
    }

    int weight;
    Graph::GraphPTR edge;
    Graph::GraphPTR inputs;
  };

private:
  friend class GraphFactory<T>;
  friend class GraphAlgo<T>;
  T mData;
  int mDist;
  GraphPTR mParent;
  bool mVisited;
  std::vector<GraphMeta> mEdges;
  std::vector<GraphPTR> mPath;
  int mID;
};

//Take Vector of two type
// And return type based on
template <typename T>
class INodeOPS
{
public:
  virtual ~INodeOPS();
  virtual T eval() = 0;
};

template <typename T>
class BinaryOps : public INodeOPS<T>
{
  INodeOPS<T> *rhs, lhs;
  enum Type
  {
    ADD,
    SUB
  } type;

public:
  BinaryOps(Type typ) : type(typ)
  {
  }

  void
      T
      eval()
  {
    if (type == ADD)
    {
      return lhs->eval() + rhs->eval();
    }
    else if (type == SUB)
    {
      return lhs->eval() - rhs->eval();
    }
  }
};

class Int32 : public INodeOPS<int>
{
public:
  Int32(int data) : mData(data)
  {
  }

  int32_t eval()
  {
    return mData;
  }

private:
  int mData;
};