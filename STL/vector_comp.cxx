#include<vector>
#include<iostream>
#include<algorithm>
#include <memory>

using namespace std;

struct Array {
  virtual void print() {
    std::cout << "Printing .... " << std::endl;

  }

  virtual bool operator==(const Array & other) {
    std::cout << " Both are equal from bace \n";
    return true;
  }
};


struct A : Array{
  virtual bool operator==(const A & other) {
    std::cout << " Both are equal from derived \n";
    return i==other.i;
  }

  A(int a) {
    i = a;
  }
  int i;
};

int main() {
  vector<std::shared_ptr<A>> a;
  vector<std::shared_ptr<A>> b;
  a.push_back(std::make_shared<A>(1));
  a.push_back(std::make_shared<A>(2));
  a.push_back(std::make_shared<A>(3));

  b.push_back(std::make_shared<A>(1));
  b.push_back(std::make_shared<A>(2));
  b.push_back(std::make_shared<A>(3));

  auto func = [](std::shared_ptr<A>& rhs,std::shared_ptr<A> &lhs){return *rhs == *lhs;};
  std::cout <<"both are equal?  " << std::equal(a.begin(),a.end(),b.begin(),func) << std::endl ;
  std::cout <<"both are equal?  " << std::equal(a.begin(),a.end(),b.begin()) << std::endl ;


}