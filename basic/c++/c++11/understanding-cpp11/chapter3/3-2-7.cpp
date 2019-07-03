#include <iostream>
using namespace std;

class DCExcept {
public:
    DCExcept(double d)
        try : DCExcept(1, d) { 
            cout << "Run the body." << endl;
            // 其它初始化
        }
        catch(...) {
            cout << "caught exception." << endl;
        }
private:
    DCExcept(int i, double d){ 
        cout << "going to throw!" << endl;
        throw 0; 
    }
    int type;
    double data;
};

int main() {
    DCExcept a(1.2);
}
