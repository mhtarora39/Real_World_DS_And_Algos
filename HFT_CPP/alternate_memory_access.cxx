#include <iostream>
#include <string>
#include <benchmark/benchmark.h>
#include <random>
#include <string.h>

// #define REPEATE2(X) X X

// #define REPEATE4(X) \
//   REPEATE2(X)       \
//   REPEATE2(X)
// #define REPEATE8(X) \
//   REPEATE4(X)       \
//   REPEATE4(X)

// #define REPEATE16(X) \
//   REPEATE8(X)        \
//   REPEATE8(X)

// #define REPEATE32(X) \
//   REPEATE32(X)       \
//   REPEATE32(X)

#define ARGS \
  ->RangeMultiplier(2)->Range(16, 2 * 1024 * 1024)->UseRealTime()

template <typename Word>
void read_alternate(benchmark::State &state)
{
  void *memory;
  const size_t size = state.range_x();
  if (::posix_memalign(&memory, 64, size) != 0)
    return;
  Word fill;
  void *const end = static_cast<char *>(memory) + state.range_x();
  memset(&fill, 0xab, sizeof(fill));
  Word *start = static_cast<Word *>(memory);
  Word *const cend = static_cast<Word *>(end);
  const size_t N = size / sizeof(Word);
  Word arr[N];
  int j = 0;
  for (Word i = 0; i < N; i++)
  {
    if (i % 2 == 0)
    {
      arr[j] = i;
      j++;
    }
  }
  for (int i = 0; i < N; i++)
  {
    if (i % 2 == 1)
    {
      arr[j] = i;
      j++;
    }
  }

  while (state.KeepRunning())
  {
    for (auto i = 0; i < N; i++)
    {
      benchmark::DoNotOptimize(*(start + arr[i]) = fill);
    }
  }
  ::free(memory);
}

template <typename Word>
void read_seq(benchmark::State &state)
{
  void *memory;
  const size_t size = state.range_x();
  if (::posix_memalign(&memory, 64, size) != 0)
    return;
  void *const end = static_cast<char *>(memory) + state.range_x();
  Word fill;
  memset(&fill, 0xab, sizeof(fill));
  Word *start = static_cast<Word *>(memory);
  Word *const cend = static_cast<Word *>(end);
  const size_t N = size / sizeof(Word);
  Word arr[N];
  for (Word i = 0; i < N; i++)
  {
    arr[i] = i;
  }

  while (state.KeepRunning())
  {
    for (auto i = 0; i < N; i++)
    {
      benchmark::DoNotOptimize(*(start + arr[i]) = fill);
    }
  }

  ::free(memory);
}

template <typename Word>
void read_rev(benchmark::State &state)
{
  void *memory;
  const size_t size = state.range_x();
  if (::posix_memalign(&memory, 64, size) != 0)
    return;
  void *const end = static_cast<char *>(memory) + state.range_x();
  Word fill;
  memset(&fill, 0xab, sizeof(fill));
  Word *start = static_cast<Word *>(memory);
  Word *const cend = static_cast<Word *>(end);
  const size_t N = size / sizeof(Word);
  Word arr[N];
  for (Word i = 0; i < N; i++)
  {
    arr[i] = N - i - 1;
  }

  while (state.KeepRunning())
  {
    for (auto i = 0; i < N; i++)
    {
      benchmark::DoNotOptimize(*(start + arr[i]) = fill);
    }
  }

  ::free(memory);
}

BENCHMARK_TEMPLATE1(read_alternate, long)
ARGS;

BENCHMARK_TEMPLATE1(read_seq, long)
ARGS;

BENCHMARK_TEMPLATE1(read_rev, long)
ARGS;

BENCHMARK_MAIN();