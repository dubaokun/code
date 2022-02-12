enum BitSet { 
    V0  =   1 << 0, 
    V1  =   1 << 1, 
    V2  =   1 << 2, 
    VMAX =  1 << 3 
};

// 重定义操作符"|", 以保证返回的BitSet值不超过枚举的最大值
const BitSet operator|(BitSet x, BitSet y) { 
    return static_cast<BitSet>(((int)x | y) & (VMAX - 1)); 
}

template <int i = V0 | V1>  // 无法通过编译
    void LikeConst(){}

