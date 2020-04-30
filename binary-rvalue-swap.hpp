#ifndef _BINARY_RVALUE_SWAP_HPP_
#define _BINARY_RVALUE_SWAP_HPP_

// Copyright (c) 2020 Paul Keir, University of the West of Scotland.

#include <utility>
#include <type_traits>

namespace nary {

template <typename T, typename U>
constexpr
std::enable_if_t<
  std::is_same_v<
    std::remove_reference_t<T>,
    std::remove_reference_t<U>
  >
>
swap(T &&x1, U &&x2)
noexcept (
  std::is_nothrow_move_constructible_v<T> &&
  std::is_nothrow_move_assignable_v<T>
)
{
  using value_t = std::remove_reference_t<T&&>;
  value_t temp = std::move(x1);
  x1 = std::move(x2);
  x2 = std::move(temp);
}

constexpr bool test_binary() {
  int x1 = 1, y1 = 2;
  swap(x1,y1);
  bool b1 = x1==2 && y1==1;

  int x2 = 1;
  swap(x2,2);       // template <template T> void swap(T&, T&&);
  bool b2 = x2==2;

  int y3 = 2;
  swap(1,y3);       // template <template T> void swap(T&, T&&);
  bool b3 = y3==1;

  swap(1,2);        // Nothing measurable, but no error => generic

  return b1&&b2&&b3;
}

static_assert(test_binary());

} // namespace nary

#endif // _BINARY_RVALUE_SWAP_HPP_
