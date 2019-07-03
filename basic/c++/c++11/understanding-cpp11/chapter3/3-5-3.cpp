#include <initializer_list>
using namespace std;

void Fun(initializer_list<int> iv){ }

int main() {
    Fun({1, 2});
    Fun({}); // 空列表
}
