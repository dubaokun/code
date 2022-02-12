class DefaultedOptr{
public:
    // 使用"= default"来产生缺省版本
    DefaultedOptr() = default;   

    // 这里没使用"= default"
    DefaultedOptr & operator = (const DefaultedOptr & );
};

// 在类定义外用"= default"来指明使用缺省版本
inline DefaultedOptr & 
DefaultedOptr::operator =( const DefaultedOptr & ) = default; 
