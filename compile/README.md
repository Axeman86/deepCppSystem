# constexpr and consteval and constinit in C++20

---

## constexpr

---

- `constexpr` is a keyword in C++ which tells the compiler to evaluate the function or variable at compile time.
  - `constexpr function` 如果结果要求为编译期常量：
    1. 传参为编译期常量，函数可以正常得到编译期常量值
    2. 传参为运行期常量，函数只能是报错处理
  - `constexpr function` 如果结果要求为运行期变量：
    1. 传参传递可以是运行期变量，也可以是编译期常量
    2. 允许运行期合法的目的仅仅是为了避免多份重载版本
