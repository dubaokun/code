
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<string.h>
#include <iomanip>
#define BUFFSIZE 2048
using namespace std;
const int SAMPLE = 1000001;
const int PARAMETER = 2;

int main(int argv,char *arg[]) 
{
    FILE *file= NULL;
    char buf[BUFFSIZE];
    if((file = fopen("data.txt", "r")) == NULL){
        cout << " open error " << endl;
    }
    double ** X = new double*[SAMPLE];
    for(int i = 0; i < SAMPLE; i++) {
      X[i] = new double[PARAMETER];
    }
    int i = 0;
    while(fgets(buf, BUFFSIZE, file)){
        cout << "________________BEGIN" << endl;
        int len= strlen(buf);
        buf[len-1]='\0';
        cout << buf << endl;
        cout << "======" << endl;
        string strs = buf;
        size_t pos = strs.find(" ");
        string temp = strs.substr(0, pos);
        strs = strs.substr(pos + 1, strs.size());
        cout << temp << " " << strs << endl;
        double a1 = stold(temp);
        double a2 = stod(strs);
        cout << a1 << " " << a2 << endl;
        X[i][0] = a1;
        X[i][1] = a2;
        cout << X[i][0] << " " << X[i][1] << endl;
        i++;
        cout << "________________END" << endl;

    }
    for (int i = 0; i < SAMPLE + 1; i++)
    {
            for (int j = 0; j < PARAMETER + 1; j++)
                cout << X[i][j] << " ";
            cout << endl;
        }
}
