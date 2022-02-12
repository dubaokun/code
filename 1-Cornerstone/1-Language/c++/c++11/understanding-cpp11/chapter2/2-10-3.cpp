struct Base {
    virtual void Turing() = 0;
    virtual void Dijkstra() = 0;
    virtual void VNeumann(int g) = 0;
    virtual void DKnuth() const;
    void Print();
};

struct DerivedMid: public Base {
    // void VNeumann(double g);
    // 接口被隔离了，曾想多一个版本的VNeumann函数
};

struct DerivedTop : public DerivedMid {
    void Turing() override;
    void Dikjstra() override;           // 无法通过编译，拼写错误，并非重载
    void VNeumann(double g) override;   // 无法通过编译，参数不一致，并非重载
    void DKnuth() override;             // 无法通过编译，常量性不一致，并非重载
    void Print() override;              // 无法通过编译，非虚函数重载
};
