#include "benchmark/benchmark.h"
#include "thread"
#include "vector"
#include "pthread.h"
#include "iostream"

#define ARGS \
  ->RangeMultiplier(2)->Range(1, 128)->UseRealTime();
class PosixThread;
//int N[4] =
void *thread_routine(void *in = NULL);
// {
//   ((PosixThread *)in)->Run();
// }

class MyThread
{
public:
  MyThread(int n) : data(n)
  {
  }

  void operator()()
  {
    int a = 1;
    for (int i = 0; i < data; i++)
    {
      a++;
    }
  }

private:
  int data;
};

class PosixThread
{
public:
  PosixThread(int data) : m_data(data)
  {

    pthread_create(&th, NULL, thread_routine, this);
  }

  void Run()
  {
    //std::cout << "in run";
    int a = 1;
    for (int i = 0; i < m_data; i++)
    {
      a++;
    }
  }

  ~PosixThread()
  {
    // pthread_join(th, NULL);
  }

private:
  int m_data;
  pthread_t th;
  // void *thread_routine(void *in = NULL)
  // {
  //   Run();
  // }
};

void *thread_routine(void *in)
{
  ((PosixThread *)in)->Run();
}

void BenchMark_thread(benchmark::State &state)
{
  int N = 100000;
  bool first = true;
  //std::cout << "Number of system threads : " << std::thread::hardware_concurrency() << std::endl;
  std::vector<std::thread *> threads(state.range_x());
  while (state.KeepRunning())
  {
    for (int i = 0; i < state.range_x(); i++)
    {

      int num = (N / (i + 1));
      //   // if (first)
      //   // {
      //   //   std::cout << state.range_x() << " " << num << std::endl;
      //   // }
      MyThread th(num);
      threads[i] = new std::thread(th);
    }
    first = false;
    for (int i = 0; i < state.range_x(); i++)
    {
      threads[i]->join();
    }
  }
}

void BenchMark_pthread(benchmark::State &state)
{
  int N = 100000;
  bool first = true;
  //std::cout << "Number of system threads : " << std::thread::hardware_concurrency() << std::endl;
  std::vector<PosixThread *> threads(state.range_x());
  while (state.KeepRunning())
  {
    for (int i = 0; i < state.range_x(); i++)
    {

      int num = (N / (i + 1));
      //   // if (first)
      //   // {
      //   //   std::cout << state.range_x() << " " << num << std::endl;
      //   // }
      //PosixThread th(num);
      threads[i] = new PosixThread(num);
    }
    // first = false;
    // for (int i = 0; i < state.range_x(); i++)
    // {
    //     threads[i]->join();
    // }
  }
}
BENCHMARK(BenchMark_thread)
ARGS
    BENCHMARK(BenchMark_pthread) ARGS
    BENCHMARK_MAIN();