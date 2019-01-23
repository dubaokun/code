#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct tagStudent
{
    int m_nID;
    int m_nScore;

    tagStudent& operator=(const tagStudent &b)
    {
        this->m_nID = b.m_nID;
        this->m_nScore = b.m_nScore;
        return *this;
    }

    tagStudent(const tagStudent &b)
    {
        this->m_nID = b.m_nID;
        this->m_nScore = b.m_nScore;
    }

    tagStudent(int nID, int nScore)
    {
        this->m_nID = nID;
        this->m_nScore = nScore;
    }

    void output() {
        cout << "m_nID=" << m_nID << endl;
        cout << "m_nScore" << m_nScore << endl;
    }

};


int main(int argc, char ** argv)
{
    tagStudent AStudent(2, 20);
    tagStudent BStudent(3, 80);

    // 在tagStudent中的拷贝构造和赋值函数中打断点会发现，拷贝构造调用了一次，赋值函数调用了两次
    std::swap(AStudent, BStudent);
    cout << "After swap begin!" << endl;
    AStudent.output();
    BStudent.output();
    cout << "After swap end!" << endl;
    int x = 10;  
    //vector<int> myContainer(10000, x); 
    string myContainer(10000,'\0');

    //这里打印仅仅是元素的个数不是内存大小  
    cout << "myContainer size :"  << myContainer.size() << ", capacity:"<< myContainer.capacity()<< endl; 

    myContainer.clear();
    cout << "after clear size :"  << myContainer.size() << ", capacity:"<< myContainer.capacity()<< endl;  
    //swap交换函数释放内存：vector<T>().swap(X);  
    //T:int ; myvertor代表X  
    //vector<int>().swap(myContainer);
    //string().swap(myContainer); 
    string tmp(100, 'a');
    tmp.swap(myContainer);

    //两个输出仅用来表示swap前后的变化  
    cout << "after swap size :"  << myContainer.size() << ", capacity:"<< myContainer.capacity()<< endl;  
    cout << "after swap size :"  << tmp.size() << ", capacity:"<< tmp.capacity()<< endl;  
    // 并不是所有的STL容器的clear成员函数的行为都和vector一样。事实上，其他容器的clear成员函数都会释放其内存。
    //
    string().swap(myContainer); 
    cout << "free memory" << endl;
    cout << "after swap size :"  << myContainer.size() << ", capacity:"<< myContainer.capacity()<< endl; 
 }
