#include <vector>
// We define subsequence as any subset of an array. We define a subarray as a contiguous subsequence in an array.

// Given an array, find the maximum possible sum among:

// all nonempty subarrays.
// all nonempty subsequences.
// Print the two values as space-separated integers on one line.

// Note that empty subarrays/subsequences should not be considered.

// For example, given an array , the maximum subarray sum is comprised of element inidices  and the sum is . The maximum subsequence sum is comprised of element indices  and the sum is .

// Function Description

// Complete the maxSubarray function in the editor below. It should return an array of two integers: the maximum subarray sum and the maximum subsequence sum of .

// maxSubarray has the following parameter(s):

// arr: an array of integers
// Input Format

// The first line of input contains a single integer , the number of test cases.

// The first line of each test case contains a single integer .
// The second line contains  space-separated integers  where .

// Constraints

// The subarray and subsequences you consider should have at least one element.

// Output Format

// Print two space-separated integers denoting the maximum sums of nonempty subarrays and nonempty subsequences, respectively.

// Sample Input 0

// 2
// 4
// 1 2 3 4
// 6
// 2 -1 2 3 4 -5
// Sample Output 0

// 10 10
// 10 11
// Explanation 0

// In the first case: The maximum sum for both types of subsequences is just the sum of all the elements since they are all positive.

// In the second case: The subarray  is the subarray with the maximum sum, and  is the subsequence with the maximum sum.

// Sample Input 1


#include <bits/stdc++.h>

#define INTMIN -2147483647
using namespace std;

vector<string> split_string(string);

// Complete the maxSubarray function below.
vector<long> maxSubarray(vector<int> arr) {
  //  2 -1 2 3 4 -5
  long max_sub_seq = 0;
  long max_sub     = 0;
  long max         = 0;
  bool all_nag     = true;
  size_t size = arr.size();
  //long tmp = 0;

  for(size_t i = 0; i < size; i++) {
    if(max_sub + arr[i] > 0) {
      all_nag = false;
      max_sub = max_sub + arr[i];
      if(arr[i] > 0) {
        max_sub_seq += arr[i];
      }
      max = max < max_sub ? max_sub : max;
    }
    else {
      max_sub = 0;
    }
  }

  if(max > max_sub) {
    max_sub =  max;
  }

  // All numbers are negative
  if(all_nag) {
    long min = INTMIN;
    for(auto &ele : arr) {
      if(ele > min) {
        min = ele;
      }
    }
    max_sub_seq = min;
    max_sub     = min;
  }
  return {max_sub,max_sub_seq};
}