/**
 * @file 17_std_function_invoke.cpp
 * @brief std::function VS std::invoke use;
 *    std::invoke 提供了一个统一的调用语法，可以调用任何可调用对象:
 *        包括函数对象、函数指针、成员函数、成员函数指针、lambda表达式、std::function 等
 * @author Albert
 * @version 1.0
 * @date 2025-01-21
 */
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class MyClass
{
public:
    int value;

    void process(int data)
    {
        cout << "MyClass process: " << data << endl;

        value += data;
    }

    static void sprocess(int data) { cout << "MyClass static process: " << data << endl; }
};

void process(int data)
{
    cout << "process function pointer: " << data << endl;
}

struct Processor
{
    void operator()(int data) const { cout << "Processor Functor: " << data << endl; }
};
/*
 * args is && type, so it forward the args to op
 * template <typename Callable, typename... Args>
 * decltype(auto) invoke(Callable && op, Args &&... args);
 * */
int main()
{
    MyClass mc{ 100 };

    cout << "std::invoke---------" << endl;
    {
        std::invoke(process, 10);
        std::invoke(Processor{}, 20);
        cout << mc.value << endl;
        std::invoke(&MyClass::process, &mc, 30); // mc.print(30); ==> MyClass::print(&mc, 30);
        cout << mc.value << endl;
        std::invoke(&MyClass::process, mc, 30);
        cout << mc.value << endl;
        std::invoke(&MyClass::sprocess, 40);
        std::invoke([](int data) { cout << "lambda:" << data << endl; }, 50);
    }

    cout << "std::function---------" << endl;
    {
        std::function func1 = process;
        func1(100);

        std::function func2 = Processor{};
        func2(200);
        cout << mc.value << endl;

        // func3_1 is callable, but can not be member variable
        std::function<void(MyClass, int)> func3_1 = &MyClass::process;
        func3_1(mc, 300);
        cout << mc.value << endl;

        std::function<void(MyClass &, int)> func3_2 = &MyClass::process;
        func3_2(mc, 300);
        cout << mc.value << endl;

        std::function<void(MyClass *, int)> func3_3 = &MyClass::process;
        func3_3(&mc, 300);
        cout << mc.value << endl;

        std::function func4 = &MyClass::sprocess;
        func4(400);
        cout << mc.value << endl;

        std::function func5 = [](int data) { cout << "lambda:" << data << endl; };
        func5(500);
        std::invoke(func5, 500);

        // mc.process(10); // process(&mc, 10);
    }
}
