#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class MyClass
{
public:
    MyClass()                  = default;
    ~MyClass()                 = default;
    MyClass(const MyClass & c) = default;
    MyClass & operator=(const MyClass & c) = default;
};

void process(MyClass c) {}

MyClass process()
{
    MyClass c;
    return c;
}

class Point
{
public:
    int x;
    int y;

    MyClass c;
};

class Rectangle
{
    Point * m_leftUp;
    int m_length;
    int m_width;

public:
    explicit Rectangle(int data) {}

    Rectangle(int x, int y, int length, int width) : m_leftUp(new Point{ x, y }), m_length(length), m_width(width) {}

    ~Rectangle() { delete m_leftUp; }

    Rectangle(const Rectangle & rect) : m_length{ rect.m_length }, m_width{ rect.m_width }
    {
        if (rect.m_leftUp != nullptr)
        {
            m_leftUp = new Point(*rect.m_leftUp);
        }
        else
        {
            m_leftUp = nullptr;
        }
        cout << "copy ctor" << endl;
    }

    /*
    Rectangle& operator=(const Rectangle& rect)
    {
        if(this== &rect){
            return *this;
        }

        this->m_length=rect.m_length;
        this->m_width=rect.m_width;

        if(rect.m_leftUp!=nullptr)
        {
            if(this->m_leftUp!=nullptr){
                *m_leftUp=*rect.m_leftUp;// Point assignment=
            }
            else{
                m_leftUp=new Point(*rect.m_leftUp);//Point copy ctor
            }
        }
        else
        {
            if(this->m_leftUp!=nullptr)
            {
                delete m_leftUp;
                m_leftUp=nullptr;
            }
        }
        cout<<"assignment= "<<endl;
        return *this;
    }*/

    // Copy & Swap
    Rectangle & operator=(const Rectangle & rect)
    {
        if (this == &rect)
        {
            return *this;
        }

        Rectangle temp{ rect }; // copy ctor

        // swap everyone data member
        swap(this->m_leftUp, temp.m_leftUp);
        swap(this->m_length, temp.m_length);
        swap(this->m_width, temp.m_width);

        cout << "assignment= " << endl;
        return *this;
    }

    inline friend ostream & operator<<(ostream & os, const Rectangle & rect);
};

ostream & operator<<(ostream & os, const Rectangle & rect)
{
    return os << "{" << rect.m_leftUp->x << "," << rect.m_leftUp->y << "," << rect.m_length << "," << rect.m_width << "}";
}

int main()
{
    Rectangle r1{ 10, 10, 30, 40 };

    Rectangle r2{ r1 }; // r2=r1; r2(r1);

    Rectangle r3{ 0, 0, 100, 200 };

    cout << r1 << endl;
    cout << r2 << endl;
    cout << r3 << endl;

    /// r1=r3;// r1.operator=(r3);
    r2 = r1 = r3; // r2.operator=(r1.operator=(r3));

    cout << r1 << endl;
    cout << r2 << endl;
    cout << r3 << endl;
}
