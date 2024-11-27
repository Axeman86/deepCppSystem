/**
 * @file 9_unique_factory.cpp
 * @brief unique_ptr的工厂函数的使用方法, 返回值优化, 避免了拷贝构造函数的调用, 但是会调用移动构造函数,
 *          但是移动构造函数的效率要高于拷贝构造函数, 但是在某些情况下, 可能会有性能损失,
 *          例如: 有资源的类, 拷贝构造函数的代价很高, 但是移动构造函数的代价很低, 这时候, 返回值优化就会有性能损失
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-25
 */
#include <iostream>
#include <memory>

using namespace std;

class Widget
{
public:
    Widget() { cout << "ctor" << endl; }
    ~Widget() { cout << "dtor" << endl; }

    Widget(const Widget & rhs) { cout << "copy ctor" << endl; }
    Widget(Widget && rhs) { cout << "move ctor" << endl; }

    Widget & operator=(Widget && rhs)
    {
        cout << "move assignment" << endl;
        return *this;
    }
    Widget & operator=(const Widget & rhs)
    {
        cout << "copy assignment" << endl;
        return *this;
    }
};

// Widget& createWidget(){

//     Widget* w=new Widget();
//     //....

//     return *w;
// }

// Widget createWidget(){

//     SubWidget w;
//     //....

//     return w;
// }

// Widget* createWidget(){

//     Widget* pw=new Widget();
//     //....

//     return pw;
// }

/* return value optimization */
unique_ptr<Widget> createWidget()
{
    unique_ptr<Widget> upw = make_unique<Widget>();
    //....

    return upw;
}

int main()
{
    unique_ptr<Widget> upw2 = createWidget();
}
