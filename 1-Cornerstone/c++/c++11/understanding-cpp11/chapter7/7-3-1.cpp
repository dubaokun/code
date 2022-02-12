int main() {
    int girls = 3, boys = 4;
    auto totalChild = [](int x, int y)->int{ return x + y; }; 
    return totalChild(girls, boys);
}
