#include <iostream>

// 函数模板
template<typename T>
bool equivalent(const T& a, const T& b){
    return !(a < b) && !(b < a);
}

// 类模板
template<typename T=int> // 默认参数
class bignumber{
    T _v;
public:
    bignumber(T a) : _v(a) { }
    inline bool operator<(const bignumber& b) const; // 等价于 (const bignumber<T>& b)
};

// 在类模板外实现成员函数
template<typename T>
bool bignumber<T>::operator<(const bignumber& b) const{
    return _v < b._v;
}

int main()
{
    bignumber<> a(1), b(1); // 使用默认参数，"<>"不能省略
    std::cout << equivalent(a, b) << '\n'; // 函数模板参数自动推导
    std::cout << equivalent<double>(1, 2) << '\n';
    std::cin.get();    
    return 0;
}
