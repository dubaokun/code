#include <vector>
using namespace std;

int main() {
    vector<int> vec;
    typedef decltype(vec.begin()) vectype;

    vectype i;  // 这是auto无法做到的
    for (i = vec.begin(); i < vec.end(); i++) {
        // 做一些事情
    }

    for (decltype(vec)::iterator i = vec.begin(); i < vec.end(); i++) {
        // 做一些事情
    }
}
