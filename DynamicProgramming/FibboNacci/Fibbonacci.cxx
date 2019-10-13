
//find Fibbonaci
#include <vector>
#include <iostream>

#define ENDL std::cout << "\n";

std::vector<int> Fibbonacci(int n)
{
  std::vector<int> fibbSeries(n);
  fibbSeries[0] = 0;
  fibbSeries[1] = 1;

  for (int i = 2; i < n; i++)
  {
    fibbSeries[i] = fibbSeries[i - 1] + fibbSeries[i - 2];
  }

  return fibbSeries;
}

int Fibbonacci_dp(int n, std::vector<int> arr)
{
  if (n == 0)
  {
    return 0;
  }
  if (n == 1)
  {
    return 1;
  }

  arr[n] = Fibbonacci_dp(n - 1, arr) + Fibbonacci_dp(n - 2, arr);
  return arr[n];
}

int main()
{
  auto vector = Fibbonacci(5);
  for (auto &item : vector)
  {
    std::cout << item << " -- ";
  }
  ENDL

      Fibbonacci_dp(5, vector);

  for (auto &item : vector)
  {
    std::cout << item << " -- ";
  }

  ENDL
}
