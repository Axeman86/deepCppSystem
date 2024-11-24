#include <iostream>
using namespace std;

struct Base1
{
    double d1;
    double d2;
    double d3;
    double d4;

    Base1() { cout << "Base1()" << endl; }

    ~Base1() { cout << "~Base1()" << endl; }
};
struct Sub1 : virtual Base1
{
    double d5;

    Sub1() { cout << "Sub1()" << endl; }

    ~Sub1() { cout << "~Sub1()" << endl; }
};

struct Sub2 : virtual Base1
{
    double d6;

    Sub2() { cout << "Sub2()" << endl; }

    ~Sub2() { cout << "~Sub2()" << endl; }
};

/*
 *    Base1
 *    /   \
 *   /     \
 *  /       \
 * Sub1     Sub2
 *  \       /
 *   \     /
 *    \   /
 *     Sub3
 * If you don't use virtual inheritance, the Sub3 object will have two Base1 objects.
 * */
struct Sub3 : Sub1, Sub2
{
    double d7;

    Sub3() { cout << "Sub3()" << endl; }

    ~Sub3() { cout << "~Sub3()" << endl; }
};

int main()
{
    cout << sizeof(Base1) << endl; // 32
    cout << sizeof(Sub1) << endl;  // 32+8=40       32(B1)+8(S1)+8(vbptr*)=48
    cout << sizeof(Sub2) << endl;  // 32+8=40       32(B1)+8(S2)+8(vbptr*)=48
    cout << sizeof(Sub3) << endl;  // 40+40+8=88   32(B1)+8(S1)+8(S2)+8(S1->vbptr*)+8(S2->vbptr*)+8(S3)=72

    Sub3 s3;

    // s3.Sub1::d1=3.14;
    // s3.Sub2::d1=3.15;
    s3.d1 = 3.14;
}
