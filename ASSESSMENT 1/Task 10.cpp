#include <chrono>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

// One journey = (zone, peak, concession); the 12 combinations repeat in a fixed pattern.
constexpr long long BASE_PAISE[] = {1000, 2000, 3000};
long long farePaise(int zone, bool peak, bool conc)
{
    long long f = BASE_PAISE[zone];
    if (peak) f += f * 20 / 100;
    if (conc) f -= f * 50 / 100;
    return f;
}
double fareRupees(int zone, bool peak, bool conc)          // same rule in double rupees
{
    double f = 10.0 * (zone + 1);
    if (peak) f *= 1.2;
    if (conc) f *= 0.5;
    return f;
}
int main()
{
    const long long counts[] = {20000, 500000, 3000000};
    std::cout << std::fixed << std::setprecision(6);
    for (long long n : counts) {
        long long paiseTotal = 0;
        double rupeeTotal = 0.0;
        int intTotal = 0; bool overflowed = false; long long firstOverflow = 0;
        for (long long i = 0; i < n; ++i) {
            int zone = static_cast<int>(i % 3);
            bool peak = (i / 3) % 2 == 1;
            bool conc = (i / 6) % 2 == 1;
            long long fp = farePaise(zone, peak, conc);
            paiseTotal += fp;
            rupeeTotal += fareRupees(zone, peak, conc);
            if (!overflowed && __builtin_add_overflow(intTotal, static_cast<int>(fp), &intTotal)) {
                overflowed = true; firstOverflow = i + 1;
            }
        }
        std::cout << "N = " << n << '\n';
        std::cout << "  long long paise total : " << paiseTotal << " paise = Rs " << paiseTotal / 100.0 << '\n';
        std::cout << "  double rupees total   : Rs " << rupeeTotal << '\n';
        std::cout << "  difference (paise)    : " << std::scientific << std::setprecision(3)
                  << std::fabs(rupeeTotal * 100.0 - static_cast<double>(paiseTotal)) << std::fixed << std::setprecision(6) << '\n';
        std::cout << "  int paise total       : " << (overflowed ? "OVERFLOW at journey " + std::to_string(firstOverflow) : std::string("fits")) << '\n';
    }
    std::cout << "INT_MAX = " << INT_MAX << " paise = Rs " << INT_MAX / 100.0 << '\n';

    // stress: a fare with a fraction that has no exact binary form (Rs 10.10), 3,000,000 times
    double d = 0.0; long long p = 0;
    for (int i = 0; i < 3000000; ++i) { d += 10.10; p += 1010; }
    std::cout << std::setprecision(9) << "stress  double Rs " << d << "   paise Rs " << p / 100.0 << '\n';
    std::cout << std::scientific << std::setprecision(3) << "stress  error = Rs " << std::fabs(d - p / 100.0) << '\n';
}
