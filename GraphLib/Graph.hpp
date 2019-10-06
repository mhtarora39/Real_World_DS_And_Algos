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

template <typename T>
void no_op_int(Graph<T> *ptr)
{
  // for locally created obejects;
}

template <typename T>
class GraphFectory
{
  std::map<T, std::shared_ptr<Graph<T>>> mGraphDataMap;
  // std::vector<std::shared_ptr<Graph<T>>> mNodes;

public:
  GraphFectory()
  {
  }
  //Memory going to manage by Fectory
  Graph<T> &GetObject(T &data)
  {

    if (mGraphDataMap.find(data) != mGraphDataMap.end())
    {

      return *(mGraphDataMap[data].get());
    }
    else
    {
      mGraphDataMap[data] = std::make_shared<Graph<T>>(data);
      (Graph<T>::mPath).push_back(mGraphDataMap[data]);
      return *(mGraphDataMap[data].get());
    }
  }

  Graph<T> &GetObject(T &&data)
  {
    if (mGraphDataMap.find(data) != mGraphDataMap.end())
    {

      //mNodes.push_back(mGraphDataMap[data]);
      return *(mGraphDataMap[data].get());
    }
    else
    {
      mGraphDataMap[data] = std::make_shared<Graph<T>>(std::move(data));
      (Graph<T>::mPath).push_back(mGraphDataMap[data]);
      return *(mGraphDataMap[data].get());
    }
  }

  //*************************************

  //This provide easy way to add the
  //graph like (src node ---W--- dst-node)

  void BuildGraph(T &&src, int weight, T &&dest)
  {
    auto &srcNode = (GetObject(src));
    auto &dstNode = (GetObject(dest));
    srcNode.AddEdge(dstNode, weight);
  }

  void BuildGraph(T &src, int weight, T &dest)
  {
    auto srcNode = GetObject(src);
    auto dstNode = GetObject(dest);
    srcNode.AddEdge(dstNode, weight);
  }

  std::vector<std::shared_ptr<Graph<T>>> &GetAllNodes()
  {
    return Graph<T>::mPath;
  }
};

//template <typename T>

int GetID()
{
  static std::atomic<int> id(0);
  return id++;
}

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

  Graph(T &data) : mData(data)
  {
    mDist = INT32_MAX;
    mVisited = false;
    mID = GetID();
  }
  Graph(T &&data) : mData(std::move(data))
  {
    mDist = INT32_MAX;
    mVisited = false;
    mID = GetID();
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