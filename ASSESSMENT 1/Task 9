#include <iostream>
#include <optional>
#include <string>
#include <iomanip>

enum class Zone { Inner, Middle, Outer };
constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;

bool isPeakHour(int h) { return (h >= 8 && h < 10) || (h >= 17 && h < 20); }
long long fare(Zone z, int hour, bool concession)
{
    long long f = BASE_PAISE[static_cast<int>(z)];
    if (isPeakHour(hour)) f += f * PEAK_SURCHARGE_PERCENT / 100;
    if (concession) f -= f * CONCESSION_PERCENT / 100;
    return f;
}
bool canTravel(long long balance, long long f) { return balance - f >= MIN_BALANCE_PAISE; }

// ---- validation helpers for the invalid cases ----
std::optional<Zone> parseZone(int code)
{
    if (code < 0 || code > 2) return std::nullopt;
    return static_cast<Zone>(code);
}
std::optional<int> parseHour(const std::string& s)
{
    try {
        std::size_t used = 0;
        int h = std::stoi(s, &used);
        if (used != s.size() || h < 0 || h > 23) return std::nullopt;
        return h;
    } catch (...) { return std::nullopt; }
}
bool validRecharge(long long paise) { return paise > 0; }

int passed = 0, failed = 0;
void check(const std::string& name, long long expected, long long actual)
{
    bool ok = expected == actual;
    (ok ? passed : failed)++;
    std::cout << std::left << std::setw(34) << name << std::right << std::setw(7) << expected
              << std::setw(8) << actual << "   " << (ok ? "PASS" : "FAIL") << '\n';
}
int main()
{
    std::cout << std::left << std::setw(34) << "TEST CASE" << std::right << std::setw(7) << "EXPECT"
              << std::setw(8) << "ACTUAL" << "   RESULT\n";
    // normal journeys (paise)
    check("Inner  12:00 off-peak",            1000, fare(Zone::Inner, 12, false));
    check("Middle 12:00 off-peak",            2000, fare(Zone::Middle, 12, false));
    check("Outer  12:00 off-peak",            3000, fare(Zone::Outer, 12, false));
    check("Inner  09:00 peak",                1200, fare(Zone::Inner, 9, false));
    check("Middle 18:00 peak",                2400, fare(Zone::Middle, 18, false));
    check("Outer  09:00 peak",                3600, fare(Zone::Outer, 9, false));
    check("Outer  18:00 peak, student",       1800, fare(Zone::Outer, 18, true));
    // boundaries of the peak rule
    check("Outer  07:00 (just before peak)",  3000, fare(Zone::Outer, 7, false));
    check("Outer  08:00 (peak starts)",       3600, fare(Zone::Outer, 8, false));
    check("Outer  10:00 (peak ended)",        3000, fare(Zone::Outer, 10, false));
    check("Outer  17:00 (peak starts)",       3600, fare(Zone::Outer, 17, false));
    check("Outer  20:00 (peak ended)",        3000, fare(Zone::Outer, 20, false));
    // balance boundary: Rs 50 must remain
    check("balance 6000, fare 1000 -> allowed", 1, canTravel(6000, 1000));
    check("balance 5999, fare 1000 -> denied",  0, canTravel(5999, 1000));
    check("balance 6000, fare 1001 -> denied",  0, canTravel(6000, 1001));
    // invalid input
    check("unknown zone 7 rejected",            0, parseZone(7).has_value());
    check("zone -1 rejected",                   0, parseZone(-1).has_value());
    check("hour 'ab' rejected",                 0, parseHour("ab").has_value());
    check("hour '9x' rejected",                 0, parseHour("9x").has_value());
    check("hour '24' rejected",                 0, parseHour("24").has_value());
    check("hour '9' accepted",                  1, parseHour("9").has_value());
    check("recharge -500 rejected",             0, validRecharge(-500));
    std::cout << "\nPassed " << passed << ", failed " << failed << '\n';

    // five journeys with a hand-calculated total
    struct J { Zone z; int hour; bool conc; };
    J js[] = {{Zone::Inner, 7, false}, {Zone::Middle, 9, false}, {Zone::Outer, 12, false},
              {Zone::Outer, 18, true}, {Zone::Middle, 20, false}};
    long long total = 0, balance = 50000;
    for (const J& j : js) { long long f = fare(j.z, j.hour, j.conc); total += f; balance -= f; }
    std::cout << "\n5-journey total: " << total << " paise (hand: 10200), final balance " << balance
              << " paise (hand: 39800)\n";
}
