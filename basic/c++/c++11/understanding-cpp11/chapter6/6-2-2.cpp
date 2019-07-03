template <typename... Elements> class tuple;        // 变长模板的声明

template<typename Head, typename... Tail>           // 递归的偏特化定义
class tuple<Head, Tail...> : private tuple<Tail...> {
    Head head;
};

template<> class tuple<> {};                        // 边界条件

