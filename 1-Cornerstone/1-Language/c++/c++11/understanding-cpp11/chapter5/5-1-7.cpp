enum struct { General, Light, Medium, Heavy } weapon;

int main() {
    weapon = General;   // 无法编译通过
    bool b = (weapon == weapon::General);   // 无法编译通过
    return 0;
}

