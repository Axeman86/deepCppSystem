/**
 * @file 2_lambda_intro.cpp
 * @brief introl: Lambda expression 在 STL 算法中的应用, example: for each, find_if, sort, count_if
 * @author Albert
 * @version 1.0
 * @date 2025-01-01
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> v)
{
    for_each(v.begin(), v.end(), [](int i) { std::cout << i << " "; });
    cout << endl;
}

// []() -> void { return true; } 无捕获，无参数，无返回值 Lambda 等价于对应的函数对象
// struct Lambda{
//  Lambda() = default;
// 	void operator()() noexcept
// 	{
// 	}
// };

int main()
{
    // 无捕获，无参数，无返回值 Lambda
    auto l1 = []() -> void { cout << "Hello, easy Lambda!" << endl; };
    l1();

    vector<int> v{ 8, 4, 5, 10, 2, 11, 18 };
    print(v);

    // 查找大于10的元素，并返回 iterator
    auto p = find_if(v.begin(), v.end(), [](int i) { return i >= 10; });
    for (auto i = p; i != v.end(); i++)
        cout << *i << " ";
    cout << endl;

    // 排序从大到小
    sort(v.begin(), v.end(), [](const int & a, const int & b) -> bool { return a > b; });
    print(v);

    // 查找大于等于7的元素，并返回 number
    int number = count_if(v.begin(), v.end(), [](int a) { return (a >= 7); });
    cout << number << endl;

    auto p1 = find_if(v.begin(), v.end(), [](int a) { return (a <= 7); });
    for (auto i = p1; i != v.end(); i++)
        cout << *i << " ";
    cout << endl;
}
