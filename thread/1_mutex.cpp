/**
 * @file 1_mutex.cpp
 * @brief 选择标准可以按一句话记：**默认用 `std::mutex`，只有在“读多写少”并且性能真有压力时，才考虑 `std::shared_mutex`。**
 *      - `std::mutex`：
 *        - 手动：`lock()` / `unlock()`
 *        - RAII：`std::lock_guard<std::mutex>` / `std::unique_lock<std::mutex>`
 *      - `std::shared_mutex`：
 *        - 写：`lock()` / `unlock()` 或 `std::unique_lock<std::shared_mutex>`
 *        - 读：`lock_shared()` / `unlock_shared()` 或 `std::shared_lock<std::shared_mutex>`
 * @author Albert
 * @version 1.0
 * @date 2025-12-22
 */
#include <iostream>
#include <mutex>
#include <shared_mutex>

int data = 0;

// - 任意读/写操作都必须串行：
std::mutex m;
void thread_func()
{
    std::lock_guard<std::mutex> lk(m); // 或 unique_lock
    // 读或写 data
    std::cout << data << std::endl;
    data++;
}

/* - 共享锁（读锁）：`lock_shared()` / `unlock_shared()`，或 `std::shared_lock`
 * - 独占锁（写锁）：`lock()` / `unlock()`，或 `std::unique_lock`
 */
std::shared_mutex sm;
// 读线程
void reader()
{
    std::shared_lock<std::shared_mutex> lk(sm); // 读锁
    // 只读 data，可并发
    std::cout << data << std::endl;
}

// 写线程
void writer()
{
    std::unique_lock<std::shared_mutex> lk(sm); // 写锁
    data++;
}
