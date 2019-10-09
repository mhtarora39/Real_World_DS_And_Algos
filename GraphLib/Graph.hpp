//Debugging

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

//Should change every thing with row pointers as we are not
//going to delete not by overselves

template <typename T>
class Graph;

template <typename T>
void no_op(Graph<T> *ptr)
{
  // for locally created obejects;
}

template <typename T>
class GraphFectory
{

public:
  GraphFectory()
  {
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

  std::vector<std::shared_ptr<Graph<T>>> &GetAllNodes()
  {
    return mCurrentPath; //Client can manupulate path
  }

private:
  std::shared_ptr<Graph<T>> GetObjectPTR(T &data, int id, bool addToPath)
  {
    auto pair = std::make_pair<T &, int &>(data, id);
    if (mGraphDataMap.find(pair) == mGraphDataMap.end())
    {
      //creating copy of data as life of object should be manged by
      //this class. It will manage both lvalue as well as rvalue

      mGraphDataMap[pair] = std::make_shared<Graph<T>>(Graph<T>(data));
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
    auto &srcNode = (GetObject(src, srcID,srcAddToPath));
    auto &dstNode = (GetObject(dest, dstID,dstAddToPath));
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
  GraphAlgo(std::vector<std::shared_ptr<Graph<T>>> &path) : mPath(path)
  {
  }

  bool isDirty()
  {
    return mDirty;
  }

  void Clear()
  {
    mDirty = false;
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
    if (mPath.empty())
    {
      return mPath;
    }

    mDirty = true;

    std::vector<GraphPTR> tmp;
    //we should be knowing in advance which nodes are going to participte
    //mPath variable should be static varable
    mPath[0]->mDist = 0;
    // or we can find all pair shortest path
    for (int j = 0; j < mPath.size(); j++)
    {
      auto minNode = findMin();

      int size = minNode->mEdges.size();

      for (int i = 0; i < size; i++)
      {

        if (minNode->mEdges[i].edge->mDist > minNode->mDist + minNode->mEdges[i].weight)
        {

          minNode->mEdges[i].edge->mDist = minNode->mDist + minNode->mEdges[i].weight;
          //std::swap(minNode->mEdges[i].edge->mParent, nullptr);
          minNode->mEdges[i].edge->mParent = minNode;

          // Front
        }
      }
    }

    std::vector<Graph<T>> pathToParent;
    GraphPTR graph = mPath[mPath.size() - 1];

    while (graph)
    {
      pathToParent.push_back(*graph);
      graph = graph->mParent;
    }

    // if (graph->mID == mPath[0]->mID)
    // {
    //   pathToParent.push_back(*graph);
    // }

    return pathToParent;
  }

private:
  bool mDirty;
};
//template <typename T>

template <typename T>
class Graph
{
  typedef std::shared_ptr<Graph<T>> GraphPTR;

public:
  T &GetData()
  {
    return mData;
  }

  void AddEdge(Graph<T> &edge, int weight = 1)
  {
    //Don't copy
    GraphPTR ptr(&edge, no_op<T>);
    mEdges.push_back(GraphMeta(ptr, weight));
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
    //TODO replace by raw ptr as memory going to managed by calling
    //function
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

  Graph<T> &operator=(const Graph<T> &&copy)
  {
    mID = copy.mID;
    mData = std::move(copy.mData);
    mEdges = std::move(copy.mEdges);
    mDist = std::move(copy.mDist);
    mVisited = copy.mVisited;
    mParent = std::move(mParent);
  }

private:
  Graph()
  {
  }
  void clearMeta()
  {

    mParent = nullptr;
    mVisited = false;
    mDist = INT16_MAX;
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
    GraphMeta(GraphPTR ptr, int wt) : edge(ptr), weight(wt)
    {
    }

    GraphMeta(const GraphMeta &other) : weight(other.weight),
                                        edge(other.edge)
    {
    }

    GraphMeta &operator=(const GraphMeta &other)
    {
      weight = other.weight;
      edge = other.edge;
    }

    int weight;
    Graph::GraphPTR edge;
  };

public:
  friend class GraphFectory<T>;
  friend class GraphAlgo<T>;
  T mData;
  int mDist;
  GraphPTR mParent;
  bool mVisited;
  std::vector<GraphMeta> mEdges;
  std::vector<GraphPTR> mPath;
  int mID;
};
