/**
 * @file 20_ref_param.cpp
 * @brief std::is_reference_v<T> 判断类型是否是引用类型
 * @author Albert
 * @version 1.0
 * @date 2025-01-23
 */
#include <iostream>

template <typename T>
void process(T)
{
    std::cout << "T is reference: " << std::is_reference_v<T> << '\n';
}

template <typename T>
void processR(T &)
{
    std::cout << "T is reference: " << std::is_reference_v<T &> << '\n';
}

int main()
{
    std::cout << std::boolalpha;
    int i;
    int & r = i;
    process(i);        // false
    process(r);        // false
    process<int &>(i); // true
    process<int &>(r); // true

    processR(i);        // int & => int &, true
    processR(r);        // int & => int &, true
    processR<int &>(i); // int& & => int&, true
    processR<int &>(r); // int& & => int&, true
}
