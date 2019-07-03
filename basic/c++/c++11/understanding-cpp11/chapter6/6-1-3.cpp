constexpr int f();
int a = f();
const int b = f();
constexpr int c = f();  // 无法通过编译
constexpr int f() { return 1; }
constexpr int d = f(); 

