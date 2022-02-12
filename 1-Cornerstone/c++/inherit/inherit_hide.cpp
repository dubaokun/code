#include <iostream>
#include <string>

using namespace std;


class Persion {
public:
    Persion(string name) { _name = name;}
    virtual ~Persion() {}

    void speak(int count) { cout << "Persion speak!" << endl;}

private:
    string _name;
};


class NBPersion : public Persion {
public:
    NBPersion(string name) : Persion(name) {}
    virtual ~NBPersion() {}

    void speak(int count, string str) { cout << "NBPersion speak!" << endl; }
};

int main(int argc, char ** argv) {
    NBPersion p1("dubaokun");
    p1.speak(1); 
    return 0;
}
