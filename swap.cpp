#include <iostream>
#include <tuple>
#include "swap.hpp"

template <typename T>
constexpr bool test_3()
{
  T a1{1}, a2{2}, a3{3};
  nary::swap(a1,a2,a3);
  nary::swap(a1,a2,a3);
  nary::swap(a1,a2,a3);
  return a1 == 1 && a2 == 2 && a3 == 3;
}

template <std::size_t N, typename ...Ts>
constexpr bool test_n(Ts &...xs)
{
  if constexpr (N==sizeof...(xs)) {
    std::tuple before(xs...);
    for (int i = 0; i < N; i++) { nary::swap(xs...); }
    std::tuple  after(xs...);
    return before==after;
  }
  else {
    std::size_t x{sizeof...(xs)};
    return test_n<N>(xs...,x);
  }
}

template <auto I, auto ...Is>
constexpr bool run_tests(std::index_sequence<I,Is...>) {
  return (... && test_n<Is>());
}

int main(int argc, char *argv[])
{
  using namespace nary;
  static_assert(test_3<int>());
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
