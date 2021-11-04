# C++ Concurrency Tests and Examples

[![CI](https://github.com/Toxe/cpp-threads/workflows/CI/badge.svg)](https://github.com/Toxe/cpp-threads/actions) [![Build Status](https://travis-ci.com/Toxe/cpp-threads.svg?branch=master)](https://travis-ci.com/Toxe/cpp-threads)

## Thread Sanitizer (TSAN)

When using Clang or GCC pass `-DUSE_SANITIZER=thread` to CMake to use Thread Sanitizer.

## Performance: Atomic vs Mutex

System: AMD Ryzen 9 3900X, no sanitizers

**Windows 10, native (MSVC 16.11.3):**

```
$ .\build\src\performance_atomic_vs_mutex\Release\performance_atomic_vs_mutex.exe
[2021-11-04 09:14:10.261] [info] atomic  (no thread): 44ms
[2021-11-04 09:14:10.262] [info] atomic (one thread): 116ms
[2021-11-04 09:14:10.262] [info] mutex   (no thread): 152ms
[2021-11-04 09:14:10.262] [info] mutex  (one thread): 263ms
```

**Windows 10, WSL2 Ubuntu 21.04 Linux (Clang 12):**

```
$ ./build/src/performance_atomic_vs_mutex/performance_atomic_vs_mutex
[2021-11-04 09:11:34.338] [info] atomic  (no thread): 44ms
[2021-11-04 09:11:34.338] [info] atomic (one thread): 117ms
[2021-11-04 09:11:34.338] [info] mutex   (no thread): 107ms
[2021-11-04 09:11:34.338] [info] mutex  (one thread): 715ms
```
