extern int z;
extern float c;
void Calc(int& , int, float &, float);

void TestCalc() {
    int x, y = 3;
    float a, b = 4.0;

    int success = 0;

    auto validate = [&]() -> bool
    {
        if ((x == y + z) && (a == b + c))
            return 1;
        else
            return 0;
    };

    Calc(x, y, a, b);
    success += validate();

    y = 1024;
    b = 1e13;

    Calc(x, y, a, b);
    success += validate();
}
