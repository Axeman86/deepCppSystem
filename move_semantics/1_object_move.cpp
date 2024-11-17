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
#include <vector>
using namespace std;

struct Point
{
    int x;
    int y;
};

struct Widget
{
    int value;
    Point * data;

    Widget(int _value = 0, int _x = 0, int _y = 0) : value(_value), data(new Point{ _x, _y })
    {
        cout << __FUNCTION__ << " ctor" << endl;
    }

    Widget(const Widget & rhs) : value(rhs.value), data(new Point(*rhs.data)) { cout << __FUNCTION__ << " copy ctor" << endl; }

    Widget & operator=(const Widget & rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        /* copy && swap */
        Widget temp(rhs);
        swap(value, temp.value);
        swap(data, temp.data);

        cout << __FUNCTION__ << " copy assignment" << endl;
        return *this;
    }

    ~Widget()
    {
        cout << __FUNCTION__ << " dtor :" << data << endl;
        delete data;
    }

    //移动构造函数
    Widget(Widget && rhs) noexcept : value(rhs.value), data(rhs.data) // 1. 窃取源对象的指针值
    {
        rhs.data = nullptr; // 2. 将源对象的值设为有效状态
        cout << __FUNCTION__ << " move ctor" << endl;
    }

    //移动赋值函数
    Widget & operator=(Widget && rhs) noexcept
    {
        /* rvalue reference is a reference, not is a pointer */
        if (this == &rhs)
        {
            return *this;
        }
#if 0
        value = rhs.value;

        delete this->data;     // 1. 删除当前值
        this->data = rhs.data; // 2. 窃取源对象的值
        rhs.data   = nullptr;  // 3. 将源对象的值设为有效状态
#else
        /* Use copy && swap mode */
        Widget tmp{ std::move(rhs) };
        swap(this->value, rhs.value);
        swap(this->data, rhs.data);
#endif
        cout << __FUNCTION__ << " move assignment" << endl;
        return *this;
    }

    void process() { cout << value << ": [" << data->x << "," << data->y << "]" << endl; }
};

Widget createWidget()
{
    Widget w(1, 10, 20);
    return w;
}

vector<Widget> getData()
{
    // initialize 10 Widget for capacity
    vector<Widget> vec(10);
    return vec;
}

int main()
{
    cout << "-------1st------" << endl;
    {
        Widget w1{ 1, 10, 20 };
        Widget w2{ 2, 100, 200 };
        w1 = w2;
    }

    cout << "-------2nd------" << endl;
    {
        Widget w{ 3, 1000, 2000 };
        w = createWidget(); // 移动赋值
    }

    cout << "\n-------3rd-------" << endl;
    {
        vector<Widget> v;

        for (int i = 0; i < 10; i++)
        {
            // vector capacity is 2^n for performance
            cout << "---loop:" << i << "---capacity:" << v.capacity() << ", size:" << v.size() << endl;
            v.emplace_back(i, i * 10, i * 20);
        }
    }

    cout << "\n-------4th-------" << endl;
    {
        vector<Widget> v;
        v = getData();
    }
}
