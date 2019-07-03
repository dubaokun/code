#include <iostream>
using namespace std;

struct Date {
    constexpr Date(int y, int m, int d):
        year(y), month(m), day(d) {}

    constexpr int GetYear() { return year; }
    constexpr int GetMonth() { return month; }
    constexpr int GetDay() { return day; }

private:
    int year;
    int month;
    int day;
};

constexpr Date PRCfound {1949, 10, 1};
constexpr int foundmonth = PRCfound.GetMonth();

int main() { cout << foundmonth << endl; }  // 10
