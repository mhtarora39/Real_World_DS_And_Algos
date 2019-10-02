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

  void BuildTreeHelper(Tree<T> &root, std::vector<Tree<T>> &array)
  {
    for(int i = 0; i < array.size() ; i++) {
      root.add
    }
  }
  Tree() {

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
  
  void AddEdge(const Tree<T> & node) {
    edge.emplace_back(std::make_shared<Tree<T>>(node));
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
    
    Tree<T> dummy;
    BuildTreeHelper(dummy,edge);
    // for (auto : all)
    // {
    //   std::shared_ptr<Tree<T>> ptr(new Tree<T>(item));
    //   usedArray.emplace_back(*ptr);
    //   edge.push_back(std::move(ptr));
    // }

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
  return 0;
}