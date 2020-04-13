
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include "read_test_file.hpp"
#include <algorithm>

using namespace std;


// You are given an array and you need to find number of tripets of indices  such that the elements at those indices are in geometric progression for a given common ratio  and .

// For example, . If , we have  and  at indices  and .

// Function Description

// Complete the countTriplets function in the editor below. It should return the number of triplets forming a geometric progression for a given  as an integer.

// countTriplets has the following parameter(s):

// arr: an array of integers
// r: an integer, the common ratio
// Input Format

// The first line contains two space-separated integers  and , the size of  and the common ratio.
// The next line contains  space-seperated integers .

// Constraints

// Output Format


//  1,2,1,2,4
//->(1 => 2 => 4) =>
//->()





long countTriplets(vector<long> arr, long r) {
  // Bruit force
  long total = 0;

  map<long,set<long>> seq_map;

  for(int i = 0; i < arr.size(); i++) {
    if(arr[i]%r == 0) {
      seq_map[arr[i]].insert(i);
    }
  }

  for(int i = 0; i < arr.size(); i++) {
    if(arr[i]%r != 0 && seq_map.find(arr[i]*r) != seq_map.end()) {
      seq_map[arr[i]].insert(i);
    }
  }

  for(auto& item : seq_map) {
    std::cout<< item.first << " ";
    for(auto &it : item.second ) {
      std::cout << it << " ";
    }
    std::cout <<std::endl;
  }


  for(int i = 0; i < arr.size(); i++) {

    if(seq_map.find(arr[i]) != seq_map.end() &&
       seq_map.find(arr[i]*r) != seq_map.end() &&
       seq_map.find(arr[i]*r*r) != seq_map.end()
      ) {
       if(!seq_map[arr[i]].empty() && *(seq_map[arr[i]].begin()) == i ) {
          std::cout << arr[i] << std::endl;
          total += max({*seq_map[arr[i]].begin(), }) ;
          seq_map[arr[i]].erase(i);
       }
      }

  }
  return total;
}

// Return the count of triplets that form a geometric progression.
// long countTriplets(vector<long> arr, long r) {
//   long size = arr.size();
//   long total = 0;
//   map<long,long> n_c;
//   for(auto &ele : arr) {
//     //cout << ele << std::endl;
//     if(ele % r == 0) {
//       if(n_c.find(ele) ==  n_c.end()) {
//         n_c[ele] = 0;
//       }
//       n_c[ele] +=1;
//     }
//   }

//   for(auto &ele : arr) {
//     if(ele%r != 0) {

//       if(n_c.find(ele*r) !=  n_c.end() && n_c.find(ele*r*r) !=  n_c.end()) {
//         if(n_c.find(ele) ==  n_c.end()) {
//           n_c[ele] = 0;
//         }
//         n_c[ele] +=1;
//       }
//     }
//   }


//   if(r != 1) {
//     for(auto &item : arr) {
//       if(n_c[item] > 0&& n_c.find(item) != n_c.end()&& n_c.find(item*r) != n_c.end() &&
//         n_c.find(item*r*r) != n_c.end()) {
//         total+=max({1L,n_c[item*r],n_c[item*r*r]});
//       }

//       if(n_c.find(item) != n_c.end()) {
//        // cout << item <<std::endl;
//         n_c[item] -=1;
//       }

//     }
//   }

//   else {
//     for(auto &item : n_c) {
//       size   = item.second;
//       total += (size*(size-1)*(size-2))/ 6;
//     }
//   }

 // std::cout << total << std::endl;
//   return total;

// }
// long countTriplets(vector<long> arr, long r) {
//   long size = arr.size();
//   long total = 0;
//   map<long,long> n_c;
//   for(auto &ele : arr) {
//     //cout << ele << std::endl;
//     if(ele % r == 0) {
//       if(n_c.find(ele) ==  n_c.end()) {
//         n_c[ele] = 0;
//       }
//       n_c[ele] +=1;
//     }
//   }

//   for(auto &ele : arr) {
//     if(ele%r != 0) {

//       if(n_c.find(ele*r) !=  n_c.end() && n_c.find(ele*r*r) !=  n_c.end()) {
//         if(n_c.find(ele) ==  n_c.end()) {
//           n_c[ele] = 0;
//         }
//         n_c[ele] +=1;
//       }
//     }
//   }


//   if(r != 1) {
//     for(auto &item : n_c) {
//       if(n_c.find(item.first*r) != n_c.end()&& n_c.find(item.first*r) != n_c.end() &&
//         n_c.find(item.first*r*r) != n_c.end()) {
//         total+= max({n_c[item.first],n_c[item.first*r],n_c[item.first*r*r]});
//       }
//     }
//   }

//   else {
//     for(auto &item : n_c) {
//       size   = item.second;
//       total += (size*(size-1)*(size-2))/ 6;
//     }
//   }

//  // std::cout << total << std::endl;
//   return total;

// }

int main(int argc, const char** argv) {
  std::vector<long> data;
  //FileSys::read_data("test_H_M_2.text",data,100000);
  long c = countTriplets({1,2,1,2,4},2);
  std::cout << " count " << c << std::endl;
}