#include <utility>
#include <type_traits>

// A version of std::swap which works for 1 or more variables using C++17 fold
// expressions.

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
    constexpr wrap operator+(wrap &&w) { x = std::move(w.x); return w; }
    T &x;
  };
  auto c = [](auto &...xs) { (... + wrap{xs}); };
  c(x,xs...,tmp);
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
*/

