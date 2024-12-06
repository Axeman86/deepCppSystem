/**
 * @file 9_unique_shared.cpp
 * @brief unique_ptr 初始化 shared_ptr, unique_ptr 不能拷贝, 但可以移动到 shared_ptr;
 * @author Albert
 * @version 1.0.0
 * @date 2024-12-04
 */
#include <iostream>
#include <memory>

using namespace std;

/*
template<typename Y, typename Deleter>
shared_ptr(unique_ptr<Y,Deleter>&& u);
*/

unique_ptr<string> process()
{
    return make_unique<string>("hello");
}

int main()
{
    shared_ptr<string> sp1 = process();

    auto up = make_unique<string>("Hello World");

    /* shared_ptr<string> sp2{ up }; // error, unique_ptr delete copy operator, so can't copy to shared_ptr */
    // success, unique_ptr delete copy operator, so can't copy to shared_ptr, but can move to shared_ptr
    shared_ptr<string> sp2{ std::move(up) };

    if (sp2.unique()) // check sp2.use_count() == 1 ?
    {
        cout << "only 1 count" << endl;
    }
}
