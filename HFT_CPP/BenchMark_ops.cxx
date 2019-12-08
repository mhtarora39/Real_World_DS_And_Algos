#include <benchmark/benchmark.h>

// #define ARGS \
//   ->RangeMultiplier(2)->Range(4, 2 * 1024 * 1024 * 50)->UseRealTime()

double min(double)
{
  return 2.2;
}

double max(double)
{
  return 8.8;
}

int min(int)
{
  return 2;
}

int max(int)
{
  return 8;
}

template <typename Data>
void bench_mark_mul(benchmark::State &state)
{
  Data a, b;
  a = min(a);
  b = max(b);

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(a * b);
  }
}

template <typename Data>
void bench_mark_div(benchmark::State &state)
{
  Data a, b;
  a = min(a);
  b = max(b);

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(a / b);
  }
}

template <typename Data>
void bench_mark_sum(benchmark::State &state)
{
  Data a, b;
  a = min(a);
  b = max(b);

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(a + b);
  }
}

template <typename Data>
void bench_mark_dif(benchmark::State &state)
{
  Data a, b;
  a = min(a);
  b = max(b);

  while (state.KeepRunning())
  {
    benchmark::DoNotOptimize(a - b);
  }
}

BENCHMARK_TEMPLATE1(bench_mark_dif, double);
BENCHMARK_TEMPLATE1(bench_mark_sum, double);
BENCHMARK_TEMPLATE1(bench_mark_mul, double);
BENCHMARK_TEMPLATE1(bench_mark_div, double);

BENCHMARK_TEMPLATE1(bench_mark_dif, int);
BENCHMARK_TEMPLATE1(bench_mark_sum, int);
BENCHMARK_TEMPLATE1(bench_mark_mul, int);
BENCHMARK_TEMPLATE1(bench_mark_div, int);

BENCHMARK_MAIN();