template<typename T1, typename T2>
void Sum(T1 & t1, T2 & t2, decltype(t1 + t2) & s) {
    s = t1 + t2;
}

void Sum(int a[], int b[], int c[]){
    // 数组版本
}

int main() {
    int a[5], b[5], c[5];
    Sum(a, b, c);   // 选择数组版本

    int d, e, f;
    Sum(d, e, f);   // 选择模板的实例化版本
}
