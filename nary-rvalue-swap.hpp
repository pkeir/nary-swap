#ifndef _NARY_RVALUE_SWAP_HPP_
#define _NARY_RVALUE_SWAP_HPP_

// Copyright (c) 2020 Paul Keir, University of the West of Scotland.

#include <utility>
#include <type_traits>

namespace nary_rvalue {

constexpr void swap() noexcept {}

template <typename T, typename ...Ts>
constexpr
std::enable_if_t<std::conjunction_v<std::is_same<T,Ts>...>>
swap(T &&x, Ts &&...xs)
noexcept (
  std::is_nothrow_move_constructible_v<T> &&
  std::is_nothrow_move_assignable_v<T>
)
{
  using value_t = std::remove_reference_t<T&&>;
  value_t tmp = std::move(x);
  struct wrap {
    constexpr wrap operator+(wrap &&w) { x = std::move(w.x); return     w; }
    value_t &x;
  };
  auto c = [](auto &...xs) { (... + wrap{xs}); };
  c(x,xs...,tmp);
}

                      constexpr void swapr()    noexcept {}
template <typename T> constexpr void swapr(T &&) noexcept {}

template <typename T, typename ...Ts>
constexpr
std::enable_if_t<std::conjunction_v<std::is_same<T,Ts>...>>
swapr(T && x, Ts &&...xs)
noexcept (
  std::is_nothrow_move_constructible_v<T> &&
  std::is_nothrow_move_assignable_v<T>
)
{
  using value_t = std::remove_reference_t<T&&>;
  value_t tmp = std::move((xs , ...));
  struct wrap {
    constexpr wrap operator+(wrap &&w) { w.x = std::move(x); return *this; }
    value_t &x;
  };
  auto c = [](auto &...xs) { (wrap{xs} + ...); };
  c(tmp,x,xs...);
}

} // namespace nary_rvalue

/*
template <typename T>
constexpr void swap(T &t1, T &t2)
{
  T temp = std::move(t1);
  t1 = std::move(t2);
  t2 = std::move(temp);
}

template <typename T>
constexpr void swapr(T &t1, T &t2)
{
  T temp = std::move(t2);
  t2 = std::move(t1);
  t1 = std::move(temp);
}
*/

#endif // _NARY_RVALUE_SWAP_HPP_
