/**
 * @file 3_optional.cpp
 * @brief optional<T> 测试用例代码
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
        return "C++ Language";
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
    if (optional<string> str = create1(true))
    {
        cout << "sizeof(str) : " << sizeof(str) << endl;
        cout << *str << endl;
    }

    cout << "sizeof(string) : " << sizeof(string) << endl;
    optional<string> value = create2(false);
    cout << "sizeof(optional<string>) : " << sizeof(optional<string>) << endl;
    cout << value.value_or("default") << endl;

    if (auto str = create_ref(true))
    {
        cout << str->get() << endl;
        str->get() = "Carbon";
        cout << str->get() << endl;
    }
}
