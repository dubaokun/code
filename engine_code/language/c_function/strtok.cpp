#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void MySplit(char * const str_ori, const char * str_pattern, vector<string>& vec_str) {
    if (NULL == str_ori || NULL == str_pattern) {
        return;
    }

    char * p = strtok(str_ori, str_pattern);
    while (NULL != p) {
        vec_str.push_back(p);
        p = strtok(NULL, str_pattern);
    }
}

void Print(vector<string>& vec_str) {
    for (vector<string>::iterator iter = vec_str.begin(); iter != vec_str.end(); ++iter) {
        cout << *iter << endl;
    }
}

int main(void)
{
    char s[] = "ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
    const char *delim = "-: ";
    
    vector<string> vec_str;
    MySplit(s, delim, vec_str); 
    Print(vec_str);
    
    cout << "===================================" << endl;

    cout << s << endl;

    return 0;

    char *p;

    printf("%s ", strtok(s, delim));
    printf("\n");        

    while((p = strtok(NULL, delim)))
        printf("%s ", p);
    printf("\n");                                  
    
    return 0;                             
}
