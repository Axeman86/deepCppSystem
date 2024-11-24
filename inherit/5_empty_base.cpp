#include <iostream>
using namespace std;

class Base
{
public:
    void process() {}

}; // 1byte

class Sub1
{
    Base b;
    double data; // 8 byte

public:
    void func() { b.process(); }
};

// 私有继承 == 组合
class Sub2 : public Base
{
    double data;

public:
    void func() { Base::process(); }
};

int main()
{
    int d1;
    Base b; // 1byte
    Base * pb = &b;
    int d2;
    // b.process(); //process(&b)  -> JMP 0x0000800

    cout << sizeof(Base) << endl; // 8 Byte
    cout << sizeof(Sub1) << endl; // 16 Byte
    cout << sizeof(Sub2) << endl; // 8 Byte
}
