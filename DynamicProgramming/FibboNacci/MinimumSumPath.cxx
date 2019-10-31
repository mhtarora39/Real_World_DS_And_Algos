#include <iostream>
#include <vector>


int main() {
  std::vector<std::vector<int>> array {
      {1,3,1},
      {1,5,1},
      {4,2,1}
   };

   int r = 2 , c = 2;
   
   //Make Sum Array 
   std::cout << "Array " << array.size() << std::endl;
   std::vector<std::vector<int>> sumArray; 
   for(int i  = 0;i <array.size(); i++ ) {
     std::vector<int> tmpArray;
     for(int j = 0; j < array[i].size(); j++) {
       int tmp  = array[i][j];
       if(i > 0 && j > 0) {
         tmp += sumArray[i-1][j];
         if(tmp > tmpArray[j-1] + array[i][j] ) {
           tmp = tmpArray[j-1] + array[i][j];
         }
       }
       else if(i>0 && j == 0) {
         tmp += sumArray[i-1][j];
       }
       else if(i==0 && j > 0)
       {
         tmp += tmpArray[j-1];
       }
       
       tmpArray.push_back(tmp);
     }
    std::cout << "size :" << tmpArray.size();
    sumArray.push_back(tmpArray);
   }

  
  for(auto row : sumArray) {
    for(auto item : row) {
      std::cout << item << " \t "; 
    }
    std::cout << "\n";
  }
   


  return 0;
}