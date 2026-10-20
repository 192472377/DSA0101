#include <iomanip>
#include <iostream>
#include <limits>

void printMoney(long long paise)                 // Rs 36.00 with <iomanip>
{
    std::cout << "Rs " << std::setw(4) << paise / 100 << '.'
              << std::setfill('0') << std::setw(2) << paise % 100 << std::setfill(' ');
}
bool readInt(const char* prompt, int lo, int hi, int& out)
{
    for (int attempt = 1; attempt <= 3; ++attempt) {
        std::cout << prompt;
        if (std::cin >> out && out >= lo && out <= hi) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        if (std::cin.eof()) return false;
        std::cin.clear();                                                   // clear fail state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
        std::cout << "  invalid input, enter " << lo << " to " << hi << " (attempt " << attempt << " of 3)\n";
    }
    return false;
}
int main()
{
    constexpr long long BASE[] = {1000, 2000, 3000};
    long long balance = 10000;
    int recharge = 0, zone = 0, hour = 0;
    if (!readInt("Recharge in rupees (0-5000): ", 0, 5000, recharge)) return 1;
    balance += recharge * 100LL;
    if (!readInt("Zone (0=Inner 1=Middle 2=Outer): ", 0, 2, zone)) return 1;
    if (!readInt("Hour (0-23): ", 0, 23, hour)) return 1;

    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    long long fare = BASE[zone] + (peak ? BASE[zone] * 20 / 100 : 0);

    std::cout << "\n--- JOURNEY REPORT ---\n";
    std::cout << std::left << std::setw(14) << "Zone"    << std::right; std::cout << std::setw(8) << zone << '\n';
    std::cout << std::left << std::setw(14) << "Hour"    << std::right; std::cout << std::setw(8) << hour << '\n';
    std::cout << std::left << std::setw(14) << "Peak"    << std::right << std::setw(8) << std::boolalpha << peak << '\n';
    std::cout << std::left << std::setw(14) << "Fare"    << std::right; printMoney(fare);    std::cout << '\n';
    std::cout << std::left << std::setw(14) << "Balance" << std::right; printMoney(balance - fare); std::cout << '\n';
    std::cout << "Fare as double: " << std::fixed << std::setprecision(2) << fare / 100.0 << '\n';
}

