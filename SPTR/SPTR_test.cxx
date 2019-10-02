#include<memory>
#include<iostream>
#include<vector>

class W_String{
public:
W_String() {
  std::cout<< "Default\n";
}
~W_String() {}

W_String(const W_String& wst) {
 
 
 std::cout << "&& Copy && \n";
 
}

//cant be const bcz we know this can be modified
void AddEdge(W_String& obj ) {
    // what forword do ?
    // what make shared do ?
    std::shared_ptr<W_String> tmp(&obj);

    Selfptr.push_back(tmp);
    std::cout << " OBJ REF COUNT "<< Selfptr[Selfptr.size() - 1].use_count() << std::endl;

}


std::vector<std::shared_ptr<W_String>> Selfptr;
std::string des;

}; 



int main() {
  

  //Test 1;
  W_String obj;
  W_String obj1;
  std::cout<<"*******Default called*********\n";
  std::shared_ptr<W_String> objptr(&obj);
  std::shared_ptr<W_String> objCopy = objptr;
  std::cout<<"Both are pointing to same object : "<<(objCopy.get() == objptr.get()) << std::endl;
  std::cout <<   (*objCopy).des << " Copy CTOR Called ? " << std::endl;
  std::vector<std::shared_ptr<W_String>> a;
  a.push_back((objCopy));
  obj.des = "Mohit";
  
  obj.AddEdge(obj1);
  obj1.des = " Diksha ";

  //objCopy->des = "Mohit";
  std::cout << "Modifed : "<< objCopy->des << " " << " Copied : " << objptr->des<<std::endl;
  std::cout << "From Vector " << a[0]->des << std::endl;
  for(auto &ele : obj.Selfptr) {
    std::cout << "Obj List "   << ele->des <<std::endl;
  } 
  return 0;
}