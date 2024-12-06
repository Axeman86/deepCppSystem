/**
 * @file 7_weak_circle.cpp
 * @brief weak_ptr 弱引用，解决循环引用问题
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-03
 */
#include <iostream>
#include <memory>

using namespace std;

struct BClass;
struct CClass;

struct AClass
{
    shared_ptr<BClass> pb;
    ~AClass() { std::cout << "~AClass()\n"; }
};

struct BClass
{
    weak_ptr<CClass> pc; //-> weak_ptr 弱引用不计引用计数
    ~BClass() { std::cout << "~BClass()\n"; }
};

struct CClass
{
    shared_ptr<AClass> pa;
    ~CClass() { std::cout << "~CClass()\n"; }
};

int main()
{
    {
        shared_ptr<AClass> a = std::make_shared<AClass>();
        shared_ptr<BClass> b = std::make_shared<BClass>();
        shared_ptr<CClass> c = std::make_shared<CClass>();
        std::cout << "a计数: " << a.use_count() << "\n";
        std::cout << "b计数: " << b.use_count() << "\n";
        std::cout << "c计数: " << c.use_count() << "\n";

        // 循环引用
        a->pb = b;
        b->pc = c; // weak_ptr 弱引用不计引用计数 for c
        c->pa = a;
        std::cout << "a计数: " << a.use_count() << "\n";
        std::cout << "b计数: " << b.use_count() << "\n";
        std::cout << "c计数: " << c.use_count() << "\n";

        a.reset();
        b.reset();
        c.reset();

        std::cout << "a计数: " << a.use_count() << "\n";
        std::cout << "b计数: " << b.use_count() << "\n";
        std::cout << "c计数: " << c.use_count() << "\n";

        /* cout << "----------" << endl;
         * std::cout << "计数: " << a->pb.use_count() << "\n";
         * std::cout << "计数: " << b->pc.use_count() << "\n";
         * std::cout << "计数: " << c->pa.use_count() << "\n";
         * b->pc.reset();
         * std::cout << "计数: " << b->pc.use_count() << "\n"; */
    }

    // a, b 仍然相互持有
}
