/**
 * @file 3_lambda_capture.cpp
 * @brief [=] 表示所有的都是值捕获，
 *        [&] 表示所有的都是引用捕获，
 *        [&x] 表示引用捕获 x 变量，
 *        [x] 表示值捕获 x 变量，
 *        [=, &x] 表示默认都是通过值捕获，但是 x 是引用捕获
 *        [&, x] 表示默认都是通过引用捕获，但是 x 是值捕获
 *        mutable 关键字用于允许 lambda 表达式在其主体内修改捕获的变量, 允许修改值捕获的变量;
 *        通过使用 mutable 关键字，你可以在 lambda 表达式内部安全地修改捕获的变量，而不会影响原始变量的值;
 * @author Albert
 * @version 1.0
 * @date 2025-01-01
 */

#include <iostream>
#include <vector>

using namespace std;

class Point
{
public:
    double x;
    double y;
    void print() const
    {
        std::cout << x << ", " << y << endl;
        ;
    }
};

/*
// [&] 等价于对应的函数对象
struct Lambda_Ref{

    Point& p1; // a pointer store sapce: 8byte
    Point& p2; // 8byte

    Lambda_Ref( Point& p1, Point& p2):p1(p1),p2(p2)
    {

    }
    void operator()(int n) {
        p1.x+=n;
        p1.y+=n;
        p2.x+=n;
        p2.y+=n;
    }
};*/

/*
// [=] 等价于对应的函数对象
struct Lambda_Value{

    Point p1;
    Point p2;

    Lambda_Value(const Point& p1, const Point& p2):p1(p1),p2(p2)
    {

    }
    void operator()(int n) {
        p1.x+=n;
        p1.y+=n;
        p2.x+=n;
        p2.y+=n;

        p1.print();
        p2.print();

        number++;
    }
};
*/

int number = 100;

int main()
{
    Point p1{ 10, 20 };
    Point p2{ 100, 200 };

    // use value gets
    auto lambda1 = [=](int n) mutable // Lambda_Value lambda1(p1,p2);
    {
        p1.x += n;
        p1.y += n;
        p2.x += n;
        p2.y += n;
        p1.print();
        p2.print();

        number++;
    };

    {
        cout << "lambda1------------" << endl;
        lambda1(10);
        lambda1(10);
        p1.print();
        p2.print();
        cout << sizeof(lambda1) << endl;
        cout << sizeof(Point) << endl;
        cout << number << endl;
    }

    // use refercence gets
    auto lambda2 = [&](int n) {
        p1.print();
        p2.print();
        p1.x += n;
        p1.y += n;
        p2.x += n;
        p2.y += n;

        number++;
    };

    // Lambda_Ref lambda2(p1,p2);
    {
        cout << "lambda2------------" << endl;
        lambda2(100);

        p1.print();
        p2.print();

        p1.x += 5;
        p1.y += 5;
        p2.x += 5;
        p2.y += 5;
        lambda2(100);
    }

    cout << sizeof(lambda2) << endl;
    cout << number << endl;

    cout << "lambda3------------" << endl;
    // default use 值捕获，p1 是引用捕获
    auto lambda3 = [=, &p1]() {
        p1.print();
        p1.x++;
        p1.y++;
        p2.print();
    };
    lambda3();
    p1.print();

    cout << "lambda4------------" << endl;
    /* default use 引用捕获，p1 值捕获 */
    auto lambda4 = [&, p1]() {
        p1.print();
        p2.x++;
        p2.y++;
    };
    lambda4();
    p2.print();

    cout << "lambda5------------" << endl;
    // p2 是值捕获
    auto lambda5 = [p2]() { p2.print(); };
    lambda5();

    cout << "lambda6------------" << endl;
    // p1 是引用捕获
    auto lambda6 = [&p1]() {
        p1.x++;
        p1.y++;
    };
    lambda6();
    p1.print();

    cout << "lambda7------------" << endl;
    // 值捕获 p1，引用捕获 p2
    auto lambda7 = [p1, &p2]() {
        p2.print();
        p2.x = p1.x;
        p2.y = p1.y;
    };
    lambda7();
    p2.print();

    cout << sizeof(lambda7) << endl;
}
