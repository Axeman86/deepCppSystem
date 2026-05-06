// ## 2) 标准/经典 Pimpl（推荐基础形态）
// `class X { struct Impl; std::unique_ptr<Impl> p; };`
#pragma once
#include <memory>
#include <string>

class FooPimpl
{
public:
    FooPimpl();
    ~FooPimpl()                                = default;
    FooPimpl(FooPimpl &&) noexcept             = default;
    FooPimpl & operator=(FooPimpl &&) noexcept = default;
    FooPimpl(const FooPimpl &)                 = delete;
    FooPimpl & operator=(const FooPimpl &)     = delete;

    void push(const std::string & s);
    std::size_t size() const;

private:
    struct Impl;                 // 前置声明
    std::unique_ptr<Impl> mImpl; // 隐藏实现
};
