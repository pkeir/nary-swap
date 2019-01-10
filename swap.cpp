// Copyright (c) 2019 Paul Keir, University of the West of Scotland.

#include "swap.hpp"
#include <iostream>
#include <tuple>

template <typename T>
constexpr bool test_3()
{
  T a1{1}, a2{2}, a3{3};
  nary::swap(a1,a2,a3);
  nary::swap(a1,a2,a3);
  nary::swap(a1,a2,a3);
  bool left  = (a1 == 1 && a2 == 2 && a3 == 3);
  nary::swapr(a1,a2,a3);
  nary::swapr(a1,a2,a3);
  nary::swapr(a1,a2,a3);
  bool right = (a1 == 1 && a2 == 2 && a3 == 3);
  return left && right;
}

template <std::size_t N, typename ...Ts>
constexpr bool test_n(Ts &...xs)
{
  if constexpr (N==sizeof...(xs)) {
    std::tuple before = std::make_tuple(xs...);
    for (std::size_t i = 0; i < N; i++) { nary::swap(xs...); }
    std::tuple after  = std::make_tuple(xs...);
    bool left  = (before==after);
    for (std::size_t i = 0; i < N; i++) { nary::swapr(xs...); }
    std::tuple afterr = std::make_tuple(xs...);
    bool right = (before==afterr);
    return left && right;
  }
  else {
    std::size_t x{sizeof...(xs)};
    return test_n<N>(xs...,x);
  }
}

template <auto ...Is>
constexpr bool run_tests(std::index_sequence<Is...>) {
  return ((test_3<char>() && ... && test_n<Is>()));
}

int main(int argc, char *argv[])
{
  using namespace nary;
  static_assert(run_tests(std::make_index_sequence<10>{}));

  double d{3.14};
  swap(d);
  std::cout << d << '\n';

  int x = 7, y = 8;
  swap(x,y);
  std::cout << x << ',' << y << '\n'; // 8,7
  swap(x,y);  
  std::cout << x << ',' << y << '\n'; // 7,8

  int a1 = 1, a2 = 2, a3 = 3;
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 1,2,3
  swap(a1,a2,a3);
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 2,3,1
  swap(a1,a2,a3);
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 3,1,2
  swap(a1,a2,a3);
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 1,2,3

  return 0;
}
