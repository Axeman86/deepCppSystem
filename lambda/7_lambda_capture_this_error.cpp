/**
 * @file 7_lambda_capture_this_error.cpp
 * @brief 以值捕获 this 指针，相当于[this]，实际是以传值的方式捕获 this 指针，效果等同于传引用捕获;
 *        使用函数包装器返回 lambda 表达式，虽然能执行函数，但是由于 this 指针失效，导致未定义行为
 * @author Albert
 * @version 1.0
 * @date 2025-01-03
 */
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

struct TCPSession
{
    int data;

    TCPSession(int d) : data(d) {}

    TCPSession(const TCPSession & rhs) : data(rhs.data) { cout << "TCPSession copy ctor" << endl; }

    ~TCPSession() { cout << "~TCPSession" << endl; }

    void process() const { cout << "process:" << data << endl; }

    auto getLambda()
    {
        auto lam = [this]() {
            data++;
            process();
        };
        return lam;
    }
};

// 返回函数包装器类型
// 它可以存储、复制和调用任何可调用的目标（如普通函数、lambda 表达式、绑定表达式或其他函数对象）
std::function<void(void)> process()
{
    TCPSession tsObj(100);
    // lambda 的生命周期跟 tsObj 一样长
    auto lambda = tsObj.getLambda(); // => getLambda(&tsObj)

    lambda();

    return lambda;
}

int main()
{
    // 不同的作用域, 使用函数包装器
    std::function<void(void)> func = process();
    // process:-1096742287 未初始化的值, 由于 this 指针失效
    func();
}
