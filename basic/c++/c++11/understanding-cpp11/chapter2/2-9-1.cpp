class Poly;
typedef Poly P;

class LiLei {
    friend class Poly;  // C++98 - 通过, C++11 - 通过 
};

class Jim {
    friend Poly;        // C++98 - 失败, C++11 - 通过
};

class HanMeiMei {
    friend P;           // C++98 - 失败, C++11 - 通过
};



