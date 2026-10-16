#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Passenger {
    string name;
    int age;
    bool student;
    bool senior;
public:
    Passenger(string n, int a, bool s, bool sr) 
        : name(n), age(a), student(s), senior(sr) {}

    bool eligibleForConcession() const {
        return student || senior;
    }
};

class SmartCard {
    double balance;
public:
    SmartCard(double b) : balance(b) {}

    bool hasSufficientBalance(double fare) const {
        return (balance - fare) >= 50;
    }

    void deductFare(double fare) {
        if(hasSufficientBalance(fare)) {
            balance -= fare;
            cout << "Fare deducted: Rs " << fare 
                 << ", Remaining balance: Rs " << balance << endl;
        } else {
            cout << "Insufficient balance for journey!" << endl;
        }
    }
};

class FareTable {
    double zoneFare[4] = {10, 20, 30, 40}; // 4 zones
public:
    double getFareForZone(int zone) const {
        return zoneFare[zone];
    }
};

class Journey {
    int startZone, endZone;
    int hour;
public:
    Journey(int s, int e, int h) : startZone(s), endZone(e), hour(h) {}

    bool isPeakHour() const {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }

    double calculateFare(const FareTable& ft, const Passenger& p) const {
        int farthestZone = max(startZone, endZone);
        double fare = ft.getFareForZone(farthestZone);

        if(isPeakHour()) fare *= 1.2; // 20% surcharge
        if(p.eligibleForConcession()) fare *= 0.5; // 50% concession

        return fare;
    }
};

int main() {
    Passenger p("Rahul", 20, true, false);
    SmartCard card(200);
    FareTable ft;
    Journey j(0, 2, 9); // Inner to Outer at 9 AM (peak)

    double fare = j.calculateFare(ft, p);
    card.deductFare(fare);

    return 0;
}
