/**
 * @file 4_SFINAE_is_class.cpp
 * @brief SFINAE (Substitution Failure Is Not An Error) 机制:
 *     通过强弱类型绑定来判断是否是类类型，如果是类类型，返回true，否则返回false
 *     std::is_class<T>::value 用于判断是否是类类型, IsClassT<T>::Value 则是自定义的判断类类型的模板类
 * @author Albert
 * @version 1.0
 * @date 2025-02-09
 */
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class IsClassT
{
private:
    using One = char; // 1 byte
    using Tow = struct
    {
        char a[2];
    }; // 2byte

    // 模板函数不要求函数必须完整实现, 只要函数签名正确即可
    template <typename Ts>
    static One test(int Ts::*); // Ts支持::运算符，较强绑定类型; 传入的参数是一个指向类成员的指针，说明Ts是一个类类型

    template <typename Ts>
    static Tow test(...); // Ts不支持::运算符，较弱绑定类型
public:
    // 因为 union 类型也支持::运算符，所以需要排除 union 类型
    static constexpr bool Value = (sizeof(IsClassT<T>::test<T>(nullptr)) == 1) && !std::is_union_v<T>;
};

struct Point
{
};

enum class Color
{
    red,
    blue,
    green,
};

enum CColor
{
    red,
    blue,
    green,
};

union BigInt
{
    int data;
    long value;
    static int sdata; // 声明静态成员变量，因为不能在类进行定义
};
int BigInt::sdata = 100; // 定义静态成员变量

int main()
{
    cout << "union type :: test: " << BigInt::sdata << endl;
    cout << std::boolalpha;

    cout << IsClassT<int>::Value << endl;
    cout << IsClassT<string>::Value << endl;
    cout << IsClassT<Point>::Value << endl;
    cout << IsClassT<Color>::Value << endl;
    cout << IsClassT<CColor>::Value << endl;
    cout << IsClassT<BigInt>::Value << endl;

    cout << endl;

    cout << std::is_class<int>::value << endl;
    cout << std::is_class<string>::value << endl;
    cout << std::is_class_v<Point> << endl;
    cout << std::is_class_v<Color> << endl;
    cout << std::is_class_v<CColor> << endl;
    cout << std::is_class_v<BigInt> << endl;

    cout << endl;
}
