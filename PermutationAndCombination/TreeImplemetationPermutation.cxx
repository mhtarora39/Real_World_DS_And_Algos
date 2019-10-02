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
class Tree;
//template <typename T>
void CustomDltr(Tree<int> *ptr)
{
  //no-op as object is managed locally
}

template <typename T>
class Tree
{
private:
  T mData;
  int id;
  int size;
  bool mBuilded;
  using Dtype = std::vector<T>;
  Dtype all;
  std::vector<std::shared_ptr<Tree<T>>> edge;
  void AddEdgeCopy()
  {
  }

  void BuildTreeHelper(Tree<T> &root, std::vector<std::shared_ptr<Tree<T>>> &array)
  {
    std::vector<std::shared_ptr<Tree<T>>> tmp;
    mBuilded = true;

    for (int i = 0; i < array.size(); i++)
    {
      // auto r = root;
      tmp.clear();
      for (int j = 0; j < array.size(); j++)
      {

        if (array[j]->mData != array[i]->mData)
        {
          tmp.push_back(array[j]);
          //Get*array[i]ting new copy
          // std::cout << "( root :" << root.mData << " ) " << array[j]->mData << std::endl;
          // root.edge.push_back(std::make_shared<Tree<T>>(*array[j]));
        }
      }
      std::cout << " root data " << array[i]->mData << " ";
      std::shared_ptr<Tree<T>> r(&root, CustomDltr);
      for (int k = 0; k < array.size(); k++)
      {
        std::shared_ptr<Tree<T>> ptr(std::make_shared<Tree<T>>(*array[k]));
        r->edge.push_back(ptr);
        r.reset();
        r = ptr;
      }

      BuildTreeHelper(*array[i], tmp);
    }
  }
  Tree()
  {
    mData = -1;
  }

public:
  Tree(const Dtype &data) : all(data)
  {
  }

  Tree(T data) : mData(data)
  {
    id = GetId();
  }
  //should not be hitted
  Tree(const Tree<T> &other)
  {
    // while (true)
    // {
    //   std::cout << "Cought" << std::endl;
    // }

    id = other.id;
    mData = other.mData;
    for (auto item : other.edge)
    {
      edge.push_back(item);
    }
  }

  void AddEdge(Tree<T> &node)
  {
    //CustomDlTR ensure that object should not
    //delete by shared pointer
    // As object is going to manage localy

    std::shared_ptr<Tree<T>> ptr(&node, CustomDltr);

    //Make share will ask for copy but underlaying
    //Object needs to modified in future;

    edge.emplace_back(ptr);
  }

  friend std::ostream &operator<<(std::ostream &out, const Tree<T> &item)
  {
    out << "Element : " << item.mData << std::endl;
    for (auto it : item.edge)
    {
      out << "Edge : " << it->mData << std::endl;
    }
    return out;
  }

  void BuildTree()
  {
    Tree<T> dummy;
    mData = -1;
    std::shared_ptr<Tree<T>> dummyPtr(&dummy, CustomDltr);

    for (auto &item : all)
    {
      edge.push_back(std::make_shared<Tree<T>>(item));
    }

    BuildTreeHelper(dummy, edge);
  }

  void GetResults(Tree<T> &node, std::vector<Dtype> &res)
  {
    static std::vector<T> data;
    for (auto &item : node.edge)
    {
      data.push_back(item->mData);
      GetResults(*item, res);
    }
    //no more edges;

    res.push_back(data);
    if (data.size() > 0)
      data.pop_back();
  }
};

void Test(int &a, std::vector<int> b)
{
  if (b.size() <= 0)
  {
    return;
  }

  int z = b[b.size() - 1];

  b.pop_back();
  Test(z, b);
}
int main()
{
  Tree<int> test{{1, 2, 3}};
  test.BuildTree();
  std::cout << test << std::endl;
  int a = -1;

  std::vector<std::vector<int>> data;

  test.GetResults(test, data);

  for (int i = 0; i < data.size(); i++)
  {
    for (int j = 0; j < data[i].size(); j++)
    {
      std::cout << data[i][j];
    }
    std::cout << "\n";
  }

  Test(a, {1, 2, 3});
  std::cout << "a = " << a;
  return 0;
}