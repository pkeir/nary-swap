A C++17 **constexpr** version of **std::swap** which supports zero or more arguments. The implementation is centered on the use of a *fold expression*. The topic is described in a blog post [here](https://pkeir.github.io/blog/2019/01/08/nary-swap).

```
hg clone https://github.com/pkeir/nary-swap
$CXX -std=c++17 swap.cpp
./a.out
```
