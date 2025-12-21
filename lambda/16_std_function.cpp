/**
 * @file 16_std_function.cpp
 * @brief std::function 是一个类模板，它是一个通用、多态的函数封装器
 *     std::function 函数包装器, 提供了一个通用的函数封装器, 可以用来包装任何可以调用的目标:
 *     (函数对象、lambda 表达式、函数指针、成员函数指针)
 *     std::function 使用了小对象优化技术(SOO), 即：小对象存储在栈，大对象存储在堆
 * @author Albert
 * @version 1.0
 * @date 2025-01-21
 */
#include <functional>
#include <iostream>
#include <string>

using namespace std;

struct Widget
{
    double x1 = 1;
    double x2;
    double x3;
    double x4;
    double x5;
    double x6;
    double x7;
    double x8;
};

void print(int no, string text)
{
    cout << "[" << no << "] " << text << endl;
}

using PrintPtr = void (*)(int, string);

// 全局函数
int fn_ptr(int x, int y)
{
    return x + y;
}

// 包含 2 个 int 成员的函数对象类型
struct PlusInts
{
    PlusInts(int m_, int n_) : m(m_), n(n_) { cout << "ctor" << endl; }

    PlusInts(const PlusInts & rhs) : m(rhs.m), n(rhs.n) { cout << "copy ctor" << endl; }

    ~PlusInts() { cout << "dtor" << endl; }

    int operator()(int x, int y) { return x + y + m + n; }

    int m;
    int n;
};

function<int(int, int)> process()
{
    // 使用 std::function 类型包装函数对象
    PlusInts plus(10, 20);

    std::function<int(int, int)> g = plus;

    return g;
}

int main()
{
    {
        PrintPtr p0                    = print;
        function<void(int, string)> p1 = print;
        p1(100, "C++");
        p1(200, "Design Patterns");

        function<void(int, string)> p2 = print;
        // 这是二个 function 对象，虽然它们包装了同一个函数，所以它们的地址是不一样的
        cout << boolalpha << (&p1 == &p2) << endl;
    }

    cout << "----" << endl;
    {
        PlusInts plus(10, 20);
        std::function<int(int, int)> g = plus;
        // sizeof(plus) == sizeof(PlusInts) == sizeof(int) * 2 bytes
        cout << "plus object size is " << sizeof(plus) << " bytes" << endl;
        /* function object size is 32 bytes */
        cout << "function object g size is " << sizeof(g) << " bytes" << endl;
    }

    cout << "----" << endl;
    {
        Widget w;
        /* lambda expret memory layout, 值捕获 Widget 对象
         * struct LambdaWiget
         * {
         *     LambdaWiget(Widget w) : w_(w) {}
         *     int operator()(int d1, int d2) const { return w_.x1 + d1 + d2; }
         *
         * private:
         *     Widget w_;
         * };
         */
        auto lambda = [=](int d1, int d2) -> int { return w.x1 + d1 + d2; };

        std::function h = lambda; // std::function<int(int, int)>
        cout << h(3, 4) << endl;
        cout << lambda(3, 4) << endl;
        cout << "lambda size is " << sizeof(lambda) << "bytes" << endl;
        cout << "function object h size is " << sizeof(h) << "bytes" << endl;

        std::function<int(int, int)> k;
        cout << "function object k size is " << sizeof(k) << "bytes" << endl;
    }
}
