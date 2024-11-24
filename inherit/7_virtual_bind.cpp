#include <iostream>
using namespace std;

struct Base
{
    Base()
    {
        cout << "Base()" << endl;
        process(); //静态绑定
    }

    virtual ~Base()
    {
        cout << "~Base()" << endl;
        process(); //静态绑定
    }

    // 0x0023723880
    void invoke()
    {
        cout << "Base.invoke()" << endl;
        process(); //动态绑定, beacause process is virtual function called, type_info store object real type
        /* Base::process(); */
    }

    // 0x008234960
    virtual void process() { cout << "Base.process()" << endl; }
};

struct Sub : Base
{
    int data;

    Sub() : Base() { data = 100; }

    // 0x008234100
    void process() override
    {
        Base::process(); ////静态绑定 JMP 0x008234960
        cout << "Sub.process(): data = " << data << endl;
        data++;
    }

    // 0x002342160
    void invoke()
    { //隐藏
        cout << "Sub.invoke()" << endl;
    }

    ~Sub() { cout << "~Sub()" << endl; }
};

struct GrandSub : Sub
{
    void process() override { cout << "GrandSub.process()" << endl; }
};

int main()
{
    Base * pb1 = new Base();
    pb1->process(); //动态绑定 JMP *(pb1->vptr+2*8) 二次指针间接运算
    pb1->invoke();  //静态绑定 JMP 0x0023723880

    Sub * ps = new Sub();
    ps->process(); //动态绑定 JMP vfunc(p2) 二次指针间接运算
    ps->invoke();  //静态绑定 JMP 0x002342160

    Base * pb2 = ps;
    pb2->process(); //动态绑定 JMP vfunc(p2) 二次指针间接运算 0x008234100
    pb2->invoke();  //静态绑定 JMP 0x0023723880

    pb2->Base::process(); //虚函数静态绑定 JMP 0x008234960

    cout << "----------" << endl;
    Base & rb1 = *ps;
    rb1.process();
    rb1.invoke(); /* virture function static bind JMP 0x0023723880 */

    cout << "----------" << endl;
    delete pb1;
    delete pb2; //多态删除
}
