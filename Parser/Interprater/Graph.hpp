#include <iostream>
#include <vector>
#include <memory>
#include <atomic>

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

class EdgeInfo
{
  EdgeInfo(Graph<T> &eg, const int &wt, std::shared_ptr<Ikernal<T>> &krnal) : mEdges(&eg),
                                                                              mWeight(wt),
                                                                              mObj(kernal)
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
      mEdges.push_back(item);
    }
  }

  void compute()
  {
  }

  void AddEdge(const Graph &edge, int weight, std::shared_ptr<Ikernal<T>> kernal)
  {
  }

private:
  int mID;
  std::vector<EdgeInfo<T>> mEdges;
  T mData;
};
