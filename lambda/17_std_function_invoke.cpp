/**
 * @file 17_std_function_invoke.cpp
 * @brief std::function VS std::invoke use;
 *    std::invoke 提供了一个统一的调用语法，可以调用任何可调用对象:
 *        包括函数对象、函数指针、成员函数、成员函数指针、lambda表达式、std::function 等
 1. **function**
   - 定义和实现一段可复用的逻辑。
   - 适用于需要多次调用、具名、可组合的操作。
   - 例子：
     ```cpp
     int add(int a, int b) { return a + b; }
     ```

2. **invoke**
   - 通常指“调用”某个可调用对象（函数、lambda、成员函数等）。
   - 在 C++ 中，`std::invoke` 可以统一调用普通函数、成员函数指针、函数对象等。
   - 适用于泛型编程、需要统一调用接口的场景。
   - 例子：
     ```cpp
     std::invoke(add, 1, 2); // 调用函数
     std::invoke(&MyClass::method, obj, arg); // 调用成员函数
     ```

**选择建议：**
- 需要定义逻辑时用 `function`（或函数/方法）。
- 需要“以统一方式调用各种可调用对象”时用 `invoke`，比如模板、回调、事件分发等场景。

简言之：
- `function` 负责“定义”；
- `invoke` 负责“调用”，尤其在泛型和多态调用时更有用。

 * @author Albert
 * @version 1.0
 * @date 2025-01-21
 */
#include <functional>
#include <iostream>

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
