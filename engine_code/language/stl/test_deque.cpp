#include <iostream>
#include <deque>

using namespace std;
 
 
int main(int argc, char** argv)
{
    deque<int> myDeque;
    myDeque.push_front(1);
    myDeque.push_front(2);
    myDeque.push_back(3);
    myDeque.push_back(4);
    myDeque.push_back(5);
    myDeque.push_front(6);
    myDeque.pop_back();
    deque<int>::iterator myItor;
    for(myItor=myDeque.begin(); myItor!=myDeque.end(); myItor++)
        cout<<*myItor<<endl;
        
    return 0;
}
