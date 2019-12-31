#include<vector>
#include<queue>
#include <random>
#include<benchmark/benchmark.h>



#define Args \
  ->RangeMultiplier(2)->Range(8, 6 * 1024 * 1024)->UseRealTime()

//   ->RangeMultiplier(2)->Range(4, 2 * 1024 * 1024 * 50)->UseRealTime()

using namespace std;

template <typename Word>
void acess_vector(benchmark::State &state)
{
  vector<Word> container;
    
}

template <typename Word>
void access_queue(benchmark::State &state)
{
}