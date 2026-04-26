// cheshire_cat.hpp
#pragma once
#include <memory>
#include <utility>

template <typename T>
using impl_ptr = std::shared_ptr<T>;

template <typename T>
class CheshireCat
{
public:
    explicit CheshireCat(impl_ptr<T> impl) : mImpl(std::move(impl)) {}

    template <typename... Args>
    explicit CheshireCat(Args &&... args) : mImpl(std::make_shared<T>(std::forward<Args>(args)...))
    {}

    CheshireCat(CheshireCat &&) noexcept             = default;
    CheshireCat & operator=(CheshireCat &&) noexcept = default;

    CheshireCat(const CheshireCat &)             = delete;
    CheshireCat & operator=(const CheshireCat &) = delete;

    virtual ~CheshireCat() = default;

protected:
    impl_ptr<T> impl() { return mImpl; }
    impl_ptr<const T> impl() const { return mImpl; }

private:
    impl_ptr<T> mImpl;
};
