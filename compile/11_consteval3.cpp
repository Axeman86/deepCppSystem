/**
 * @file 11_consteval3.cpp
 * @brief lambda 函数使用 consteval 关键字，编译时计算哈希值，返回值必须在编译时确定
 * @author Albert
 * @version 1.0
 * @date 2025-02-18
 */
#include <array>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

int main()
{
    auto hashed = [](const char * str) consteval
    {
        std::size_t hash = 5381;
        while (*str != '\0')
        {
            hash = hash * 33 ^ *str++;
        }
        return hash;
    };

    // 编译时上下文
    std::array arr{ hashed("beer"), hashed("wine"), hashed("water") };

    cout << arr[0] << endl;
    cout << arr[1] << endl;
    cout << arr[2] << endl;
}
