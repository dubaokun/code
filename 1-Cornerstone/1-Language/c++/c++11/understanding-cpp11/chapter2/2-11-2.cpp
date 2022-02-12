void DefParm(int m = 3) {}  // c++98 - 编译通过，c++11 - 编译通过
template <typename T = int> 
    class DefClass {};      // c++98 - 编译通过，c++11 - 编译通过
template <typename T = int> 
    void DefTempParm() {};  // c++98 - 编译失败，c++11 - 编译通过
