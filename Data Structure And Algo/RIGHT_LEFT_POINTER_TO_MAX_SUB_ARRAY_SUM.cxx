#include <iostream>
#include <vector>

typedef std::vector<int>::iterator pointer;

std::vector<pointer> get_left_right_pointer_max_sum_subarray(std::vector<int>& array) {

  pointer lft , rht, tmp;
  lft = array.begin();
  tmp  = lft;
  long sum = 0;
  long ans = array[0];
  for(auto iter = array.begin(); iter < array.end(); iter++) {
    sum = sum + *iter;
    if(sum > ans) {
      ans = sum;
      rht = iter;
      lft = tmp;
    }
    if(sum < 0) {
      sum = 0;
      tmp = iter + 1;
    }
  }
  return {lft , rht};
}

int main() {
  std::vector<int> array {-2,-1,3,3,4,-5 ,2 ,1,-10};
  auto ptrs = get_left_right_pointer_max_sum_subarray(array);
  std::cout << " -2,-1,3,3,4,-5 ,2 ,1,-10" << std::endl;
  std::cout << "left : " << *ptrs[0] << std::endl;
  std::cout << "right : " << *ptrs[1] << std::endl;
  int a;
  std::cin >> a;
}