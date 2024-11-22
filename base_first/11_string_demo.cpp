/**
 * @file 11_string_demo.cpp
 * @brief string 类型的内存分配机制, string().size < 16 时，string 会在栈上分配内存，
 *        否则在堆上分配内存, 在 Ubuntu 20.04 LTS, g++ 9.3.0 下测试
 * @author Albert
 * @version 1.0.0
 * @date 2024-11-22
 */
#include <iostream>
using namespace std;

auto allocated = 0;

void * operator new(size_t size)
{
    void * p = std::malloc(size);
    allocated += size;
    return p;
}

void operator delete(void * p) noexcept
{
    return std::free(p);
}

int main()
{
    const char * h = "hello";

    // stack size = 32, heap size = 0, capacity = 15, size= 10
    string s = "0123456789"s;

    // stack size = 32, heap size = 18, capacity = 17, size= 17
    // string s = std::string{ "0123456789,012345" };

    // s.reserve(1000);

    std::cout << "stack size = " << sizeof(s) << ", heap size = " << allocated << ", capacity = " << s.capacity()
              << ", size= " << s.size() << '\n';
}

/*
struct Long {
  size_t capacity_{};
  size_t size_{};
  char* data_{}; //堆
};

struct Short {
  unsigned char size_{};
  char data_[23]{}; //栈
};

union u_ {
  Short short_layout_;
  Long long_layout_;
};
*/
