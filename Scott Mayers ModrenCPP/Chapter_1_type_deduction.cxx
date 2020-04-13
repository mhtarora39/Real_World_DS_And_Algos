/*
 * This file use for understanding c plus plus
 *
 */



#include<iostream>
#include<vector>
#include <typeinfo> //use for typeid


//Decltype


//Type Deduction
/*
the specification for std::type_info::name mandates that the type be treated
as if it had been passed to a template function as a by-value parameter.
*/


template<typename T>
void f(const T& ele) {
    std::cout << "Type : " << typeid(T).name() << std::endl;
    std::cout << "Type ele : " << typeid(ele).name() << std::endl;
}


int main() {
  auto ele = std::vector<int>(2);
  f(&ele);
  return 0;
}



