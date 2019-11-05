//Given an integer array with all positive numbers and no duplicates,
//find the number of possible combinations that add up to a positive 
//integer target.

#include <vector>
#include <iostream>

int main() {
  
  std::vector<int> m_ivector {1,2,3};
  int m_trget_sum = 4;
  std::vector<int> dp;
  dp.assign(m_trget_sum+1,0);
  dp[0] = 1;
  //
  // dp[i] += dp[i-1] + dp[i -2] + dp[i - 3]
  //

  for(int i = 1 ; i < dp.size() ; i++ ) {
    for(auto item : m_ivector) {
      if(i >= item)
      dp[i] += dp[i - item];
    }
  }
  
  std::cout << "dp[4] = " << dp[4] << std::endl;



}