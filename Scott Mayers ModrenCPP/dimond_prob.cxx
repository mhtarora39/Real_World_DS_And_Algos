#include<iostream>


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

int main() {
  DerivedAB a;
}