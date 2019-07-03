#include <iostream>
#include <type_traits>
using namespace std;

// 一个对齐值为4的对象
struct IntAligned{
  int a;
  char b;
};

// 使用aligned_storage使其对齐要求更加严格
typedef aligned_storage<sizeof(IntAligned),alignof(long double)>::type StrictAligned;

int main() {
  StrictAligned sa;
  IntAligned* pia = new (&sa) IntAligned;
  cout << alignof(IntAligned) << endl;      // 4
  cout << alignof(StrictAligned) << endl;   // 16
  cout << alignof(*pia) << endl;            // 4
  cout << alignof(sa) << endl;              // 16
  return 0;
}
