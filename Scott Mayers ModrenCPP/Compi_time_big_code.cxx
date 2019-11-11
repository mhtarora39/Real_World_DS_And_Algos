//This is big code which has compile time dispatch
#include<type_traits>
#include <iostream>


  template<typename T>
  struct is_array:std::false_type{};

  template<typename T> 
  struct is_array<T[]>:std::true_type{};

  template<typename T>
  constexpr bool is_array_v = is_array<T>::value;

int main() {

  static_assert(is_array_v<int> == false);
  static_assert(is_array_v<int[]>);
  std::cout << is_array_v<int[]> << std::endl;
  int a;
  std::cin >> a;
}