#include <iostream>
using namespace std;

union T{
    static long Get() { return 32; }
};

int main(){
    cout << T::Get() << endl;
}
