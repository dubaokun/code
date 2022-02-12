namespace ns_adl{
    struct A{};
    void ADLFunc(A a){} // ADLFunc定义在namespace ns_adl中
}

int main() {
    ns_adl::A a;
    ADLFunc(a); // ADLFunc无需声明名字空间
}


