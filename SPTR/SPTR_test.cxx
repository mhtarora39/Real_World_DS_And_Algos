#include <memory>
#include <iostream>
#include <vector>

class W_String;

// Custom dltr which ensure that object dele
void null_deleter(W_String *y)
{
  if (y == NULL)
  {
    std::cout << "Test";
  }
}

class W_String
{
  W_String(W_String &&w) = delete;
  static bool delted;

public:
  W_String(const W_String &wst)
  {
    std::cout << "&& Copy && \n";
    des = wst.des;
  }

  W_String()
  {
    std::cout << "Default\n";
  }
  ~W_String()
  {
    std::cout << " Distructed Object " << des << std::endl;
    if (Selfptr.size() > 0)
      std::cout << " ref count " << Selfptr[0].use_count();
  }

  //cant be const bcz we know this can be modified
  void AddEdge(W_String &obj)
  {
    // what forword do ?
    // what make shared v

    //std::shared_ptr<W_String> tmp(std::make_shared<W_String>(tmp));

    std::shared_ptr<W_String> tmp(&obj, null_deleter);

    Selfptr.push_back(tmp);
    std::cout << " OBJ REF COUNT " << Selfptr[Selfptr.size() - 1].use_count() << std::endl;
  }

  std::vector<std::shared_ptr<W_String>> Selfptr;
  std::string des;
};

int main()
{

  //Test 1;
  W_String obj;
  W_String obj1;
  // std::cout << "*******Default called*********\n";
  // std::shared_ptr<W_String> objptr(&obj);
  // std::shared_ptr<W_String> objCopy = objptr;
  // std::cout << "Both are pointing to same object : " << (objCopy.get() == objptr.get()) << std::endl;
  // std::cout << (*objCopy).des << " Copy CTOR Called ? " << std::endl;
  // std::vector<std::shared_ptr<W_String>> a;
  //a.push_back((objCopy));
  obj.des = "Mohit";
  obj.AddEdge(obj1);
  std::cout << "New Ref Count : " << obj.Selfptr[0].use_count() << std::endl;
  obj1.des = " Diksha ";

  // //objCopy->des = "Mohit";
  // std::cout << "Modifed : " << objCopy->des << " "
  //           << " Copied : " << objptr->des << std::endl;
  // std::cout << "From Vector " << a[0]->des << std::endl;
  for (auto &ele : obj.Selfptr)
  {
    std::cout << "Obj List " << ele->des << std::endl;
  }
  return 0;
}