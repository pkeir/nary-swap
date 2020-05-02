#ifndef _NARY_HETERO_FOLD_HPP_
#define _NARY_HETERO_FOLD_HPP_

#include <type_traits>

struct A { int v = 0; };
struct B { int v = 0; };

template <typename T, typename ...Ts>
struct is_one_of : std::disjunction<std::is_same<T,Ts>...> {};

static_assert(!is_one_of<int>::value);
static_assert( is_one_of<int>::value == std::disjunction<>::value);
static_assert( is_one_of<int,int>::value);
static_assert( is_one_of<A,A>::value);
static_assert( is_one_of<A,A,B>::value);
static_assert( is_one_of<A,int,A>::value);
static_assert(!is_one_of<A,int>::value);

template <typename T>
struct wrapl {
  template <typename U>
//  constexpr wrap<U> operator+(wrap<U> w) { w.x.v = x.v+1; return w; }
  constexpr auto operator+(wrapl<U> w) { w.x.v = x.v+1; return w; }
  T x;
};

template <typename T, typename ...Ts>
constexpr
std::enable_if_t<
  std::conjunction_v<is_one_of<T,A,B>,is_one_of<Ts,A,B>...>
  ,int
>
sumAB(T x, Ts ...xs)
{
  auto c = [](auto ...xs) { return (... + wrapl{xs}); };
  auto w = c(x,xs...);
  return w.x.v;
}

//static_assert(sumAB(A{},int{}));
//static_assert(sumAB(int{},A{}));
static_assert(0==sumAB(A{}));
static_assert(0==sumAB(B{}));
static_assert(1==sumAB(A{},A{}));
static_assert(1==sumAB(A{},B{}));
static_assert(1==sumAB(B{},B{}));
static_assert(2==sumAB(A{},A{},A{}));
static_assert(2==sumAB(A{},B{},A{}));
static_assert(2==sumAB(A{},B{},B{}));
static_assert(2==sumAB(B{},A{},A{}));

#endif // _NARY_HETERO_FOLD_HPP_
