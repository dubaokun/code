class OuterType{
    struct InnerType { int i; };

    InnerType GetInner();
    InnerType it;
};
    
// 可以不写OuterType::InnerType
auto OuterType::GetInner() -> InnerType {
    return it;
}
