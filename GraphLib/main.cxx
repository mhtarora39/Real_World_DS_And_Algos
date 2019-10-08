#include "Graph.hpp"

class test {
  public:
  test() {

  }
  
  test(const test& t) {
    std::cout<<"Copy COTR" << std::endl;
  }

};
int main()
{
  // test a;
  // std::vector<test> b;
  // b.emplace_back(a);


  //   int tmp = 1;
  //   std::shared_ptr<int> tmpPTR(&tmp);
  //   std::shared_ptr<int> tmpPTR2 = tmpPTR;
  //  delete(&tmp);
  //   std::cout <<
  // std::shared_ptr<Test> tmpPTR(&tmp,no_op);
  // Graph<int> a(1);
  // Graph<int> b(2);
  // Graph<int> c(2);
  // Graph<int> d(4);

  // a.AddEdge(b, 2);
  // b.AddEdge(d, 4);
  // a.AddEdge(c, 4);
  // c.AddEdge(d, 1);

  // a.AddToPath(a);
  // a.AddToPath(b);
  // a.AddToPath(c);
  // a.AddToPath(d);

  GraphFectory<int> obj;
  obj.BuildGraph(1, 1, 2);
  obj.BuildGraph(2, 1, 6);
  //6  1 10,  10  1  11
  obj.BuildGraph(6, 3, 10);
  obj.BuildGraph(2, 1, 11);
  obj.BuildGraph(10, 1, 11);
   
  auto list = obj.GetAllNodes();
  obj.GetObject(1).SetPath(list);
  auto path = obj.GetObject(1).DijkstraShortestPath();
  
  for(auto item: path) {
    std::cout << item.GetData() <<std::endl;
  }
  ///auto path = a.DijkstraShortestPath();
  //int a = 0;
  //std::cin >> a;
  return 0;
}