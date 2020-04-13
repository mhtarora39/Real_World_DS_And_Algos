#include <iostream>
#include <vector>

using namespace std;

enum EStep {
  eUP,
  eLeft,
  eDown,
  eRight
};

void print_spiral(vector<vector<int>> arr,int n) {
  //given n os odd
  EStep step = eUP;
  int len = 0;
  std::cout << " " << arr[n/2][n/2] ;
  bool flag = true;
  int movment = 0;
  int row = n/2; // n = 3
  int clmn = n/2; // n =
  for(int i = 0; i < n*n;i++) {

    if(step == eUP) {
      if(flag) {
          len++;
          movment = ++len;
          flag = false;
        }
        row = row - 1;
        movment--;
        if(movment == 0) {
          flag = true;
          step = eLeft;
        }
      }
      else if(step == eLeft) {
        if(flag) {
          movment = len;
          flag = false;
        }
        clmn = clmn -1;
        movment--;
        if(movment == 0) {
          flag = true;
          step = eDown;
        }
      }
      else if(step == eDown) {
        if(flag) {
          movment = ++len;
          flag = false;
        }
        row = row+1;
        movment--;
        if(movment == 0) {
          flag = true;
          step = eRight;
        }
      }
      else if(step == eRight) {
        if(flag) {
          movment = len ;
          flag = false;
        }
        clmn = clmn - 1;
        movment--;
        if(movment == 0) {
          flag = true;
          step = eUP;
        }
      }
      if(clmn < 0 || row < 0) {
        break;
      }
      std::cout << arr[row][clmn] << " ";

    }
  }

  int main() {
    vector<vector<int>> arr{{1,2,3},{4,5,6},{7,8,9}};
    print_spiral(arr,3);
    return 0;
    int a;
    // cin >> a;
    // while (true)
    // {
    //   /* code */
    // }

  }

