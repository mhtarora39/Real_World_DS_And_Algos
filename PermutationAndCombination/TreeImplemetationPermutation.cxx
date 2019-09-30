#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <atomic>

int GetId()
{
  static std::atomic<int> id;
  return id++;
}

template <typename T>
class Tree
{
private:
  T mData;
  int id;
  int size;
  using Dtype = std::vector<T>;
  Dtype all;
  std::vector<std::shared_ptr<Tree<T>>> edge;

  void BuildTreeHelper(Tree<T> &root, int size, std::vector<Tree<T>> &unused, std::vector<Tree<T>> &used)
  {
  }

public:
  Tree(const Dtype &data) : all(mData)
  {
  }

  Tree(T data) : mData(data)
  {
    id = GetId();
  }
  Tree(const Tree<T> &other)
  {
    id = other.id;
    mData = other.mData;
  }

  friend std::ostream &operator<<(std::ostream &out, const Tree<T> &item)
  {
    std::cout << "Element : " << item.mData << std::endl;
    for (auto it : item.edge)
    {
      std::cout << "Edge : " << it->mData << std::endl;
    }
  }

  void BuildTree()
  {
    std::vector<Tree<T>> usedArray;
    std::vector<Tree<T>> used;

    for (auto &item : all)
    {
      std::shared_ptr<Tree<T>> ptr(new Tree<T>(item));
      usedArray.emplace_back(*ptr);
      edge.push_back(std::move(ptr));
    }
    BuildTreeHelper(*this, all.size(), used, usedArray);
  }

  std::vector<Dtype> GetResults()
  {
  }
};

int main()
{
  Tree<int> test{{1, 2, 3, 4}};
  test.BuildTree();
  std::cout << test << std::endl;
}