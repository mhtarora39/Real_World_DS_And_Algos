#include<iostream>
#include<vector>

struct Base {
  Base() {
    std::cout << "Base is called " << std::endl;
  }
};

struct DerivedA : virtual Base {
  DerivedA() {
    std::cout << " Derived A is called " << std::endl; 
  } 
};

struct DerivedB : virtual Base {
  DerivedB() {
    std::cout << " Derived B is Called " << std::endl;
  }
};

struct DerivedAB : DerivedA ,  DerivedB {
  DerivedAB() {
    std::cout << " Derived A _ B is called " << std::endl;
  }
};

//Array reserve

int  function(int i) {
  if(i == 0) {
    throw "This is non std exception " ;
  }
  return 0;
}

int  function_1() {
  try {
    return function(0);
  }
  catch( ... ) {
    return 100;
  }
  return 200;
}

int main() {

  auto i = function_1();
  std::cout << i <<std::endl;
  std::vector<int> a{1,2,3};
  std::vector<int> b;
  b.resize(a.size());
  std::cout << b.size() <<std::endl;
  for(int i = 0; i < a.size() ; i++) {
    b[i] = a[i];
  }
   for(int i = 0; i < a.size() ; i++) { 
   std::cout << b[i] <<" ----- " <<std::endl;
   }
  //DerivedAB a;
}