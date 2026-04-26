// ## 2) 标准 Pimpl（推荐基础形态）
#pragma once
#include <memory>
#include <string>

class FooPimpl
{
public:
    FooPimpl();
    ~FooPimpl(); // 需要在 cpp 定义
    FooPimpl(FooPimpl &&) noexcept;
    FooPimpl & operator=(FooPimpl &&) noexcept;

    FooPimpl(const FooPimpl &)             = delete;
    FooPimpl & operator=(const FooPimpl &) = delete;

    void push(const std::string & s);
    std::size_t size() const;

private:
    struct Impl;                 // 前置声明
    std::unique_ptr<Impl> mImpl; // 隐藏实现
};
