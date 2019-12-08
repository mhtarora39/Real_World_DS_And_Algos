
#include <string.h>
#include <emmintrin.h>
#include <immintrin.h>
#include <string>

#include <benchmark/benchmark.h>
//These are range arguments
// This line is just defining range mltyply by
// 2 start from 1024 to 2 Mb
#define ARGS \
  ->RangeMultiplier(2)->Range(4, 2 * 1024 * 1024 * 50)->UseRealTime()

template <typename T>
std::string get_type(T *)
{
  return " T * ";
}

template <typename T>
std::string get_type(const T *)
{
  return " const  T * ";
}

//Write to memory
template <class Word>
void BM_Write_Sq(benchmark::State &state)
{
  void *memory;
  //Allocate allign memoru
  //state.range_x() getting from ARGS preprocesser
  if (::posix_memalign(&memory, 64, state.range_x()) != 0)
    return;
  void *const end = static_cast<char *>(memory) + state.range_x();
  Word fill;
  memset(&fill, 0xab, sizeof(fill));
  Word *const start = static_cast<Word *>(memory);
  Word *const cend = static_cast<Word *>(end);
  //Keep runnig until collect data
  //we will see iteration count
  while (state.KeepRunning())
  {
    for (Word *p = start; p < cend; ++p)
    {
      benchmark::DoNotOptimize(*p = fill);
    }
  }
  free(memory);
}

//Read From Memory
template <class Word>
void BM_read_Sq(benchmark::State &state)
{
  void *memory;
  if (::posix_memalign(&memory, 64, state.range_x()) != 0)
    return;
  void *const end = static_cast<char *>(memory) + state.range_x();
  Word fill;
  //memset(&fill,0xab,sizeof(fill));
  Word *const start = static_cast<Word *>(memory);
  Word *const cend = static_cast<Word *>(end);
  while (state.KeepRunning())
  {

    for (Word *p = start; p < cend; p++)
    {
      benchmark::DoNotOptimize(fill = *p);
    }
  }
  free(memory);
}

// undefined reference to
//`benchmark::Initialize(int*, char**)'

BENCHMARK_TEMPLATE1(BM_Write_Sq, long)
ARGS;
BENCHMARK_TEMPLATE1(BM_read_Sq, long)
ARGS;

BENCHMARK_MAIN();
