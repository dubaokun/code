#include <iostream>
#include <vector>
#include <map>

using namespace std;

using myIntVec = std::vector<int>;
void testUsing2() {
  myIntVec mvec = { 1, 2, 3, 4, 5 };
  mvec.push_back(123);
  for (int num : mvec)
      printf("--- num:%d\n", num);
      //std::cout << is_same< std::vector<int>, myIntVec>::value << std::endl; // 1
}

template <typename T>
using MapStr = std::map<T, std::string>;

void testUsing3() {
  MapStr<int> intStrMap;
  intStrMap.insert(make_pair(123, "aaa"));
  intStrMap.insert(make_pair(456, "bbb"));

  MapStr<std::string> strstrMap;
  strstrMap.insert(make_pair("ccc", "ddd"));
  strstrMap.insert(make_pair("eee", "fff"));
}

int main(int argc, char ** argv) {
  testUsing3();
  return 0;
}
