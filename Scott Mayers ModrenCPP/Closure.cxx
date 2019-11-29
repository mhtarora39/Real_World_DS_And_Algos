#include <iostream>


enum class EOperations {
  eAdd,
  eSub
};

//(a+b) + (b+c)
template<typename T>
class BinOperation {
  public:

    BinOperation(EOperations eType):m_type(eType)
    {
    }

    T operator() (T &rhs, T &lhs) {
      switch (m_type)
      {
      case EOperations::eAdd:
        return rhs() +
        break;

      default EOperations::eSub:
        break;
      }
    }




  private:
    EOperations m_type;
}