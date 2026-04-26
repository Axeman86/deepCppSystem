#include "foo_plain.hpp"

FooPlain::FooPlain() = default;
void FooPlain::push(const std::string & s)
{
    mData.push_back(s);
}
std::size_t FooPlain::size() const
{
    return mData.size();
}
