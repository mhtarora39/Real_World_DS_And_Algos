#include <vector>
#include <iostream>
#include <string>

int main() {
  int mode , base , expo;
  std::cout << " Enter Base : ";
  std::cin >> base;
  std::cout << "\n Enter exponential : ";
  std::cin >> expo;
  std::cout << "\n Enter Mode : ";
  std::cin >> mode;
  long long result = 1;
  long current_base = base;
  int i = expo;
  //lets take i ->-

    while(i  > 0) {

    if(i%2 == 1)  {
      result = result*current_base;
      i = i - 1;
    }
    else {
      current_base = current_base*current_base;
      result = current_base*result;
      i = i/2 - 1;
    }

    std::cout << i  << " : " << result << std::endl;

    ///any resul => result * result => i
    ///i = i*2
     // 4.8.
    ///if(i > )

  }
  std::cout << "ANS : " << result << std::endl;
  std::cin >> expo;


}