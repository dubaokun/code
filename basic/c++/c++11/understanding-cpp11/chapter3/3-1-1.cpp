struct A { A(int i) {} };
struct B : A { 
    B(int i): A(i), d(i) {} 
    int d;
};

