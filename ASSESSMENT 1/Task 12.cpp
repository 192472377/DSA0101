#include <iomanip>
#include <iostream>
#include <optional>
#include <string>

// ---------- constants: the only place a revision is made ----------
enum class Zone { Inner = 0, Middle = 1, Outer = 2, Airport = 3 };
constexpr int ZONE_COUNT = 4;
constexpr long long BASE_PAISE[ZONE_COUNT] = {1000, 2000, 3000, 6000};   // Airport Rs 60
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr int WEEKEND_DISCOUNT_PERCENT = 10;
constexpr int CONCESSION_PERCENT = 50;
constexpr long long MIN_BALANCE_PAISE = 5000;

constexpr int idx(Zone z) { return static_cast<int>(z); }
long long percentOf(long long amount, int percent) { return (amount * percent + 50) / 100; }  // nearest paisa
bool isPeakHour(int h) { return (h >= 8 && h < 10) || (h >= 17 && h < 20); }

// ---------- separate discount rule ----------
// Weekend: 10% off and NO peak surcharge. Weekday: peak surcharge applies. Concession is applied last.
long long fare(Zone z, int hour, bool weekend, bool concession)
{
    long long f = BASE_PAISE[idx(z)];
    if (weekend)                  f -= percentOf(f, WEEKEND_DISCOUNT_PERCENT);
    else if (isPeakHour(hour))    f += percentOf(f, PEAK_SURCHARGE_PERCENT);
    if (concession)               f -= percentOf(f, CONCESSION_PERCENT);
    return f;
}

// ---------- new Pass class ----------
class Pass {
    Zone a_, b_;
public:
    Pass(Zone a, Zone b) : a_(a), b_(b) {}
    bool covers(Zone from, Zone to) const
    {
        return (from == a_ || from == b_) && (to == a_ || to == b_);
    }
};

class SmartCard {
    long long balance_;
    std::optional<Pass> pass_;
public:
    explicit SmartCard(long long paise) : balance_(paise) {}
    void buyPass(const Pass& p) { pass_ = p; }
    bool passCovers(Zone from, Zone to) const { return pass_ && pass_->covers(from, to); }
    bool canTravel(long long f) const { return balance_ - f >= MIN_BALANCE_PAISE; }
    bool deduct(long long f) { if (!canTravel(f)) return false; balance_ -= f; return true; }
    long long balance() const { return balance_; }
};

struct Journey { Zone from, to; int hour; bool weekend; bool concession; };

// returns the fare charged, or -1 when denied
long long processJourney(SmartCard& card, const Journey& j)
{
    if (card.passCovers(j.from, j.to)) return 0;                 // unlimited inside the pass zones
    Zone farthest = idx(j.from) > idx(j.to) ? j.from : j.to;
    long long f = fare(farthest, j.hour, j.weekend, j.concession);
    return card.deduct(f) ? f : -1;
}

int passed = 0, failed = 0;
void expect(const std::string& name, long long want, long long got)
{
    bool ok = want == got;
    (ok ? passed : failed)++;
    std::cout << std::left << std::setw(46) << name << std::right << std::setw(6) << want
              << std::setw(7) << got << "  " << (ok ? "PASS" : "FAIL") << '\n';
}
int main()
{
    std::cout << std::left << std::setw(46) << "TEST CASE" << std::right << std::setw(6) << "WANT"
              << std::setw(7) << "GOT" << "  RESULT\n";
    expect("Airport weekday 12:00",                        6000, fare(Zone::Airport, 12, false, false));
    expect("Airport weekday 09:00 (peak +20%)",            7200, fare(Zone::Airport, 9, false, false));
    expect("Airport Saturday 09:00 (-10%, no surcharge)",  5400, fare(Zone::Airport, 9, true, false));
    expect("Outer Sunday 12:00 (-10%)",                    2700, fare(Zone::Outer, 12, true, false));
    expect("Middle Saturday 18:00 student (-10%, -50%)",    900, fare(Zone::Middle, 18, true, true));
    expect("Inner weekday 10:00 (peak ended)",             1000, fare(Zone::Inner, 10, false, false));

    SmartCard c1(30000);
    c1.buyPass(Pass(Zone::Inner, Zone::Middle));
    expect("Pass(Inner,Middle): Inner->Middle 09:00",         0, processJourney(c1, {Zone::Inner, Zone::Middle, 9, false, false}));
    expect("  balance unchanged",                         30000, c1.balance());
    expect("Pass(Inner,Middle): Inner->Outer 12:00",       3000, processJourney(c1, {Zone::Inner, Zone::Outer, 12, false, false}));
    expect("  balance after paying Outer",                27000, c1.balance());

    SmartCard c2(7000);
    expect("balance 7000, Airport 12:00 -> denied",          -1, processJourney(c2, {Zone::Inner, Zone::Airport, 12, false, false}));
    expect("  balance unchanged",                          7000, c2.balance());
    SmartCard c3(11000);
    expect("balance 11000, Airport 12:00 -> allowed",      6000, processJourney(c3, {Zone::Inner, Zone::Airport, 12, false, false}));
    expect("  Rs 50 left exactly",                         5000, c3.balance());

    std::cout << "\nPassed " << passed << ", failed " << failed << '\n';
}

