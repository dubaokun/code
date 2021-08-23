#include "helloworld.pb.h"

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char ** argv)
{
    FILE * fp = fopen("../src/data", "r");
    if (NULL == fp) {
        cout << "fopen file fail" << endl;
        return -1;
    }

    char buffer[1024] = {0};
    int read_bytes = fread(buffer, 1, 1024, fp);
        
    cout << "read_bytes=" << read_bytes << endl;

    fclose(fp);
    
    cout << buffer << endl;

    Order order;
    if(order.ParseFromString(buffer)) {
        cout << order.time() << endl;
        cout << order.userid() << endl;
        cout << order.price() << endl;
        cout << order.desc() << endl;
        //cout << order.ext() << endl;
    } else {
        cout << "ParseFromString error" << endl;
    }

    return 0;
}
