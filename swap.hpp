// Copyright (c) 2019 Paul Keir, University of the West of Scotland.

// A version of std::swap which works for 0 or more variables using C++17 fold
// expressions.

#include <utility>
#include <type_traits>

namespace nary {

constexpr void swap() {}

template <typename T, typename ...Ts>
constexpr
std::enable_if_t<std::conjunction_v<std::is_same<T,Ts>...>>
swap(T &x, Ts &...xs)
noexcept (
  std::is_nothrow_move_constructible_v<T> &&
  std::is_nothrow_move_assignable_v<T>
)
{
  T tmp = std::move(x);
  struct wrap {
    constexpr wrap operator+(wrap &&w) { x = std::move(w.x); return     w; }
    T &x;
  };
  auto c = [](auto &...xs) { (... + wrap{xs}); };
  c(tmp,x,xs...,tmp);
}

constexpr void swapr() {}

template <typename T, typename ...Ts>
constexpr
std::enable_if_t<std::conjunction_v<std::is_same<T,Ts>...>>
swapr(T &x, Ts &...xs)
noexcept (
  std::is_nothrow_move_constructible_v<T> &&
  std::is_nothrow_move_assignable_v<T>
)
{
  T tmp = std::move(x);
  struct wrap {
    constexpr wrap operator+(wrap &&w) { w.x = std::move(x); return *this; }
    T &x;
  };
  auto c = [](auto &...xs) { (wrap{xs} + ...); };
  c(tmp,x,xs...,tmp);
}

} // namespace nary

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
