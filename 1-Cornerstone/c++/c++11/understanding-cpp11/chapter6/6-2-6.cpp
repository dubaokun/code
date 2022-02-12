#include <cstdio>
#include <tuple>
using namespace std;

template<typename A, typename B> struct S {};

// 两个模板参数包
template<
    template<typename... > class T, typename... TArgs
  , template<typename... > class U, typename... UArgs
  >
  struct S< T< TArgs... >, U< UArgs... > > {};

int main()
{
    S<int, float>  p;
    S<std::tuple<int, char>, std::tuple<float>>  s;
}

