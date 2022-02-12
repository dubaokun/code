#define Max1(a, b) ((a) > (b)) ? (a) : (b)
#define Max2(a, b) ({ \
        auto _a = (a); \
        auto _b = (b); \
        (_a > _b) ? _a: _b; })

int main() {
    int m1 = Max1(1*2*3*4, 5+6+7+8);
    int m2 = Max2(1*2*3*4, 5+6+7+8);
}
    

