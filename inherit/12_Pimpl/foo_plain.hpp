// ## 1) 非 Pimpl（实现细节暴露在头文件）
#pragma once
#include <string>
#include <vector>

class FooPlain
{
public:
    FooPlain();
    void push(const std::string & s);
    std::size_t size() const;

private:
    std::vector<std::string> mData; // 细节暴露
};
