#include <iostream>
#include "swap.hpp"

template <typename T>
constexpr bool test3() 
{
  using namespace nary;
  T a1 = 1, a2 = 2, a3 = 3;
  swap(a1,a2,a3);
  swap(a1,a2,a3);
  swap(a1,a2,a3);
  return a1 == 1 && a2 == 2 && a3 == 3;
}

int main(int argc, char *argv[])
{
  using namespace nary;
  static_assert(test3<int>());

  double d{3.14};
  swap(d);
  std::cout << d << '\n';

  int x = 7, y = 8;
  swap(x,y);
  std::cout << x << ',' << y << '\n'; // 8,7
  swap(x,y);  
  std::cout << x << ',' << y << '\n'; // 8,7

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
