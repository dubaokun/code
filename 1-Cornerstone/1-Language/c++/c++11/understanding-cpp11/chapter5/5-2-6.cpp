#include <memory>
using namespace std;

int main() {
    int *p = new int;
    declare_reachable(p);   // 在p被隐藏之前声明为可达的
    int *q = (int*)((long long)p ^ 2012); 
    // 解除可达声明
    q = undeclare_reachable<int>((int*)((long long)q ^ 2012));    
    *q = 10;
}
