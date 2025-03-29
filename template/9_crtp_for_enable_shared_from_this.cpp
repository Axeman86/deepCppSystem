/**
 * @file 8_crtp_for_enable_shared_from_this.cpp
 * @brief CRTP modle FOR std::enable_shared_from_this implementation
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-21
 */
#include <iostream>
#include <memory>

template <typename T>
class my_enable_shared_from_this
{
private:
    // 保存一个弱指针, 用于获取共享指针; 这样就不会因为共享指针的引用计数永远不为0而导致内存泄漏;
    std::weak_ptr<T> weak_this;

protected:
    constexpr my_enable_shared_from_this() noexcept { std::cout << "my_enable_shared_from_this()" << std::endl; }

    my_enable_shared_from_this(const my_enable_shared_from_this &) noexcept {}

    my_enable_shared_from_this & operator=(const my_enable_shared_from_this &) noexcept { return *this; }

    ~my_enable_shared_from_this() { std::cout << "~my_enable_shared_from_this()" << std::endl; }

public:
    void initializer_list(std::shared_ptr<T> obj) noexcept { weak_this = obj; }
    std::shared_ptr<T> shared_from_this() // 获取一个子类的共享指针
    {
#if 1
        return static_cast<std::shared_ptr<T>>(this->weak_this);
#else
        if (!weak_this.expired())
        {
            return weak_this.lock();
        }
        else
        {
            throw std::exception{};
        }
#endif
    }

    std::shared_ptr<const T> shared_from_this() const { return static_cast<std::shared_ptr<T>>(this->weak_this); }
};

// 扩展接口： 父类里面注入子类信息
class Widget : public my_enable_shared_from_this<Widget>
{
public:
    std::shared_ptr<Widget> getWidget()
    {
        return shared_from_this(); // OK
    }

    void process(std::shared_ptr<Widget> ptr) { std::cout << "process() " << ptr << std::endl; }

    void invoke() { process(shared_from_this()); }

    void print() { std::cout << "print " << shared_from_this() << std::endl; }

    ~Widget() { std::cout << "~Widget()" << std::endl; }

    //工厂函数
    static std::shared_ptr<Widget> factoryModeCreate()
    {
        std::shared_ptr<Widget> tmp = std::shared_ptr<Widget>(new Widget(), [](Widget * p) {
            std::cout << "Delete Widget " << p << std::endl;
            delete p;
        });
        if (tmp)
        {
            tmp->initializer_list(tmp);
        }
        return tmp;
    }

private:
    // 构造函数私有化, 防止外部直接创建对象, 只能通过成员工厂函数创建
    Widget() { std::cout << "Widget()" << std::endl; }
};

int main()
{
    {
        std::shared_ptr<Widget> w = Widget::factoryModeCreate();
        w->print();
        w->invoke();
        std::cout << "w.use_count() = " << w.use_count() << std::endl;
        std::shared_ptr<Widget> w2 = w->getWidget();
        w2->print();
        w2->invoke();
        std::cout << "w2.use_count() = " << w2.use_count() << std::endl;
        const std::shared_ptr<Widget> w3 = w->getWidget();
        w3->print();
        w3->invoke();
        std::cout << "w3.use_count() = " << w3.use_count() << std::endl;
    }
    std::cout << "Program finished" << std::endl; // 会调用析构函数 "~Widget()
    return 0;
}
