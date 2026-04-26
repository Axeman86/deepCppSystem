/**
 * @file 3_atomic.cpp
 * @brief 多线程计数器
 *      - 在 C++20 及以后、简单读的情况下：`x` 和 `x.load()` 效果一样
 *      - 为了兼容性和可读性，**推荐总是用 `.load()` / `.store()`**
 * @author Albert
 * @version 1.0
 * @date 2025-12-24
 */
#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

std::atomic<int> counter{ 0 };

void worker()
{
    for (int i = 0; i < 100000; ++i)
    {
        counter.fetch_add(1); // 原子自增，也可以用 ++counter or counter++
        counter += 2;
        counter.fetch_sub(1); // 原子自减，也可以用 --counter or counter--
    }
}

void test_thread_count()
{
    std::cout << "Atomic Example\n";
    std::vector<std::thread> ts;
    for (int i = 0; i < 4; ++i)
    {
        ts.emplace_back(worker);
    }
    for (auto & t : ts)
        t.join();

    // 没有数据竞争，结果一定是 8 * 100000
    int result = counter.load();
    std::cout << "Final counter value: " << result << std::endl;
}

std::atomic<bool> stop{ false };
void worker_flag()
{
    while (!stop.load())
    { // 读
        std::cout << "worker_flag: " << std::boolalpha << stop.load(std::memory_order_seq_cst) << std::endl;
        // 做一些工作
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    test_thread_count();

    std::thread t(worker_flag);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // ...
    stop.store(true); // 通知退出
    t.join();
}
