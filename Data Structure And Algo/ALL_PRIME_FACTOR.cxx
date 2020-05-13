#include <vector>
#include <iostream>
#include <cmath>       // for std::sqrt


std::vector<int> prime_factors(int number) {
  std::vector<int> factors;
  int num = std::sqrt(number);
  for(int i = 2; i <= num ;) {
    if(number % i == 0) { //
      number = number / i;
      factors.push_back(i);
    }
    else {
      i++;
    }
    if(number == 1) {
      break;
    }
  }
  if(number > 1) {
    factors.push_back(number);
  }
  return factors;
}

std::ostream& operator << (std::ostream& os, std::vector<int> vec ) {
  for(auto &num : vec) {
    os << num << " ";
  }
  os << "\n";
  return os; // Copy constructor of  ostream is inaccessible so we should returning ref
}

int main() {
  int num;
  while(true) {
    std::cout << "Enter Number : " ;
    std::cin >> num;
    auto factors = prime_factors(num);
    std::cout << " Factors : ";
    std::cout << factors;
  }

}