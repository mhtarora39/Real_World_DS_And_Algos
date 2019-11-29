#include <iostream>
#include <fstream>
#include <vector>

namespace FileSys {


void read_data(std::string path, std::vector<long>& data , size_t size) {
  std::fstream ifile;
  ifile.open(path,std::fstream::in | std::fstream::out);
  if(ifile.fail()) {
    std::cout <<"Failed\n";
    return;
  }
  std::string word;
  data.reserve(size);
  while(ifile>>word) {
    data.push_back(std::stol(word));
  }

}


};