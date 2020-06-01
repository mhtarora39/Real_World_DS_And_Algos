
#include <vector>
#include <iostream>


class PartialSum {

public:
  PartialSum(std::vector<int> elements) {
    int sum = 0;
    for(auto& ele: elements) {
       sum =+ sum + ele;
       m_partial_sums.push_back(sum);
    }
  }

  int get_sum(int start,int end) {
    int size = m_partial_sums.size();
    if(start >=  size || start <  0  || end >= size || end < start) {
      throw "Invalid Min Max";
    }
    if(start == 0) {
      return m_partial_sums[end];
    }
    return m_partial_sums[end] - m_partial_sums[start -1];
  }

private:
  std::vector<int> m_partial_sums;

};

int main()
{
  PartialSum sum({1,2,3,4,22,2,1,-1});
  while(true) {
    std::cout << "Enter Start : ";
    int start;
    std::cin >> start;
    int end;
    std::cout << "\nEnter End : ";
    std::cin >> end;
    std::cout << "Result : " << sum.get_sum(start,end) << std::endl;;
  }
}