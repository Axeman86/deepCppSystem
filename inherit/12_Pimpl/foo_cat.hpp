// foo_cat.hpp
// ## 3) CheshireCat / 模板化 Pimpl 风格（把 Pimpl 样板抽出来）
// 通过实现继承（implementation inheritance）复用样板代码来对 Pointer 进行统一管理
#pragma once
#include "CheshireCat.hpp"
#include <string>

class FooCat : private CheshireCat<struct FooCatImpl>
{
public:
    FooCat();
    void push(const std::string & s);
    std::size_t size() const;
};
