# shared_ptr 测试用例

---

## 1. shared_ptr 简介

- shared_ptr 是 C++11 提供的智能指针，用于管理动态分配的内存资源。
- shared_ptr 是一个模版类，可以存储任意类型的指针，通过引用计数的方式来管理资源的生命周期。
- shared_ptr 通过 std::make_shared 创建，可以避免内存泄漏和提高性能。
- shared_ptr 支持拷贝、移动、析构，是对其内部指针的委托调用。
