# C++ STL 笔记

《C++标准库》第二版代码记录，本书包括C++11的特性，但不包括其后的C++14、C++17、C++20、C++23。

这里仅注明一些比较重要的细节。

## 标准库六大组件

- 容器（Containers）：
    - 顺序容器：`array vector deque list forward_list`
    - 关联容器（树形容器）：`map set multimap multiset`
    - 无序容器：`unordered_map unordered_set unordered_multimap unordered_multiset`
- 迭代器（Itrerators）：输入、输出、前向、双向、随机访问
- 泛型算法（Generic Algorithms）：`<algorithm> <numeric>`
- 适配器（Adapters）
    - 容器适配器（`stack queue priority_queue`）
    - 迭代器适配器（反向迭代器、插入迭代器、流迭代器、移动迭代器）
    - 函数适配器（`std::function`）
- 函数对象（Function Object）：`std::function std::bind`、Lambda
- 分配器（Allocators）：`std::allocator<>`

## STL错误处理

使用STL容器和算法时，必须时刻注意对容器迭代器的要求：
- 迭代器合法有效。
- 不能解引用尾后迭代器。
- 区间必须合法：指向同一容器、从第一个迭代器出发能够到达第二个迭代器。
- 涉及多个区间时，第二个区间必须至少与第一个区间一样长。
- 写入目标区间必须拥有足够元素，或者是使用的插入迭代器。

这些要求必须在使用STL的容器和算法时作为常识得到完全地保证。为了效率优先，STL的错误处理机制比较少，这些要求得不到满足时通常会导致运行时错误，并且大概率会破坏内存并且得不到有效的错误提示。可以在开发测试中使用安全版本的STL以提供错误提示：
- g++提供了`-D_GLIBCXX_DEBUG`选项，定义`_GLIBCXX_DEBUG`宏以开启STL错误检测。

## 输入输出流

IO操纵符：
- 无参数的操纵符通常定义为`stream&(stream&)`的函数，通过标准库中预定义的接受函数指针版本的`operator>>/<<`调用。
- 无参数的操纵符对应于一个格式化标志`std::ios_base::xxx`，一组标志合（按位或）起来会形成一个组（常用作掩码），其等效作用可以通过`setf`函数实现。
- 有参数的操纵符可以通过定义自定义类型，并通过对该类型重载`operator>>/<<`来实现。
- 有参数操纵符对应于一个流的成员函数。

作用域：
- 输入输出格式标志、相关类型等大多定义在`std::ios_base<>`内。
- 通常会使用其派生类`std::ios`也就是`std::basic_ios<char>`来引用，写起来更短，看起来更清晰。

用户自定义标志：
- `std::ios_base<>`提供了机制用以自定义标志。
- 可以是整数或者指针类型，保存在一个数组中，通过下标来引用。
- `xalloc`函数每次调用会分配一个新的下标，应该将其保存为一个常量。
- 对于指针类型，可能需要处理`copyfmt`复制流的标志和销毁时的指针标志的深拷贝和释放问题。
- `std::ios_base<>::register_callback`提供了注册回调函数的机制来处理这些问题。

连接两个流：
- 使用`tie`可以将一个流连接到另一个输出流，使得该流的操作之前总是刷新输出流缓冲区。
- 通过共用同一个stream buffer，可以将两个流绑定。可以用以实现以下行为：
    - 创建一个新流绑定到已有的流的stream buffer，设置新格式，不用切换设置标志的情况下以不同格式输出信息到同一个输出通道。
    - 设置流的stream buffer为其他的流的stream buffer，不依赖于操作系统将流重定向。
    - 两个流分别以读写方式绑定到同一个stream buffer，实现对同一个流的读写操作。（多用于文件流，但其实`fstream`的`in | out`模式原生就支持）。

Stream buffer：
- 格式控制操作在`std::basic_ios<>`中做，具体的读写则是在其中的Stream Buffer中做。
- 标准库对各种流都定义了对应的Stream buffer类，也可以自己定义Stream Buffer类。
- Stream Buffer迭代器类似于输入流和输出流迭代器。Stream Buffer同时支持输入和输出。

自定义Stream Buffer：
- Stream Buffer类基类`std::basic_streambuf<>`中实现了基本的功能，但如果要添加缓冲功能的话需要自己在派生类中来实现。
- 实现Stream Buffer时不一定要实现缓冲机制，比如输出时每个字符都直接输送输出通道，不经过缓冲。
- 通常Stream Buffer的读写操作是通过调用操作系统底层的系统调用来实现，比如类UNIX系统中的`read write`系统调用。而通常系统调用的消耗很高，实现缓冲机制可以显著减少系统调用次数，提升性能。

提升IO性能：
- IO的性能通常来说已经比较高了，如果IO成为了瓶颈，可以考虑以下方式优化，当然可能会存在一定副作用。
- 如果不用到全局的IO对象，就不要包`<iostream>`，包了之后会有一些初始化的开销。
- 使用`std::ios_base::sync_with_stdio(false)`取消C++标准流和C标准流的同步，可以减少一部分开销。这会失去标准流对并发的支持。
- 底层的读写操作的系统调用消耗很高，使用有缓冲机制的IO并且减少缓冲区刷新次数以减少底层系统调用次数。
    - 可以尽量不要使用`endl/flush/unitbuf`。
    - 不要使用`tie`绑定一个流到另一个输出流。
    - 在出错状态下可能会出现缓冲区未刷新的情况，不利于排查错误。可以在debug环境和release环境中采用不同策略，debug环境永远刷新。
- 如果不需要使用格式化的IO，可以直接使用流底层的Stream Buffer。可以减少中间的`sentry`对象相关的开销。
    - `sentry`对象做格式控制、多线程环境加锁之类的事情，每个基本类型的`operator<<`中都会构造并使用。（更多细节参见国际化章节）
    - 比如循环读取数据时，避免多次构造`sentry`，可以手工处理格式化，然后使用facet的`num_get`等底层接口直接读取数据。
    - 属于比较终极的优化方法了，会增加代码复杂度，具有一定使用门槛。