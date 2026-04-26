// foo_pimpl.cpp
#include "foo_pimpl.hpp"
#include <vector>

// 具体实现类定义
struct FooPimpl::Impl
{
    std::vector<std::string> mData;
};

FooPimpl::FooPimpl() : mImpl(std::make_unique<Impl>()) {}
FooPimpl::~FooPimpl()                                = default;
FooPimpl::FooPimpl(FooPimpl &&) noexcept             = default;
FooPimpl & FooPimpl::operator=(FooPimpl &&) noexcept = default;

void FooPimpl::push(const std::string & s)
{
    mImpl->mData.push_back(s);
}
std::size_t FooPimpl::size() const
{
    return mImpl->mData.size();
}
