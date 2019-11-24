#include <algorithm>
#include <vector>
#include <initializer_list>
#include <cmath>
#include <iostream>

template <typename T>
class BinaryHeap
{

  using Heap = BinaryHeap<T>;
  using Iterator = BinaryHeap<T> *;

public:
  BinaryHeap(const std::initializer_list<T> &elements)
  {
    for (auto &ele : elements)
    {
      push_back(ele);
    }
  }

  BinaryHeap(BinaryHeap &&other)
  {
    size = 0;
    std::swap(*this, other);
  }

  BinaryHeap() : size(0)
  {
  }

  //print level wise
  void debug_out()
  {
    for (auto &item : heap_array)
    {
      std::cout << " --- " << item << std::endl;
    }
  }
  void shift_up(size_t index)
  {
    //error prone
    if (index <= 0)
    {
      return;
    }
    else
    {
      //2,3,1,3,4
      //3,3,1,2,4
      //3,4,1,2,3
      //4,3,1,2,3

      size_t parent = floor(index / 2) - (index + 1) % 2;
      if (parent >= 0 && heap_array[parent] < heap_array[index])
      {
        std::swap(heap_array[parent], heap_array[index]);
        shift_up(parent);
      }
    }
  }

  void shift_down(size_t index)
  {
    size_t lh = 2 * index + 1;
    size_t rh = 2 * index + 2;

    if ((rh >= size && lh < size) ||
        (lh < size && rh < size && heap_array[lh] > heap_array[rh]))
    {
      if (heap_array[index] < heap_array[lh])
        std::swap(heap_array[index], heap_array[lh]);
      shift_down(lh);
    }

    if ((rh < size && lh >= size) ||
        (lh < size && rh < size && heap_array[lh] < heap_array[rh]))
    {
      if (heap_array[index] < heap_array[rh])
        std::swap(heap_array[index], heap_array[rh]);
      shift_down(rh);
    }
  }

  BinaryHeap(const Heap &copy)
  {
    //test std::Copy
  }

  size_t count()
  {
    return size;
  }

  bool operator==(const Heap &other)
  {
    return true;
    //TODO Vector equal
  }

  // Iterator begin()
  // {
  // }

  // Iterator end()
  // {
  // }

  // custom deleter
  void push_back(const T &data)
  {
    // ToDo check for value type
    heap_array.push_back(data);
    size++;
    shift_up(size - 1);
  }

  T extract_max()
  {
    T ele;
    if (size >= 1)
    {
      size--;
      ele = heap_array[0];
      std::swap(heap_array[0], heap_array[size]);
      heap_array.erase(heap_array.begin() + size);
      shift_down(0);
      return ele;
    }
    else
    {
      return heap_array[0];
    }
  }

  // T &pop()
  // {
  // }

private:
  std::vector<T>
      heap_array;
  size_t size;
};

int main()
{
  BinaryHeap<int> heap({2, 3, 1, 3, 4});
  heap.debug_out();
  std::cout << heap.extract_max() << std::endl;
  std::cout << heap.extract_max() << std::endl;
  std::cout << heap.extract_max() << std::endl;
  std::cout << heap.extract_max() << std::endl;
  return 0;
}
