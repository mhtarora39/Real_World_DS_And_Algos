#include <iostream>
#include <memory>

using namespace std;

class CPointer {
public:
    CPointer(double a, double b)
    {
        m_dX = a;
        m_dY = b;
    }

    ~CPointer()
    {
        m_dX = m_dY = 0;
    }


    double getX() const
    {return m_dX;}

    double getY() const
    {return m_dY;}

private:
    double m_dX;
    double m_dY;
};

class CContainer
{
public:
    CContainer(CPointer* p)
    {
        m_p = p;
    }

    ~CContainer()
    {
        m_p = nullptr;
    }

    CPointer* getP() const
    {return m_p;}

private:
    CPointer* m_p;

};


class CBigContainer
{
public:
    CBigContainer(std::shared_ptr<CContainer> p)
    {
        m_p = p.get();
    }
    ~CBigContainer()
    {
        m_p = nullptr;
    }
    CContainer* getP() const
    {return m_p;}

private:
    CContainer* m_p;
};

int main()
{
    CPointer* pPointer = new CPointer(150,360);

    cout << "1.) " << pPointer->getX() << " , " << pPointer->getY() << "\n";

    std::shared_ptr<CContainer> spContainer = std::make_shared<CContainer>(pPointer);

    cout << "2.) " << pPointer->getX() << " , " << pPointer->getY() << "\n";
    //std::shared_ptr<CContainer> other = std::move(spContainer);
    std::shared_ptr<CBigContainer> spBigContainer = std::make_shared<CBigContainer>(std::move(spContainer)); //<--- std::move here

   // cout << "3.) " << spBigContainer->getP()->getP()->getX() << " , " << spBigContainer->getP()->getP()->getY() << "\n";
    cout << "4.) " << spContainer->getP()->getX() << " , " << spContainer->getP()->getY() << "\n";
    cout << "5.) " << pPointer->getX() << " , " << pPointer->getY() << "\n";

    return 0;
}