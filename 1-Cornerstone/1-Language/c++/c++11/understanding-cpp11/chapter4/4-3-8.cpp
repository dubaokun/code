#include <type_traits>
using namespace std;

typedef double (*func)();
 
int main() {
    result_of<func()>::type f;   // 由func()推导其结果类型
}
