//Debugging

#include <iostream>
#include <memory>
#include <vector>
#include <atomic>
#include <map>

template <typename T>
class Graph;

//Should change every thing with row pointers as we are not
//going to dlete not by overselves

namespace AtomicOps
{
  int GetID()
  {
    static std::atomic<int> id(0);
    return id++;
  }

} // namespace AtomicOPS

template <typename T>
void no_op_int(Graph<T> *ptr)
{
  // for locally created obejects;
}

template <typename T>
class GraphFectory
{
  std::map<std::pair<T,int>, std::shared_ptr<Graph<T>>> mGraphDataMap;
  // std::vector<std::shared_ptr<Graph<T>>> mNodes;

  std::shared_ptr<Graph<T>> GetObjectPTR(T &data, int id)
  {
    auto pair = std::make_pair<T&,int&>(data,id);
    if (mGraphDataMap.find(pair) == mGraphDataMap.end())
    {
      mGraphDataMap[pair] = std::make_shared<Graph<T>>(data);
      mGraphDataMap[pair]->mID = id;
      (Graph<T>::mPath).push_back(mGraphDataMap[pair]);
    }

    return (mGraphDataMap[pair]);
  }

  void BuildGraphHelper(T &src, int weight, T &dest,int srcID = -1,int dstID = -1) {
    auto &srcNode = (GetObject(src,srcID));
    auto &dstNode = (GetObject(dest,dstID));
    srcNode.AddEdge(dstNode, weight);
  }

public:
  GraphFectory()
  {
  }

  //ID is provided by GETID fuction 
  Graph<T> &GetObject(T &data, int id = -1)
  {
    return *GetObjectPTR((data),id);
  }



  Graph<T> &GetObject(T &&data, int id = - 1)
  {
    return *GetObjectPTR((data),id);
  }

  //*************************************

  //This provide easy way to add the
  //graph like (src node ---W--- dst-node)

  void BuildGraph(T &&src, int weight, T &&dest, int srcID = -1,int dstID = -1)
  { 
    //Not need to move data as we are storing the copy of the data it will get 
    // distroyed

    BuildGraphHelper((src),weight,(dest),srcID,dstID);
    
  }

  void BuildGraph(T &src, int weight, T &dest, int srcID = -1,int dstID = -1)
  {
     BuildGraphHelper(src,weight,dest,srcID,dstID); 
  }

  std::vector<std::shared_ptr<Graph<T>>> &GetAllNodes()
  {
    return Graph<T>::mPath;
  }
};

//template <typename T>



template <typename T>
class Graph
{
  typedef std::shared_ptr<Graph<T>> GraphPTR;

  Graph()
  {
  }
  void clearMeta()
  {

    mParent = nullptr;
    mVisited = false;
    mDist = INT16_MAX;
  }

public:
  void SetPath(std::vector<GraphPTR> &gPtr)
  {
    mPath = gPtr;
  }

  void AddToPath(Graph<T> &edge)
  {
    GraphPTR ptr(&edge, no_op_int<T>);
    mPath.push_back(ptr);
  }
  
  T& GetData() {
    return mData;
  }
  Graph(const Graph<T> &copy)
  {
    mID = copy.mID;
    mData = copy.mData;
    mEdges.clear();
    mEdges = copy.mEdges;
    mDist = copy.mDist;
    mVisited = copy.mVisited;
    mParent = nullptr;
  }

  Graph<T> &operator=(const Graph<T> &copy)
  {
    mID = copy.mID;
    mData = copy.mData;
    mEdges.clear();
    mEdges = copy.mEdges;
    mDist = copy.mDist;
    mVisited = copy.mVisited;
  }

  Graph(T &data,int id = -1) : mData(data)
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

  void AddEdge(Graph<T> &edge, int weight = 1)
  {
    //Don't copy
    GraphPTR ptr(&edge, no_op_int<T>);
    mEdges.push_back(GraphMeta(ptr, weight));
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
  struct GraphMeta
  {
    GraphMeta(GraphPTR ptr, int wt) : edge(ptr), weight(wt)
    {
    }

    GraphMeta(const GraphMeta &other)
    {
      weight = other.weight;
      edge = other.edge;
    }

    GraphMeta &operator=(const GraphMeta &other)
    {
      weight = other.weight;
      edge = other.edge;
    }

    int weight;
    Graph::GraphPTR edge;
  };

  friend class GraphFectory<T>;

  T mData;
  int mDist;
  GraphPTR mParent;
  bool mVisited;
  std::vector<GraphMeta> mEdges;
  static std::vector<GraphPTR> mPath;
  int mID;
};

template <typename T>
std::vector<std::shared_ptr<Graph<T>>> Graph<T>::mPath = {};