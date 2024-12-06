/**
 * @file 10_this_share_error.cpp
 * @brief shared_ptr 不能直接初始化 this 指针, 会导致 double free;
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-04
 */
#include <iostream>
#include <memory>

using namespace std;

class Widget
{
public:
    shared_ptr<Widget> getWidget() { return shared_ptr<Widget>(this); }
};

// shared_ptr<Widget> getWidget(Widget * this)
// {
//         return shared_ptr<Widget>(this);  //
// }

int main()
{
    {
        /* double free */
        Widget * p = new Widget();

        shared_ptr<Widget> pw{ p };

        // shared_ptr<Widget> s=pw->getWidget(); // shared_ptr<Widget> s= getWidget{p}; =>shared_ptr<Widget>{p}
        shared_ptr<Widget> s{ p };
    }
    cout << "------------------" << endl;

    {
        /* double free */
        Widget * pw          = new Widget();
        shared_ptr<Widget> s = pw->getWidget();
        delete pw;
    }
    cout << "------------------" << endl;

    {
        /* double free */
        Widget w;
        shared_ptr<Widget> s = w.getWidget(); // getWidget(&w);
    }
    cout << "------------------" << endl;

    {
        /* double free */
        shared_ptr<Widget> sw = make_shared<Widget>();
        shared_ptr<Widget> s  = sw->getWidget(); // getWidget(sw.get());
    }
    cout << "------------------" << endl;
}
