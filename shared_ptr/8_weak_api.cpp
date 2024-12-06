/**
 * @file 8_weak_api.cpp
 * @brief weak_ptr API 使用, 检查 weak_ptr 是否已经销毁;
 *        wptr.use_count() 返回关联的 std::shared_ptr 的引用计数, 如果关联的 std::shared_ptr 已经被销毁, 返回 0;
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-03
 */
#include <iostream>
#include <memory>

using namespace std;

struct Widget
{
    int data;
    Widget(int d) : data(d) { cout << "ctor" << endl; }
    ~Widget() { cout << "dtor" << endl; }
};

weak_ptr<Widget> wptr;

void check()
{
    cout << "wptr 引用计数 " << wptr.use_count() << endl;

    if (!wptr.expired())
    {
        // 当你调用 wptr.lock() 时，它会尝试获取一个 std::shared_ptr，如果底层对象仍然存在，则返回一个新的
        // std::shared_ptr，并增加引用计数; 如果底层对象已经被销毁，则返回一个空的 std::shared_ptr;
        shared_ptr<Widget> sptr = wptr.lock(); // Geted shared_ptr from weak_ptr

        cout << "wptr 引用计数 " << wptr.use_count() << endl;
        cout << "sptr 引用计数 " << sptr.use_count() << endl;

        cout << "当前值 " << sptr->data << '\n';
    }
    else
    {
        cout << "wptr 已销毁\n";
    }

    cout << "wptr 引用计数 " << wptr.use_count() << endl;
}
int main()
{
    {
        shared_ptr<Widget> s = make_shared<Widget>(42);
        wptr                 = s;
        cout << "s reforence count " << s.use_count() << endl;
        check();
    } // s 销毁
    cout << "s销毁后......" << endl;
    check();
}
