// foo_cat.cpp
#include "foo_cat.hpp"
#include <iostream>
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

int main()
{
    FooCat foo;

    foo.push("Hello");
    foo.push("World");

    std::cout << "Size: " << foo.size() << std::endl;
}
