#include <iostream>
// ---- PROCEDURAL version: global data + free functions ----
constexpr long long MIN_BALANCE_PAISE = 5000;
long long balance = 20000;                       // Rs 200.00, global: anyone can change it

long long fareFor(int zone, bool peak)
{
    const long long base[] = {1000, 2000, 3000};
    long long f = base[zone];
    return peak ? f + f * 20 / 100 : f;
}
bool canTravel(long long f) { return balance - f >= MIN_BALANCE_PAISE; }
void pay(long long f)
{
    if (canTravel(f)) { balance -= f; std::cout << "paid " << f << ", balance " << balance << '\n'; }
    else              { std::cout << "denied " << f << ", balance " << balance << '\n'; }
}
int main()
{
    pay(fareFor(2, true));    // Outer, peak
    pay(fareFor(1, false));   // Middle
    pay(fareFor(2, true));    // Outer, peak
    pay(fareFor(2, true));    // Outer, peak
    balance -= 99999;         // nothing stops this line
    std::cout << "after careless line: " << balance << '\n';
}
