class ConvType {
public:
    ConvType(int i) {};
    explicit ConvType(char c) = delete;  // 删除explicit的char构造函数
};

void Func(ConvType ct) {}

int main() {
    Func(3);
    Func('a');      // 可以通过编译

    ConvType ci(3);
    ConvType cc('a');   // 无法通过编译
}
    
