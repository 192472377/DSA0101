#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

// Fare table read from a configuration file when the gate starts.
std::vector<long long> loadFares(const char* path)
{
    std::vector<long long> fares;
    std::ifstream in(path);
    long long v;
    while (in >> v) fares.push_back(v);
    return fares;
}
int main()
{
    { std::ofstream out("fares.cfg"); out << "1000 2000 3000 6000\n"; }   // paise per zone

    const int REPEATS = 100000;
    std::size_t zones = 0;
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < REPEATS; ++i) zones = loadFares("fares.cfg").size();
    auto t1 = std::chrono::steady_clock::now();
    double perLoadUs = std::chrono::duration<double, std::micro>(t1 - t0).count() / REPEATS;

    std::vector<long long> fares = loadFares("fares.cfg");
    std::cout << "zones read: " << zones << ", fares:";
    for (long long f : fares) std::cout << ' ' << f;
    std::cout << '\n' << "memory for fares: " << fares.size() * sizeof(long long) << " bytes\n";
    std::cout << "start-up read time: about " << perLoadUs << " microseconds per load\n";
    std::cout << "(done once per gate start, not per journey)\n";
}
