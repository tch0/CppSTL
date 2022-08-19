## 第十八章 并发

<del>由于windows上的mingw-w64目前仍然是GCC 8.1且不支持多线程。所以本章的代码仅运行在Linux上，当然也可以在Windows上使用其他编译器来编译</del>。

Windows上可选择支持C++17的MingW-w64版本，或者使用MSYS2环境亦可。

调试时需要选择`Linux: make and gdb debug single file`这个task。

编译：
```sh
make a_target_file
make all
```

编译调试版本：
```sh
make debug=yes a_target_file
make debug=yes all
```