// You are climbing a stair case.It takes
// n steps to reach to the top.
// Each time you can either climb 1 or
// 2 steps.In how many distinct ways can you climb to the top
// ?

#include <iostream>
#include <vector>
#define ONE 1
#define TWO 7

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

//This can't be done without array 
int numberOfSteps_1(int dest)
{
  std::vector<int> stepsArray;

  auto first = 1;
  int second = first;
  if (TWO > dest)
  {
    return 1;
  }
  else if (dest == TWO) {
    return 2;
  }

  stepsArray.assign(TWO-1,1);
  stepsArray.push_back(2);
  second = TWO-1;
  
  first  = 0;
  for (auto i = TWO ; i < dest; i++)
  {
    
    int tmp = stepsArray[first] +stepsArray[second];
    //4  =  //3   //2
    // 6
    stepsArray.push_back(tmp);
    first++;
    second++;
  }

  return stepsArray.back();
}

int main()
{
  std::cout << " Recursive " <<numberOfSteps(10) << std::endl;
   std::cout <<" Iter "  <<numberOfSteps_1(10) << std::endl;
  return 0;
}


