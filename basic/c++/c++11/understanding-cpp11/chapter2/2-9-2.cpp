class P;

template <typename T> class People {
    friend T;
};

People<P> PP;   // 类型P在这里是People类型的友元
People<int> Pi; // 对于int类型模版参数，友元声明被忽略
