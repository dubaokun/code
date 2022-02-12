template <int I> struct A {};

char xxx(int);
char xxx(float);

template <class T> A<sizeof(xxx((T)0))> f(T){}

int main() {
    f(1);
}
