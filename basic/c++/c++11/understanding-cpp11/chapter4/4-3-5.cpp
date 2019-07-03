// s的类型被声明为decltype(t1 + t2)
template<typename T1, typename T2>
void Sum(T1 & t1, T2 & t2, decltype(t1 + t2) & s) {
    s = t1 + t2;
}

int main() {
    int a = 3;
    long b = 5;
    float c = 1.0f, d = 2.3f;

    long e;
    float f; 
    Sum(a, b, e);   // s的类型被推导为long
    Sum(c, d, f);   // s的类型被推导为float
}
