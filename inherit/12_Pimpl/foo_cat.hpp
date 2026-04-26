// foo_cat.hpp
// ## 3) CheshireCat 风格（把 Pimpl 样板抽出来）
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
