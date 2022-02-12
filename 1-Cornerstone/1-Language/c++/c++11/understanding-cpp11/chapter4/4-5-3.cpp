#include <iostream>
using namespace std;

int main() {
    int arr[5] = { 1, 2, 3, 4, 5 };
    for (int & e: arr)
        e *= 2;

    for (int & e: arr)
        cout << e << '\t';
}
