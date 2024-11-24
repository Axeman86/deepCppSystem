#include <iostream>
#include <memory>
using namespace std;

class Base1
{
public:
    virtual ~Base1()                       = default;
    virtual std::unique_ptr<Base1> clone() = 0;
};

class Sub1 : public Base1
{ //继承

public:
    Sub1(int data)
    {
        cout << "Sub1 constructor data value " << data << endl;
        //....
    }

    Sub1(const Sub1 & rhs)
    {
        cout << "Sub1 Copy constructor" << endl;
        //....
    }

    std::unique_ptr<Base1> clone() override
    {
        return std::make_unique<Sub1>(*this); // called Copy constructor functions
    }
};

class Sub2 : public Sub1
{ //继承
public:
    Sub2(int data) : Sub1(data)
    {
        cout << "Sub2 constructor data value " << data << endl;
        //....
    }

    Sub2(const Sub2 & rhs) : Sub1(rhs)
    {
        cout << "Sub2 Copy constructor" << endl;
        //....
    }

    std::unique_ptr<Base1> clone() override
    {
        return std::make_unique<Sub2>(*this); // called Copy constructor
    }
};

int main()
{
    std::unique_ptr<Base1> pb = std::make_unique<Sub2>(100);
    cout << "================================" << endl;
    std::unique_ptr<Base1> pb2 = pb->clone();
}
