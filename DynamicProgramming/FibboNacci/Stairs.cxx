// You are climbing a stair case.It takes
// n steps to reach to the top.
// Each time you can either climb 1 or
// 2 steps.In how many distinct ways can you climb to the top
// ?

#include <iostream>
#include <vector>
#define ONE 1
#define TWO 2

//Time  Complexity => 2pow(n)
//Space complexity => 2pow(n)

int numberOfSteps(int dest)
{
  if (dest <= 0)
  {
    return 0;
  }
  if (dest == TWO)
  {
    return 2;
  }

  if (dest == ONE)
  {
    return 1;
  }

  auto curr = numberOfSteps(dest - ONE) + numberOfSteps(dest - TWO);
  return curr;
};

int countWaysUtil(int n, int m)
{
  int res[n];
  res[0] = 1;
  res[1] = 1;
  for (int i = 2; i < n; i++)
  {
    res[i] = 0;
    for (int j = 1; j <= m && j <= i; j++)
      res[i] += res[i - j];
  }
  return res[n - 1];
}

// Returns number of ways to reach s'th stair
int countWays(int s, int m)
{
  return countWaysUtil(s + 1, m);
}

int numberOfSteps_1(int dest)
{
  auto first = 1;
  int second = first;
  if (TWO <= dest)
  {
    second = 2;
  }
  int tmp = second;
  for (auto i = TWO + 1; i <= dest; i++)
  {
    tmp = first + second;
    first = second;
    second = tmp;
  }

  return tmp;
}

int main()
{
  std::cout << numberOfSteps_1(4) << std::endl;
  return 0;
}
