/*
 *
 *
 * assign 允许在不同的容器之间进行赋值
 *
 *
 *
 *
 */
#include <list>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    list<string> names;
    vector<const char*> oldstyle = { "I","love","you" };

    names.assign(oldstyle.begin(), oldstyle.end());
    list<string>::iterator it;

    for (auto it = names.begin();  it != names.end(); it++)
        cout << *it << " ";
    cout << endl;

    return 0;
}
