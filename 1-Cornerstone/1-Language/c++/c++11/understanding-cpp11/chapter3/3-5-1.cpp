#include <vector>
#include <map>
using namespace std;

int a[] = {1, 3, 5};        // C++98 - 通过, C++11 - 通过
int b[] {2, 4, 6};          // C++98 - 失败, C++11 - 通过
vector<int> c{1, 3, 5};     // C++98 - 失败, C++11 - 通过
map<int, float> d = {{1, 1.0f}, {2, 2.0f} , {5, 3.2f}}; // C++98 - 失败, C++11 - 通过 
