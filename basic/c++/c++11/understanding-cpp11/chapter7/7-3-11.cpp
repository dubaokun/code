int main(){
    int val;
    // 编译失败, 在const的lambda中修改常量
    auto const_val_lambda = [=]() { val = 3;};

    // 非const的lambda,可以修改常量数据
    auto mutable_val_lambda = [=]() mutable { val = 3;};  

    // 依然是const的lambda，不过没有改动引用本身
    auto const_ref_lambda = [&] { val = 3;};

    // 依然是const的lambda，通过参数传递val
    auto const_param_lambda = [&](int v) { v = 3;};
    const_param_lambda(val);

    return 0;
}
