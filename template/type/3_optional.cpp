/**
 * @file 3_optional.cpp
 * @brief optional<T> 是 C++17 引入的一个模板类，用于表示一个可能包含或不包含值的对象;
 *        它提供了一种类型安全的方式来处理可能为空的值，而不需要使用指针或特殊的标志值。
 *        类型安全： std::optional<T> 提供了一种类型安全的方式来表示一个值可能不存在的情况，而不需要使用指针或特殊的标志值。
 *        简洁的接口： std::optional<T> 提供了一些简洁的接口来检查和访问其包含的值。
 *        避免未初始化变量： 使用 std::optional<T> 可以避免未初始化变量的使用，因为它明确地表示一个值可能不存在。
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-27
 */
#include <functional>
#include <iostream>
#include <optional>
#include <string>

using namespace std;

optional<string> create1(bool flag)
{
    if (flag)
    {
        return make_optional("C++ Language");
        // return "C++ Language";
    }
    return {};
}

auto create2(bool flag)
{
    return flag ? optional<string>{ "C Language" } : nullopt;
}

auto create_ref(bool flag)
{
    static string value = "Rust Language";
    return flag ? optional<reference_wrapper<string>>{ value } : nullopt;
}

int main()
{
    {
        optional<string> str = create1(true);
        if (str.has_value())
        {
            cout << "sizeof(str) : " << sizeof(str) << endl;
            cout << "Value found: " << str.value() << endl;
        }
        else
        {
            cout << "No value found!" << endl;
        }
        cout << "sizeof(string) : " << sizeof(string) << endl;
    }

    cout << "-----------------" << endl;
    if (auto str = create_ref(true))
    {
        cout << str->get() << endl;
        str->get() = "Carbon";
        cout << str->get() << endl;
    }

    cout << "-----------------" << endl;
    {
        optional<string> value = create2(false);
        if (value)
        {
            cout << "sizeof(value) : " << sizeof(value) << endl;
            cout << "Value found: " << *value << endl;
        }
        else
        {
            cout << "Value has not found!" << endl;
        }
        cout << "sizeof(optional<string>) : " << sizeof(optional<string>) << endl;
        cout << "value_or :" << value.value_or("default") << endl;
    }
}
