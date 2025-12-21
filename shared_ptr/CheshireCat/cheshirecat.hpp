/*
 *     Copyright (c) 2021-2022 Project CHIP Authors
 *     All rights reserved.
 *
 *     Licensed under the Apache License, Version 2.0 (the "License");
 *     you may not use this file except in compliance with the License.
 *     You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 *     Unless required by applicable law or agreed to in writing, software
 *     distributed under the License is distributed on an "AS IS" BASIS,
 *     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *     See the License for the specific language governing permissions and
 *     limitations under the License.
 */
#include <memory>

// pimpl base class
template <typename T>
using impl_ptr = std::shared_ptr<T>;
template <typename T>
class CheshireCat
{
public:
    CheshireCat(impl_ptr<T> impl) : mImpl(std::move(impl)) {}
    template <typename... Args>
    CheshireCat(Args... args) : mImpl(std::make_shared<T>(std::forward<Args>(args)...))
    {}
    CheshireCat(CheshireCat<T> && cc) { *this = std::move(cc); }
    CheshireCat(const CheshireCat<T> &) = delete;

    virtual ~CheshireCat() = default;

    CheshireCat & operator=(CheshireCat<T> && cc)
    {
        mImpl = std::move(cc.mImpl);
        return *this;
    };
    CheshireCat & operator=(const CheshireCat<T> &) = delete;

protected:
    impl_ptr<T> impl() { return mImpl; }
    impl_ptr<const T> impl() const { return mImpl; }

private:
    impl_ptr<T> mImpl;
};
