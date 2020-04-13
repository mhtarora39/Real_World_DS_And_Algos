//This is big code which has compile time dispatch
#include<type_traits>
#include <iostream>
#include <map>
#include<vector>

enum class EDataType {
  eVector,
  eMap,
  eOther
};

template<typename T>
struct get_type {
  static constexpr EDataType value = EDataType::eOther;
};

template<typename key, typename val>
struct get_type<std::map<key,val>> {
  static constexpr EDataType value = EDataType::eMap;
};

template<typename T>
struct get_type<std::vector<T>> {
  static constexpr EDataType value = EDataType::eVector;
};

template<typename T>
EDataType GetType(T& ty) {
  return get_type<T>::value;
}




  // template<typename T>
  // struct is_array:std::false_type{};

  // template<typename T> 
  // struct is_array<T[]>:std::true_type{};

  // template<typename T>
  // constexpr bool is_array_v = is_array<T>::value;

int main() {
   
  std::map<int,int> b;
  std::cout << static_cast<int>(get_type<std::vector<int>>::value) << std::endl;
  
  std::cout << static_cast<int>(get_type<std::map<int,int>>::value) << std::endl;

  std::cout << static_cast<int>(GetType(b)) <<std::endl; 
  // static_assert(is_array_v<int> == false);
  // static_assert(is_array_v<int[]>);
  // std::cout << is_array_v<int[]> << std::endl;
  int a;
  std::cin >> a;
}