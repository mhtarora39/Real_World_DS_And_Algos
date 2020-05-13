#include <iostream>
#include <string>


// A.	Show that the problem can be broken down into optimal sub-problems.
// B.	Apply Intuition at each step
// C.	Recursively define the value of the solution by expressing it in terms of optimal solutions for smaller sub-problems.
// D.	Compute the value of the optimal solution in bottom-up fashion.
// E.	Construct an optimal solution from the computed information

using namespace std;
string permutation(string str , int index = 0) {
  static int size = str.size();
  //abc acb cab bca
  //bac cba
  //abcd
  if(index >= size) {
    return "";
  }

  if(str.size() == 2) {
    char a =  str[0];
    str[0] = str[1];
    str[1] = a;
    return str;
  }

  if(str.size() == 1);
    return str;

  auto tmp = str[index] + permutation(str.substr(0,index)) + permutation(str.substr(index+1));
  std::cout << (tmp) << std::endl;
  return tmp;


}

int main() {
  //[A] : any substring is part of orginal string
  //i.e CAT -> ATC -> ACT -> TAC -> TCA -> CTA
  //[B] Apply intuition

  std::string str;
  str = "CAT";
  permutation(str);


}

