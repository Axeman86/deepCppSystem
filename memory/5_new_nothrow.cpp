/**
 * @file 5_new_nothrow.cpp
 * @brief 使用 new_handler 注册回调函数来处理内存分配失败的情况
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-11
 */
#include <iostream>
#include <new>
#include <vector>
using namespace std;

class Point
{
public:
    int x;
    int y;
    int z;
};

void new_handler1()
{
    cout << "Hello Kitty " << __FUNCTION__ << endl;
    abort();
}

int main()
{
    set_new_handler(new_handler1);
    try
    {
        for (;;)
        {
            int * p = new int[10000000000];
            if (nullptr == p)
            {
                cout << "apply memory faild !" << endl;
                break;
            }
        }
    } catch (bad_alloc)
    {
        cerr << "out of memory";
    }

    {
        for (;;)
        {
            int * p = new (nothrow) int[100000];
            if (p == nullptr)
            {
                cout << "apply memory faild !" << endl;
                break;
            }
        }
    }
}
