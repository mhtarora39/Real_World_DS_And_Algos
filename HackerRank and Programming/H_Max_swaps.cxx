#include <iostream>
#include <vector>

// You are given an unordered array consisting of consecutive integers  [1, 2, 3, ..., n] without any duplicates. You are allowed to swap any two elements. You need to find the minimum number of swaps required to sort the array in ascending order.

// For example, given the array  we perform the following steps:

// i   arr                         swap (indices)
// 0   [7, 1, 3, 2, 4, 5, 6]   swap (0,3)
// 1   [2, 1, 3, 7, 4, 5, 6]   swap (0,1)
// 2   [1, 2, 3, 7, 4, 5, 6]   swap (3,4)
// 3   [1, 2, 3, 4, 7, 5, 6]   swap (4,5)
// 4   [1, 2, 3, 4, 5, 7, 6]   swap (5,6)
// 5   [1, 2, 3, 4, 5, 6, 7]
// It took  swaps to sort the array.

// Complete the minimumSwaps function below.
int minimumSwaps(vector<int> arr) {
    int c = 0;
    vector<int> f(arr.size(), 0);

    for (int i = 0; i < arr.size(); ++i) {
        f[arr[i] - 1] = i;
    }

    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] - 1 != i) {
            c++;
            arr[f[i]] = arr[i];
            f[arr[i] - 1] = f[i];
        }
    }
    return c;
}
using namespace std;
int minimumSwaps(vector<int> arr) {
  int swap_count = 0;
 int tot_count  =0;
  //size_t i          = 0;
  size_t size       = arr.size();
  vector<bool> visited(size,false);

  for(int i = 0; i < size; i++) {
    int index = i;
    swap_count = 0;
    while (true)
    {

      if(arr[index] == index+1 || (arr[index] == arr[i]) || visited[index]) {
        if((arr[index] == arr[i]) && visited[index] && swap_count != 0)
          tot_count += swap_count -1;
        break;
      }
      else {
        index = arr[index] -1;
        swap_count++;
      }
      visited[index] = true;
    }

  }




  return swap_count;

}

// It's New Year's Day and everyone's in line for the Wonderland rollercoaster ride!
//There are a number of people queued up, and each person wears a sticker indicating their
//initial position in the queue. Initial positions increment by from  at the front of the line
//to  at the back.Any person in the queue can bribe the person directly in front of them to swap
//positions. If two people swap positions, they still wear the same sticker denoting their original
//places in line. One person can bribe at most two others. For example, if  and  bribes ,
//the queue will look like this: .Fascinated by this chaotic queue, you decide you must know the
//minimum number of bribes that took place to get the queue into its current state!