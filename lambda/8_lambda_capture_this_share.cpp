/**
 * @file 8_lambda_capture_this_share.cpp
 * @brief 对于 lambda 表达式捕获 this 指针，可以使用 shared_from_this() 函数返回一个指向当前对象的弱引用的 shared_ptr 智能指针，
 *        从而避免 this 指针失效的问题
 * @author Albert
 * @version 1.0
 * @date 2025-01-04
 */
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

struct TCPSession : public enable_shared_from_this<TCPSession>
{
    int data;

    TCPSession(int d) : data(d) {}

    TCPSession(const TCPSession & rhs) : data(rhs.data) { cout << "TCPSession copy ctor" << endl; }

    void process() const { cout << "process:" << data << endl; }

    auto getLambda()
    {
        // shared_ptr<TCPSession> self=make_shared<TCPSession>(this);
        shared_ptr<TCPSession> self = shared_from_this();

        auto lam = [self]() {
            self->data++;
            self->process();

            cout << "引用计数：" << self.use_count() << endl;
        };

        //等价：
        // auto lam=[this,self]()
        // {
        //     this->data++;
        //     this->process();
        // };

        return lam;
    }

    ~TCPSession() { cout << "~TCPSession" << endl; }
};

std::function<void(void)> invoke()
{
    shared_ptr<TCPSession> tsObj = make_shared<TCPSession>(100);

    auto lambda = tsObj->getLambda();

    cout << "引用计数：" << tsObj.use_count() << endl;
    lambda();

    return lambda;
}

int main()
{
    std::function<void(void)> lamObj = invoke();

    lamObj();
}
