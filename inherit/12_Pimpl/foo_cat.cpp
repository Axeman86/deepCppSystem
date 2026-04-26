// foo_cat.cpp
#include "foo_cat.hpp"
#include <vector>

struct FooCatImpl
{
    std::vector<std::string> mData;
};

FooCat::FooCat() : CheshireCat<FooCatImpl>() {}
void FooCat::push(const std::string & s)
{
    impl()->mData.push_back(s);
}
std::size_t FooCat::size() const
{
    return impl()->mData.size();
}
