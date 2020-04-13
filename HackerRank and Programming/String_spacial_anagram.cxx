// A string is said to be a special string if either of two conditions is met:

// All of the characters are the same, e.g. aaa.
// All characters except the middle one are the same, e.g. aadaa.
// A special substring is any substring of a string which meets one of those criteria. Given a string, determine how many special substrings can be formed from it.

// For example, given the string , we have the following special substrings: .

#include <string>
#include <vector>
#include <set>


using namespace std;
// Complete the substrCount function below.
long substrCount(int n, string s) {
  vector<pair<char,long>> total;
  long count = 1;
  char ch = s[0];
  long index = 0;
  total.push_back({ch,count});
  for(long i = 1; i < n; i++) {
    if(total[index].first == s[i]) {
       total[index].second = ++count;
    }
    else {

      count =1;
      total.push_back({s[i],count});
      ++index;
    }
  }
  //std::cout << index << std::endl;
  count = 0;
  for(long i =0; i <= index; i++) {
  // std::cout << total[i].second << " i " << i << std::endl;
   count = count + ((total[i].second * (total[i].second + 1)) / 2);
  }
  //std::cout << count << std::endl;
  for(long i = 1; i < index; i++) {
    if(total[i - 1].first == total[i + 1].first && total[i].first != total[i + 1].first ){
        count += min(total[i - 1].second,total[i + 1].second);
    }
  }

  return count;

}

