#include <iostream>
using namespace std;

int main() {
    int arr[5] = { 1, 2, 3, 4, 5};
    int * p;
    for (p = arr; p < arr + sizeof(arr)/sizeof(arr[0]); ++p){
        *p *= 2;
    }
    for (p = arr; p < arr + sizeof(arr)/sizeof(arr[0]); ++p){
        cout << *p << '\t';
    }
}
