/*
 *  template< class InputIt, class Distance >
 *  constexpr void advance( InputIt& it, Distance n );
 *  
 *  it  -   要前进的迭代器
 *  n   -   it 要前进的元素数
 *
 */
#include <iostream>
#include <iterator>
#include <vector>
 
int main() 
{
    std::vector<int> v{ 3, 1, 4 };
 
    auto vi = v.begin();
 
    std::advance(vi, 2);
 
    std::cout << *vi << '\n';
}
