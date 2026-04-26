/**
 * @file 2_unique_shared_lock.cpp
 * @brief - 多个**读者**同时持有共享锁（`shared_lock`）
 *        - 只有一个**写者**可以持有独占锁（`unique_lock` / `lock_guard`）
 * @author Albert
 * @version 1.0
 * @date 2025-12-24
 */
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex m;
int value = 0;

void reader(int id)
{
    for (int i = 0; i < 5; ++i)
    {
        std::shared_lock<std::shared_mutex> lock(m);
        std::cout << "reader " << id << " sees value = " << value << '\n';
        // lock 自动释放
    }
}

void writer(int id)
{
    for (int i = 0; i < 5; ++i)
    {
        /* - `std::lock_guard`
            - 进入作用域：自动加锁
            - 作用域结束：自动解锁
            - 期间**不能**手动 `unlock()` / 重新 `lock()` / 延迟加锁
            - 用途：最简单的“在这个大括号内持有锁”
         * */
        std::lock_guard<std::shared_mutex> lock(m);
        /* - `std::unique_lock`
            - 进入作用域时可以选择：
              - 立刻加锁
              - 延迟加锁（`std::defer_lock`）
              - 尝试加锁（`std::try_to_lock`）
            - 期间可以：
              - 手动 `lock()` / `unlock()`
              - 用于定时锁（`try_lock_for/try_lock_until`，配合 `timed_mutex` 一类）
              - 把这个锁对象 **move** 到别的函数/线程中
            - 作用域结束时，如果还持有锁，会自动解锁
         * */
        // std::unique_lock<std::shared_mutex> lock(m);
        ++value;
        std::cout << "writer " << id << " set value = " << value << '\n';
    }
}

int main()
{
    std::vector<std::thread> threads;
    threads.emplace_back(writer, 1);
    threads.emplace_back(reader, 1);
    threads.emplace_back(reader, 2);

    for (auto & t : threads)
        t.join();
}
