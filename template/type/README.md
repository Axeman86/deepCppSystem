# CPP 常用类型的使用方式总结

---

## std::pair 类型

- 将两个对象组合成一个对象，两个对象可以是同一类型或不同类型
- C++17 之前，支持模版函数自动推导: `auto kv = std::make_pair(100, "Cpp"s);`
- C++17 之后，支持构造函数参数类型推导: `std::pair kv{100, "Cpp"s}`
- std::pair 支持拷贝、移动、析构，是对 first and second 的委托调用

## std::tuple 类型

- 标准库类型 std::tuple 是一个通用的元组类，可以存储多个不同类型的值
- std::tuple 是一个变参模版类，可以存储任意数量的值，支持自动类型推导，通过 std::get<> 获取元素
- C++17 之前，支持模版函数自动推导: `auto tp = std::make_tuple(100, "Cpp"s);` 使用 `int id = std::get<0>(tp)` 获取第一个元素;
- C++17 之后，支持构造函数参数类型推导: `std::tuple tp{100, 3.14, "Cpp"s}` 使用 `string lang = std::get<2>(tp)` 获取第一个元素;
- std::tuple 支持拷贝、移动、析构，是对其内各个元素的委托调用
