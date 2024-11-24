#include <iostream>
using namespace std;

template <typename T>
class ScopeGuard final
{
public:
    ScopeGuard()                   = delete;
    ScopeGuard(const ScopeGuard &) = delete;
    ScopeGuard & operator=(const ScopeGuard &) = delete;
    explicit ScopeGuard(T && f) : m_func(f) { cout << "ScopeGuard(T &&): constructor" << endl; }
    explicit ScopeGuard(const T & f) : m_func(f) { cout << "ScopeGuard(const T&): constructor" << endl; }
    ~ScopeGuard()
    {
        if (!m_dismiss)
            m_func();
    }
    ScopeGuard(ScopeGuard && rhs) : m_func(move(rhs.m_func)), m_dismiss(rhs.m_dismiss)
    {
        cout << "ScopeGuard(ScopeGuard &&)" << endl;
        rhs.dismiss();
    }
    void dismiss() { m_dismiss = true; }

private:
    T m_func;
    bool m_dismiss = false;
};

class Base1
{
public:
    virtual Base1 * clone() = 0;

    virtual ~Base1() = default;
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

    Base1 * clone() override
    {
        return new Sub1(*this); // called Copy constructor functions

        /* return pb; */
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

    Base1 * clone() override
    {
        Sub2 * pb = new Sub2(*this); // called Copy constructor

        return pb;
    }
};

int main()
{
    Base1 * pb = new Sub2(100);
    cout << "================================" << endl;
    Base1 * pb2 = pb->clone();
    ScopeGuard sg([&]() {
        delete pb;
        delete pb2;
    });
}
