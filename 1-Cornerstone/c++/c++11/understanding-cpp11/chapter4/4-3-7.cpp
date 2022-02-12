#include <map>
using namespace std;

int hash(char*);

//map<char*, decltype(hash)> dict_key;    // 无法通过编译
map<char*, decltype(hash(nullptr))> dict_key;
