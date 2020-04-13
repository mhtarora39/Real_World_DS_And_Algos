#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

// Two strings are anagrams of each other if the letters of one string can be rearranged to form the other string. Given a string, find the number of pairs of substrings of the string that are anagrams of each other.
// For example , the list of all anagrammatic pairs is  at positions  respectively.
// Function Description
// Complete the function sherlockAndAnagrams in the editor below. It must return an integer that represents the number of anagrammatic pairs of substrings in .

// sherlockAndAnagrams has the following parameter(s):
// s: a string .
// Input Format
// The first line contains an integer , the number of queries.
// Each of the next  lines contains a string  to analyze.
// Constraints
// String  contains only lowercase letters  ascii[a-z].
// Output Format
// For each query, return the number of unordered anagrammatic pairs.
// Sample Input 0
// 2
// abba
// abcd
// Sample Output 0

// 4
// 0
// Explanation 0

// The list of all anagrammatic pairs is  and  at positions  and  respectively.

// No anagrammatic pairs exist in the second query as no character repeats.

// Sample Input 1

// 2
// ifailuhkqq
// k_k_k_k =
// kk   => 2
// KKK  =>
// How many continues le
// Sample Output 1

// 3
// 10


//I did as well at first. But it's easier if you break it into two parts:

//Traverse all possible substrings within string
//Check if any two substrings of equal length are anagrams
//
//


///K K K
//0->K, KK,  K ,kkk ,
using namespace std;

void get_sub_strings(string str,vector<string> & tmp) {
  for(int i = 0; i < str.size(); i++) {
   // std::cout << string(str.begin(), str.begin()+i+1) << " out \n";
    tmp.push_back(string(str.begin(), str.begin()+i+1));
    if(i != 0 ) {
     // std::cout << string(str.begin()+i,str.end()) << " Insie \n";
      tmp.push_back(string(str.begin()+i,str.end()));
    }
  }
}
// void get_sub_strings(string str,vector<string> & tmp) {
//   for(int i = 0; i < str.size(); i++) {
//    // std::cout << string(str.begin(), str.begin()+i+1) << " out \n";
//     tmp.push_back(string(str.begin(), str.begin()+i+1));
//     if(i != 0 ) {
//      // std::cout << string(str.begin()+i,str.end()) << " Insie \n";
//       tmp.push_back(string(str.begin()+i,str.end()));
//     }
//   }
// }
// // Complete the sherlockAndAnagrams function below.
// int sherlockAndAnagrams(string s) {
//   //Bruit Force
//   vector<string> sub_string;
//   for(int i = 0; i < s.size()/2; i++) {
//     get_sub_strings(string(s.begin()+i,s.end()-i),sub_string);
//   }
//  //get_sub_strings(s,sub_string);
//   int count = 0;
//   for(int i = 0; i < sub_string.size() ; i++) {
//     for(int j = i + 1; j < sub_string.size(); j++) {
//       if(sub_string[i].size() == sub_string[j].size() ) {
//         std::reverse(sub_string[i].begin() , sub_string[i].end());
//         if(sub_string[i] == sub_string[j]) {
//           count++;
//         }
//       }
//     }

//   }
//   return count;
// }


int ana(std::string s) {

  vector<string> sub_string;
  for(int i = 0; i < s.size()/2; i++) {
    get_sub_strings(string(s.begin()+i,s.end()-i),sub_string);
  }
  // for(auto & item : sub_string) {
  //   std::cout << item << std::endl;
  // }
 //get_sub_strings(s,sub_string);
  int count = 0;
  for(int i = 0; i < sub_string.size() ; i++) {
    string tmp = sub_string[i];
    std::reverse(tmp.begin(),tmp.end());
    for(int j = i+1; j < sub_string.size(); j++) {
      if(sub_string[i].size() == sub_string[j].size() ) {
        bool is_ana = true;
        int bit_mask_a[26] = {0};
        for(int k = 0; k < sub_string[i].size(); k++) {
           bit_mask_a[(sub_string[i][k]-97)]++ ;
           bit_mask_a[(int(sub_string[j][k]) - 97)]--;
        }

        for(int k =0; k < 26 ;k++ ) {
          if(bit_mask_a[k]) {
            is_ana = false;
          }

        }

        if(is_ana) {
        // std::cout << "------ " <<sub_string[i] << "    " << sub_string[j] <<std::endl;
          count++;
        }
      }
    }
  }
  std::cout << count << std::endl;
  cin >> count;

}

int main() {
  ana("ifailuhkqq");
  return 0;
}