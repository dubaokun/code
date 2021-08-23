#include "helloworld.pb.h"

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    Order order;
    //order.set_time(123456);
    order.set_userid(123);
    order.set_price(100.1f);
    order.set_desc("a test order");
    order.set_ext("hello world");

    string sOrder;
    order.SerializeToString(&sOrder);    // string仅仅是作为载体，实际存储的是二进制
    
    std::cout << "==================" << std::endl;
    std::cout << sOrder << std::endl;
    std::cout << "==================" << std::endl;

    FILE * fp = fopen("./data", "w+");
    if (NULL == fp) {
        cout << "fopen file fail" << endl;
        return -1;
    }

    int write_bytes = fwrite(sOrder.c_str(), 1, sOrder.size(), fp);
    if (write_bytes != sOrder.size()) {
        cout << "write_bytes=" << write_bytes << " sOrder.size()=" << sOrder.size() << endl;
        return -2;
    }

    fclose(fp);

    Order order2;
    if(order2.ParseFromString(sOrder)) {
        cout << order2.time() << endl;
        cout << order2.userid() << endl;
        cout << order2.price() << endl;
        cout << order2.desc() << endl;
        cout << order2.ext() << endl;
    } else {
        cout << "ParseFromString error" << endl;
    }

    return 0;
}
