/**
 * @file 16_forward_param.cpp
 * @brief 构造函数的参数实现完美转发后可以衍生出多个组合的不同参数的类型组合的构造函数测试用例
 * @author Albert
 * @version 1.0.0
 * @date 2024-10-26
 */
#include <iostream>
#include <vector>
using namespace std;

/*
class Widget {
public:

        Widget(string& n, vector<int>& c):
        name(n), coordinates(c)
    {}

    Widget(string&& n, vector<int>&& c):
        name(std::move(n)),
        coordinates(std::move(c))
    {

    }

    Widget(string& n, vector<int>&& c):
        name(n),
        coordinates(std::move(c))
    {

    }

    Widget(string&& n, vector<int>& c):
        name(std::move(n)),
        coordinates(c)
    {

    }
private:
        std::string name;
        std::vector<int> coordinates;
};
*/

/*
 * 上面的 class Widget contructor functions, 可以使用下面的这一个构造函数来替代, 使用参数的完美转发。
 * */
class Widget
{
public:
    template <typename T1, typename T2>
    Widget(T1 && n, T2 && c) // n 和 c可以绑定任何值
        :
        name(std::forward<T1>(n)),       // 将 n 转发给string构造
        coordinates(std::forward<T2>(c)) // 将 c 转发给vector构造
    {}

    void print()
    {
        cout << "Name is " << name << endl;
        cout << "coordinates is capacity:" << coordinates.capacity() << ", size:" << coordinates.size() << endl;
    }

private:
    std::string name;
    std::vector<int> coordinates;
};

int main()
{
    Widget w{ "Hello"s, vector<int>(5) };
    w.print();
    return 0;
}
