#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

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
        cout << boolalpha << (&p1 == &p2) << endl;
    }
    cout << "----" << endl;

    {
        PlusInts plus(10, 20);
        std::function<int(int, int)> g = plus;
        cout << "plus object size is " << sizeof(plus) << " bytes" << endl;
        /* function object size is 32 bytes */
        cout << "function object g size is " << sizeof(g) << " bytes" << endl;
    }
    cout << "----" << endl;

    {
        Widget w;
        /* lambda expret memory layout
         * struct lambdaWiget
         * {
         *     int operator()(int d1, int d2) { return x1 + d1 + d2; }
         *
         *     int x1 = 1;
         *     int x2;
         *     int x3;
         *     int x4;
         *     int x5;
         *     int x6;
         *     int x7;
         *     int x8;
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

        vector<std::function<int(int, int)>> vfunc;

        /// vector<decltype(lambda)> vlam;
    }
}
