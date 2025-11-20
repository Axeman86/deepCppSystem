
/**
 * @file 8_scopeguard.cpp
 * @brief ScopeGuard is RAII (Resource Acquisition Is Initialization)
 *        资源获取即初始化的一种实现，用于资源管理，确保资源在作用域结束时被释放，避免资源泄漏。
 *        ScopeGuard 通过在构造函数中接受一个函数对象，然后在析构函数中调用该函数对象来实现资源的释放。
 *        ScopeGuard 还提供了一个 dismiss() 方法，用于在作用域结束时不释放资源。
 *        ScopeGuard 通过在作用域结束时调用析构函数来实现资源的释放，因此不需要手动释放资源，避免了忘记释放资源的问题。
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-22
 */
#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

template <typename F>
class ScopeGuard final
{
public:
    explicit ScopeGuard(F && f) : m_func(std::move(f)), m_dismiss(false) { cout << "ScopeGuard(F &&)" << endl; }

    explicit ScopeGuard(const F & f) : m_func(f), m_dismiss(false) { cout << "ScopeGuard(const F &)" << endl; }

    ~ScopeGuard()
    {
        cout << "~ScopeGuard()" << endl;
        if (!m_dismiss)
            m_func();
    }

    ScopeGuard(ScopeGuard && rhs) : m_func(std::move(rhs.m_func)), m_dismiss(rhs.m_dismiss)
    {
        cout << "ScopeGuard(ScopeGuard &&)" << endl;
        rhs.dismiss();
    }

    ScopeGuard()                               = delete;
    ScopeGuard(const ScopeGuard &)             = delete;
    ScopeGuard & operator=(const ScopeGuard &) = delete;

    void dismiss() { m_dismiss = true; }

private:
    F m_func;
    bool m_dismiss;
};

void invoke(int data)
{
    if (data < 0)
    {
        invalid_argument exp("data"); // 创建参数错误异常对象
        throw exp;
    }
}

void file_process()
{
    FILE * fp = fopen("filename", "wb");
    cout << "打开文件...." << endl;

    /* automatic type_info */
    ScopeGuard scopeguard([&]() {
        fclose(fp);
        cout << "确保关闭文件" << endl;
    });

    cout << "处理文件...." << endl;

    invoke(-100);

    // 关闭文件
    //   fclose(fp);
    //   cout<<"关闭文件"<<endl;
}

void stack_process()
{
    {
        stack<string> cityStack;

        cityStack.push("Shanghai"s);
        ScopeGuard scopeGuard{ [&] {
            string s = cityStack.top();
            cityStack.pop();
            cout << "roll back: " << s << endl;
        } };

        cout << "invoke..." << endl;
        invoke(-100);

        scopeGuard.dismiss();
    }
}

int main()
{

    try
    {
        file_process();

        /* stack_process(); */

    } catch (invalid_argument & e)
    {
        cerr << "invalid arg: " << e.what() << endl;
    }
}
