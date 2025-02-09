/**
 * @file 8_enable_if_stl.cpp
 * @brief 深入 std::shared_ptr 实现的源码分析，了解 enable_if 的在模板类中的应用
 * @author Albert
 * @version 1.0
 * @date 2025-02-09
 */
#include <iostream>
#include <memory>

using namespace std;

namespace custom {
template <typename _Tp>
class shared_ptr
{
public:
    // 强类型绑定： If _OrigPtr * and const enable_shared_from_this<_Yp> * is convertible, then enable weak type
    // binding return type is void
    template <typename _Yp, typename _OrigPtr>
    typename enable_if<is_convertible_v<_OrigPtr *, const enable_shared_from_this<_Yp> *>, void>::type
    __enable_weak_this(const enable_shared_from_this<_Yp> * __e, _OrigPtr * __ptr) noexcept
    {
        typedef typename remove_cv<_Yp>::type _RawYp;
        if (__e && __e->__weak_this_.expired())
        {
            __e->__weak_this_ = shared_ptr<_RawYp>(*this, const_cast<_RawYp *>(static_cast<const _Yp *>(__ptr)));
        }
    }

    // 弱类型绑定
    void __enable_weak_this(...) noexcept {}
};
} // namespace custom

int main()
{
    shared_ptr<int> p;
    custom::shared_ptr<int> cp;
}
