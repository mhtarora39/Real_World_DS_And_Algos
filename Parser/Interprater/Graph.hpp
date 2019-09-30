#include <iostream>
#include <vector>
#include <memory>
#include <atomic>

template <typename T>
class Graph;

int GetID()
{
  static std::atomic<int> id(0);
  return id++;
}

template <typename T>

class Ikernal
{

public:
  virtual ~Ikernal(){};

  Ikernal()
  {
  }

  virtual T &compute(const Graph<T> &lhs, const Graph<T> &rhs) = 0;
};
template <typename T>
class NoOp : Ikernal<T>
{
public:
  NoOp()
  {
  }
  ~NoOp()
  {
  }

  const Graph<T> &compute(const Graph<T> &lhs, const Graph<T> &rhs)
  {
    Graph<T> dummy(lhs);
    return dummy;
  }
};

template <typename T>

class EdgeInfo
{
public:
  EdgeInfo(Graph<T> &eg, const int &wt, std::shared_ptr<Ikernal<T>> &kernal) : mEdge(&eg),
                                                                               mWeight(wt),
                                                                               mObj(kernal)
  {
  }

  Graph<T> &GetInfo()
  {
    return *mEdge;
  }

  EdgeInfo(EdgeInfo &copy) : mWeight(copy.mWeight),
                             mObj(copy.mObj),
                             mEdge(copy.mEdge)
  {
  }

private:
  int mWeight;
  std::shared_ptr<Ikernal<T>> mObj;
  std::shared_ptr<Graph<T>> mEdge;
};

template <typename T>
class Graph
{
public:
  Graph(const T &data) : mID(GetID()),
                         mData(data)
  {
  }

  Graph(const Graph &other)
  {
    mData = other.data;
    //mID   = GetID();
    mID = other.mID;
    mEdges.clear();
    //Creating Deep Copy
    for (auto &item : other.mEdges)
    {
      // ToDo safe copy...
      mEdges.push_back(item);
    }
  }

  void compute()
  {
  }

  void DFSTest(const Graph &from)
  {
    if (from.mEdges.size() > 0)
    {

      for (auto item : mEdges)
      {
        std::cout << "Data : " << item.GetInfo().mData << std::endl;
        DFSTest(item.GetInfo());
      }
    }
  }

  void AddEdge(Graph &edge, int weight = 1, std::shared_ptr<Ikernal<T>> kernal = std::make_shared<Ikernal<T>>(new NoOp<T>()))
  {
    mEdges.push_back(EdgeInfo<T>(edge, weight, kernal));
  }

private:
  int mID;
  std::vector<EdgeInfo<T>> mEdges;
  T mData;
};
