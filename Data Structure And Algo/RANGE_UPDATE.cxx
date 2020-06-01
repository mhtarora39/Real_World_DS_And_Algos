#include <iostream>
#include <vector>

// Add elements in to particular range
// ie if we have array {1,2, 5,34} (Add 5 between index 1 and 3)

class RangeUpdate {
public:
  /*
    Create a vector of size n with
    all values as 10.
    vector<int> vector(n, 10);
  */
  explicit RangeUpdate(std::vector<int> array) : m_original(array),
                                                 m_copy(array.size(),0)
  {
  }


  //1,2,3
  //1,2,2
  //0,2,1

  void update(int start, int end, int value)
  {
    size_t size = m_original.size()
    if(start >=  size || start <  0  || end >= size || end < start) {
      throw "Invalid Min Max";
    }
    m_commands.push_back({start,end,value});
  }

  void execute()
  {
    size_t size_x = m_commands.size();
    for(int i = 0; i < size_x; i = i+3)
    {
      size_t start = m_commands[i];
      size_t end   = m_commands[i+1];
      int val      = m_commands[i+2]

      m_copy[start]   += val;
      if(end < size -1) {
        m_copy[end+1]   -= val
      }
    }
    for(int i = 0; i< m_copy.size() -1; i++)
    {
      m_copy[i+1] += m_copy[i];
      m_original[i] += m_copy[i];

    }

  }

  int get_sum(int start,int end) {
    int size = m_copy.size();
    if(start >=  size || start <  0  || end >= size || end < start) {
      throw "Invalid Min Max";
    }
    if(start == 0) {
      return m_copy[end];
    }
    return m_copy[end] + m_original[end] - m_copy[start -1]+ m_original[start - 1];
  }


private:
  std::vector<int> m_copy;
  std::vector<int> m_commands;
  std::vector<int> m_original;
};

int main() {
  RangeUpdate range({1,2,4});
  while(true) {
    std::cout << "Enter Start : ";
    int start;
    std::cin >> start;
    int end;
    std::cout << "\nEnter End : ";
    std::cin >> end;
    int val;
    std::cout << "\nenter value : " << val;
    if(end == -1) {
      range.execute();

    }

  }
}