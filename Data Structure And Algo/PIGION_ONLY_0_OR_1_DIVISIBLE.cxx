#include <iostream>
#include <map>

int generate_once(int n) {
  return n*10 + 1;
}


/*
Return the number which is made up of only 1 or 0 and divisible by given number
*/

int generate_number(int n) {
  std::map<int,int> num_mod_rlsp;
  //pegion principle says that atleast 2
  //number have same reminder in the range 2 to n -1
  //if two number have same reminder there difference will
  //is perfect divisible. SO if the number made up of
  //only 1s then there difference is always made up of
  // 1 and 0
  int i = 1;
  for (;i <= n;) {
    int reminder = i%n;
    if(reminder == 0) {
      return i;
    }
    num_mod_rlsp[reminder] = i;
    i = generate_once(i);
  }
  for(;n <= i;) {
    //early exit as number only made up of 1s
    int reminder = i%n;
    if(reminder == 0) {
      return i;
    }

    if(num_mod_rlsp.count(reminder) > 0) {
       return i - num_mod_rlsp[reminder];
    }
    else
    {
      num_mod_rlsp[reminder] = i;
    }

    i = generate_once(i);
  }
  return -1;
}


int main() {
  int i = 0;
  while(true) {
    std::cout << " Enter number \n";
    std::cin >> i;
    std::cout << "Result : " << generate_number(i) << std::endl;
  }
}

