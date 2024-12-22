# template: README.md

---

## type

- type 目录下是一些常用的类型使用方式的测试用例: [type](./type/README.md)

## Table of Contents

- 主要是一些常用的模板，方便快速使用。
- 个人对于模版的理解，以及 CRTP 模式的使用。

## CRTP

---

奇异递归模板模式（Curiously Recurring Template Pattern, CRTP）是一种在 C++中使用模板的编程技巧。它允许一个类将自己作为模板参数传递给基类，从而实现静态多态性和编译时多态性。CRTP 的用途包括：

- 静态多态性：通过 CRTP，可以在编译时实现多态性，而不需要运行时的虚函数调用，从而提高性能。
- 代码复用：基类可以定义通用的算法，而派生类可以提供特定的实现。
- 编译时检查：CRTP 可以在编译时进行类型检查，避免运行时错误。
