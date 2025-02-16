/**
 * @file 3_constexpr3.cpp
 * @brief 区分编译时常量和运行时常量字符串, 以及 constexpr function 的使用
 *   const char * s = "hello";           // s 是运行时常量
 *   const char s[] = "hello";           // s 是运行时常量, 虽然字符串内容在编译时是已知的，但数组 s 的存储位置是在运行时分配的
 *   constexpr char * s = "hello";       // s 是编译时常量
 *   constexpr auto s = "hello";         // s 是编译时常量, auto 会自动推导为 const char *
 *   constexpr char s[] = "hello";       // s 是编译时常量
 *
 *   constexpr std::string my_string = "Hello, world!"; // c++20 string is a literal type
 *   constexpr std::string_view my_string = "Hello, world!"; // c++17 string_view is a literal type
 *
 *   constexpr function, 如果结果要求为编译期常量：
 *     1. 传参为编译期常量，函数可以正常得到编译期常量值
 *     2. 传参为运行期常量，函数只能是报错处理
 *
 *   constexpr function, 如果结果要求为运行期变量：
 *     1. 传参传递可以是运行期变量，也可以是编译期常量
 *     2. 允许运行期合法的目的仅仅是为了避免多份重载版本
 *
 * @author Albert
 * @version 1.0
 * @date 2025-02-16
 */
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace std;

//可支持编译期、也可支持运行时
constexpr bool isPrime(unsigned int p)
{
    // cout<<"hello"<<endl;
    for (unsigned int d = 2; d <= p / 2; ++d)
    {
        if (p % d == 0)
        {
            return false;
        }
    }

    return p > 1;
}

using CCharArray = const char[6];

constexpr int getLen(const char * text)
{
    int i = 0;

    while (text[i] != '\0')
    {
        i++;
    }

    return i;
}

// string type is not a literal type, so it can't be used in a constexpr
// c++20 string is a literal type, so it can be used in a constexpr
constexpr int getLen(string text)
{
    int i = 0;

    while (text[i] != '\0')
    {
        i++;
    }

    return i;
}

constexpr int getLen(string_view text)
{
    return text.length();
}

int main()
{
    {
        int data = 100;
        bool b1  = isPrime(data);
        cout << boolalpha << b1 << endl;
        // static_assert(b1, "Compile time error"); // if b1 is false, then compile error
        constexpr bool b2 = isPrime(197);
        static_assert(b2, "Compile time error");
        cout << boolalpha << b2 << endl;
    }

    {
        /* constexpr function, 如果结果要求为编译期常量：
         *   1. 传参为编译期常量，函数可以正常得到编译期常量值
         *   2. 传参为运行期常量，函数只能是报错处理
         */
        cout << "getLen() arguments are runtime constants" << endl;
        const char s1[] = "hello";
        // static_assert(getLen(s1) == 5, "Compile time error: Length of s1 is not 5");
        // constexpr int len1 = getLen(s1);  // error: call to non-constexpr function 'int getLen(const char*)'
        // 输出结果为运行期变量，因为 cout 是运行期函数
        cout << "getLen(s1) : " << getLen(s1) << endl;

        const char * s2 = "hello";
        // static_assert(getLen(s2) == 5, "Compile time error: Length of s2 is not 5");
        // 输出结果为运行期变量，因为 cout 是运行期函数
        cout << "getLen(s2) : " << getLen(s2) << endl;
    }
    {
        cout << "getLen() arguments are compile time constants" << endl;
        constexpr char str[] = "Hello, world!";
        constexpr int len    = getLen(str);
        static_assert(len == 13, "Compile time error");
        cout << "getLen(str) : " << len << endl;

        constexpr const char * s = "helloworld";
        static_assert(s[0] == 'h', "Compile time error");
        cout << "getLen(s) : " << getLen(s) << endl;
    }

    {
        // constexpr auto s2 = "hello"; 定义了一个指向字符串字面量 "hello" 的指针。
        // s2 的值在编译时是已知的，因此它是一个编译时常量。
        // 字符串 "hello" 的内容是在静态存储区分配的，并在运行时访问。
        // => constexpr char * s2 = "hello";
        constexpr auto s2 = "hello";
        static_assert(s2[0] == 'h', "Compile time error");
        constexpr int len2 = getLen(s2);
        static_assert(len2 == 5, "Compile time error");
        cout << "getLen2(s2) : " << len2 << endl;
    }

    {
        constexpr std::string_view my_string = "Hello, world!";
        static_assert(my_string == "Hello, world!", "Compile time error");
        constexpr int len3 = getLen(my_string);
        cout << "getLen3(my_string) : " << len3 << endl;
    }
}
