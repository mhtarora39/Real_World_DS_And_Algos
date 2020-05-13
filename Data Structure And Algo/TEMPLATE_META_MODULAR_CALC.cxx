#include <iostream>

//Calculate Mode like m^n % any number  using template

//power (a(n/2))2

template<int N>
int pow(int a) {
  int num;
  if(N%2 == 0) {
    num = pow<N/2>(a) * pow<N/2>(a);
  }
  else {
    num = pow<N-1>(a) * pow<1>(a);
  }
  return num;
}

template<> pow<2>(int a) {
  return a*a;
}

template<> pow<1>(int a) {
  return a;
}

int main() {
  // while(true) {
  //   int base,expo;
  //   std::cout << "enter base : ";
  //   std::cin >> base;
  //   std::cout << "enter exponent : ";
  //std::cin >> expo;
  std:: cout << "Sol : " << pow<10>(2);
  int x;
  std::cin >> x;
}