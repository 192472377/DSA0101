#include <iostream>
#include <climits>
using namespace std;

int main() {
    // Data type choices
    bool isPeak = true;                 // peak hour flag
    char zoneCode = 'I';                // zone code (Inner)
    int farePaise = 1000;               // fare stored in paise (Rs 10.00)
    long long balancePaise = 20000;     // balance stored in paise (Rs 200.00)
    unsigned int journeyCount = 3000000; // daily journeys
    int hour = 9;                       // journey time hour

    // sizeof evidence
    cout << "sizeof(bool): " << sizeof(bool) << endl;
    cout << "sizeof(char): " << sizeof(char) << endl;
    cout << "sizeof(int): " << sizeof(int) << endl;
    cout << "sizeof(long long): " << sizeof(long long) << endl;
    cout << "sizeof(unsigned int): " << sizeof(unsigned int) << endl;

    // Precision problem demonstration
    double wrongMoney = 0.1; // rupees
    for(int i=0; i<10; i++) wrongMoney += 0.1; // floating-point error
    cout << "Double rupees total: " << wrongMoney << endl;

    long long correctMoney = 0; // paise
    for(int i=0; i<10; i++) correctMoney += 10; // exact integer addition
    cout << "Integer paise total: " << correctMoney << " paise" << endl;

    // Range evidence
    cout << "INT_MAX: " << INT_MAX << endl;
    cout << "LONG_LONG_MAX: " << LLONG_MAX << endl;

    return 0;
}
