/**
 * @file 10_lambda_generic.cpp
 * @brief 使用泛型 lambda 表达式，实现通用的比较函数对象，支持不同类型的比较操作，如整型、浮点型、字符串等
 * @author Albert
 * @version 1.0
 * @date 2025-01-04
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    auto compareLam = [](auto x, auto y) -> bool { return x < y; };
    auto printLam   = [](auto item) { cout << item << " "; };

    vector v1 = { 7, 2, 8, 4, 3 };
    sort(v1.begin(), v1.end(), compareLam);
    for_each(v1.begin(), v1.end(), printLam);

    cout << endl;

    vector<string> v2 = { "Python"s, "C"s, "Java"s, "C++"s, "GO"s, "Rust"s };

    sort(v2.begin(), v2.end(), compareLam);
    for_each(v2.begin(), v2.end(), printLam);
    cout << endl;

    int d1    = 234;
    double d2 = 342.24;
    cout << std::boolalpha << compareLam(d1, d2) << endl;
    cout << std::boolalpha << compareLam(d2, d1) << endl;
}
