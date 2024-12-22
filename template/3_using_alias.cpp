/**
 * @file 3_using_alias.cpp
 * @brief using 的使用方式，来对类型进行重命令, 类型别名和模板别名
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-15
 */
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

// template<typename T, typename Alloca=alloctor<T>>
// vector;

//类型别名
using svector = vector<string>; //指定所有参数，完整类型

//模板别名
template <typename T>
using SmallVec = vector<T>; //指定部分参数，模板类型

void process()
{
    svector s{ "hello"s, "boolan"s, "cpp"s, "camp"s };
    for (auto & i : s)
        cout << i << " ";
    cout << endl;

    SmallVec<int> si{ 1, 2, 3, 4, 5 }; // vector<int, SmallAlloca<int>>;
    for (auto & i : si)
        cout << i << " ";
    cout << endl;
}

template <typename T>
class Array
{
private:
    T * ptr;
    int size;

public:
    using value_type = T;
    using iterator   = Array<T>;
};

/* <==> int data; */
Array<int>::value_type data;

int main()
{
    process();
    return 0;
}
