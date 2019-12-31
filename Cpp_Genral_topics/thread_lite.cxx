#include <pthread.h>
#include <map>
#include <iostream>

namespace Thread
{

class RAII_Thread;
struct Options
{
  static const Options default_op()
  {
    return Options();
  }
};

void *start_rutine(void *st);

class RAII_Thread
{
public:
  RAII_Thread(Options optionds = Options::default_op()) : m_joinable(true)
  {
    std::cout << "self : " << this << std::endl;
  }
  void start()
  {

    pthread_create(&m_thread, nullptr, start_rutine, this);
  }

  virtual ~RAII_Thread()
  {
  }

  virtual void run() = 0;

  // {
  //   std::cout << "This should not\n";
  // }
  void join()
  {
    if (m_joinable)
    {
      std::cout << "Joining..." << std::endl;
      int *error_number;
      pthread_join(m_thread, (void **)&error_number);
      // if ((intptr_t)(error_number) != 0)
      // {
      //   errors[m_thread] = (intptr_t)(error_number);
      // }
    }
    std::cout << "join completed \n";
  }

  Options m_options;
  pthread_t m_thread;
  bool m_joinable;
  static std::map<pthread_t, intptr_t> errors;
};

void *start_rutine(void *st)
{

  std::cout << "Strating Routine \n"; //<< &(((RAII_Thread *)(st))->run) << std::endl;
  ((RAII_Thread *)(st))->run();
}

class MyThread : public RAII_Thread
{

public:
  MyThread(const Options ops = Options::default_op()) : parent(ops)
  {
    std::cout << " self " << this << std::endl;
  }
  ~MyThread()
  {
    join();
    std::cout << "Distroying ..\n";
  }

  void run() override
  {
    std::cout << "Thread is running" << std::endl;
  }

private:
  typedef RAII_Thread parent;
};
std::map<pthread_t, intptr_t> RAII_Thread::errors = std::map<pthread_t, intptr_t>();
} // namespace Thread

//test

struct Test
{
  Test()
  {
    Start(this);
  }

protected:
  virtual void run() = 0;
  static void Start(void *t)
  {
    ((Test *)t)->run();
  }
};
struct Test2 : public Test
{
  void run()
  {
    std::cout << "This is running";
  }
  /* data */
};

int main()
{
  // Test *a(new Test2());
  std::cout << "Main started\n";
  Thread::RAII_Thread *th(new Thread::MyThread());
  th->start();

  // while (true)
  // {
  //   /* code */
  // }
  //th->join();
  delete (th);
}