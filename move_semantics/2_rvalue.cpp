/*
 *     Copyright (c) 2021-2022 Project CHIP Authors
 *     Copyright (c) 2019 Google LLC.
 *     All rights reserved.
 *
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */
#include <iostream>
#include <numeric>
using namespace std;

void process(int && data);
void process(int & data);

void process(int && data)
{
    cout << "right value ref:" << &data << "," << data << endl;
    cout << "&data value : " << *reinterpret_cast<int *>(&data) << endl;
    process(data);
}

void process(int & data)
{
    cout << "left value ref:" << data << endl;
}

int main()
{
    int x = 100;
    int y = 200;
    cout << "&x = " << &x << endl;
    cout << "&y = " << &y << endl;
    cout << "-----" << endl;

    process(x);   /// left
    process(100); /// right
    cout << "-----" << endl;

    // ++x（前置自增）
    // 行为：首先将 x 的值增加 1，然后返回增加后的值。
    // 返回值：返回增加后的值。
    // 左值/右值：++x 是一个左值，因为它返回的是变量 x 本身。
    process(++x); /// left
    // x++（后置自增）
    // 行为：首先返回 x 的当前值，然后将 x 的值增加 1。
    // 返回值：返回增加前的值。
    // 左值/右值：x++ 是一个右值，因为它返回的是一个临时值，而不是变量 x 本身。
    process(x++); //// right

    // 左值和右值的判断:
    // 左值（Lvalue）：表示一个对象的内存位置，可以出现在赋值操作符的左侧。++x 是一个左值，因为它返回的是变量 x 本身，可以被赋值。
    // 右值（Rvalue）：表示一个对象的值，不能出现在赋值操作符的左侧。x++ 是一个右值，因为它返回的是一个临时值，不能被赋值。
    // int *px = &(x++); // Error
    // x++ = 10; // Error：expression is not assignable
    cout << "-----" << *(&(++x)) << endl;

    process(x = 300); /// left
    process(x + y);   /// right
    cout << "-----" << endl;

    auto s1 = "hello";
    auto s2 = "hello"s;

    // invoke(s1);
    // invoke(s2);
    // invoke("hello");
    // invoke("hello"s);

    auto * p1 = &("hello");
    cout << p1 << endl;

    //  auto *p2=&("hello"s);
    //  cout<<p2<<endl;
}
