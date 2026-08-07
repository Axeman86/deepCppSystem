#include "foo_plain.hpp"
#include <iostream>

FooPlain::FooPlain() = default;
void FooPlain::push(const std::string & s)
{
    mData.push_back(s);
}
std::size_t FooPlain::size() const
{
    return mData.size();
}

int main()
{
    FooPlain foo;

    foo.push("Hello");
    foo.push("World");

    std::cout << "Size: " << foo.size() << std::endl;
}
