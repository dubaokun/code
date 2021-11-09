#include <iostream>

using namespace std;

class G {
public:
  virtual void func(const char *) { cout << "base func" << endl;}
};

class H: G
{
public:
  virtual void func(double) { cout << "son func" << endl;}
};

int main(int argc, char ** argv) {
    H h;
    h.func("1,0");
    h.func(5.0);
    return 0;
}
