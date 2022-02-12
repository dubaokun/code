#include <iostream>
#include <map>
 
int main()
{
    std::multimap<int, char> dict {
        {1, 'A'},
        {2, 'B'},
        {2, 'C'},
        {2, 'D'},
        {4, 'E'},
        {3, 'F'}
    };

    std::multimap<int, char> dict2 {
        {2, 'B'},
        {2, 'C'},
        {2, 'D'}
    };

 
    auto range = dict.equal_range(2);

    std::cout << range.first->first << std::endl;
    std::cout << range.second->first << std::endl;

    std::cout << "===========================" << std::endl;
    auto range2 = dict2.equal_range(2);

    std::cout << range2.first->first << " value=" << range2.first->second << std::endl;
    std::cout << range2.second->first << " value=" << range2.second->second << std::endl;

    std::cout << "===========================" << std::endl;
 
 
    for (auto i = range.first; i != range.second; ++i)
    {
        std::cout << i->first << ": " << i->second << '\n';
    }
}
