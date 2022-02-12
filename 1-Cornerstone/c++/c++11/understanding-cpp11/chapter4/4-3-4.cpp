enum class{K1, K2, K3}anon_e;   // 匿名的强类型枚举

union {
    decltype(anon_e) key;
    char* name;
}anon_u;    // 匿名的union

struct {
    int d;
    decltype(anon_u) id;
}anon_s[100];   // 匿名的struct数组


int main() {
    decltype(anon_s) as;
    as[0].id.key = decltype(anon_e)::K1;   // 引用匿名强类型枚举中的值
}
