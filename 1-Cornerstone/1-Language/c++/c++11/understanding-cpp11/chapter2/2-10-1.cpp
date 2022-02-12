#include <iostream>
using namespace std;

class MathObject{ 
public:
    virtual double Arith() = 0;
    virtual void Print() = 0; 
};

class Printable : public MathObject{
public:
   double Arith() = 0;
   void Print() // C++98中我们无法阻止该接口被重写
   {
       cout << "Output is: " << Arith() << endl;
   }
};

class Add2 : public Printable {
public:
    Add2(double a, double b): x(a), y(b) {}
    double Arith() { return x + y; }
private:
    double x, y;
};

class Mul3 : public Printable {
public:
    Mul3(double a, double b, double c): x(a), y(b), z(c) {}
    double Arith() { return x * y * z; }
private:
    double x, y, z;
};

