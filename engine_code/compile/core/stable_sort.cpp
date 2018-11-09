#include <stdlib.h>
#include <time.h>

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;


class CompareData
{
public:
    CompareData() {};
    ~CompareData() {};

public:
    bool operator() (const int& i_idx, const int& r_idx) const {
        int i = rand();
        int j = rand() + 3;
        if (i >= j)
            return true;
        else
            return false;
    }

};

int main(int argc, char ** argv) {
    srand((unsigned)time(NULL));  
    CompareData compare;
    vector<int> vec_;
    for(int i = 0; i < 1000000; ++i) {
        vec_.push_back(i);
    }

    std::stable_sort(vec_.begin(), vec_.end(), compare);
}
