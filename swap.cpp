// Copyright (c) 2019 Paul Keir, University of the West of Scotland.

#include "swap.hpp"
#include <iostream>
#include <tuple>
#include <vector>
#include <memory>
#include <cassert>

template <typename T>
constexpr bool test_3()
{
  T a1{1}, a2{2}, a3{3};
  nary::swap(a1,a2,a3);
  nary::swap(a1,a2,a3);
  nary::swap(a1,a2,a3);
  bool left  = (a1 == 1 && a2 == 2 && a3 == 3);
//  nary::swapr(a1,a2,a3);
//  nary::swapr(a1,a2,a3);
//  nary::swapr(a1,a2,a3);
//  bool right = (a1 == 1 && a2 == 2 && a3 == 3);
  return left;// && right;
}

template <std::size_t N, typename ...Ts>
constexpr bool test_n(Ts &...xs)
{
  if constexpr (N==sizeof...(xs)) {
    std::tuple before = std::make_tuple(xs...);
    for (std::size_t i = 0; i < N; i++) { nary::swap(xs...); }
    std::tuple after  = std::make_tuple(xs...);
    bool left  = (before==after);
//    for (std::size_t i = 0; i < N; i++) { nary::swapr(xs...); }
//    std::tuple afterr = std::make_tuple(xs...);
//    bool right = (before==afterr);
    return left;// && right;
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

  int x{7}, y{8};
  swap(x,y);
  std::cout << x << ',' << y << '\n'; // 8,7
  swap(x,y);  
  std::cout << x << ',' << y << '\n'; // 7,8

  const std::vector<int> v1_orig{1,2}, v2_orig{3,4,5}, v3_orig{6,7,8,9};
        std::vector<int> v1(v1_orig),  v2(v2_orig),    v3(v3_orig);
  swap(v1,v2,v3);
  assert(v1==v2_orig && v2==v3_orig && v3==v1_orig);

        auto p1      = std::make_unique<int>(42);
        auto p2      = std::make_unique<int>(43);
        auto p3      = std::make_unique<int>(44);
  swap(p1,p2,p3);
  assert(*p1==43 && *p2==44 && *p3==42);

  int a1{1}, a2{2}, a3{3};
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 1,2,3
  swap(a1,a2,a3);
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 2,3,1
  swap(a1,a2,a3);
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 3,1,2
  swap(a1,a2,a3);
  std::cout << a1 << ',' << a2 << ',' << a3 << '\n'; // 1,2,3

  return 0;
}
