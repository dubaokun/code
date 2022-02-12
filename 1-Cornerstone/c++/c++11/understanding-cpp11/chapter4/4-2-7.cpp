template<typename T1, typename T2>
double Sum(T1 & t1, T2 & t2) {
    auto s = t1 + t2;   // s的类型会在模板实例化时被推导出来
    return s; 
} 

int main() {
    int a = 3;
    long b = 5;
    float c = 1.0f, d = 2.3f;
    
    auto e = Sum(a, b); // s的类型被推导为long
    auto f = Sum(c, d); // s的类型被推导为float
}
