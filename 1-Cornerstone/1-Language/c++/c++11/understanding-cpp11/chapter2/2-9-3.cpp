// 为了方便测试，做了危险的定义
#ifdef UNIT_TEST
#define private public
#endif

class Defender {
public:
    void Defence(int x, int y){}
    void Tackle(int x, int y){}

private:
    int pos_x = 15;
    int pos_y = 0;
    int speed = 2;
    int stamina = 120;
};

class Attacker {
public:
    void Move(int x, int y){}
    void SpeedUp(float ratio){}

private:
    int pos_x = 0;
    int pos_y = -30;
    int speed = 3;
    int stamina = 100;
};

#ifdef UNIT_TEST
class Validator {
public:
    void Validate(int x, int y, Defender & d){}
    void Validate(int x, int y, Attacker & a){}
};

int main() {
    Defender d;
    Attacker a;
    a.Move(15, 30);
    d.Defence(15, 30);
    a.SpeedUp(1.5f);
    d.Defence(15, 30);
    Validator v;
    v.Validate(7, 0, d);
    v.Validate(1, -10, a);
    return 0;
}
#endif
