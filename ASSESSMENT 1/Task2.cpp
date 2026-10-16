#include <iostream>
using namespace std;

// ---------- Constants ----------
constexpr int MIN_BALANCE = 50;          // must remain after journey
constexpr double PEAK_SURCHARGE = 0.20;  // 20% surcharge
constexpr double CONCESSION = 0.50;      // 50% off for students/seniors

// ---------- Enum Class for Zones ----------
enum class Zone {
    Inner = 0,
    Middle = 1,
    Outer = 2,
    Extended = 3
};

// ---------- Fare Table ----------
constexpr int FARE_TABLE[] = {10, 20, 30, 40}; // fares for zones

// ---------- Example Function ----------
double calculateFare(Zone z, bool peak, bool concession) {
    int baseFare = FARE_TABLE[static_cast<int>(z)];
    double fare = baseFare;

    if (peak) fare += baseFare * PEAK_SURCHARGE;
    if (concession) fare *= CONCESSION;

    return fare;
}

int main() {
    double fare = calculateFare(Zone::Outer, true, true);
    cout << "Fare: Rs " << fare << endl;
    return 0;
}
