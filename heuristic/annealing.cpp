#include <bits/stdc++.h>

void solve_annealing() {
    const auto t_start = std::chrono::system_clock::now();
    const auto T_LIMIT = std::chrono::milliseconds(2000);

    constexpr double ALPHA = 0.9999995;
    double temp = 1000;

    constexpr int n_time = 1000;
    int i_time = 0;

    int64_t count = 0, update_count = 0;
    while (true) {
        /*
             *- code -* 
        */
        ++count;
        ++i_time;
        if (i_time == n_time) {
            if (std::chrono::system_clock::now() - t_start >= T_LIMIT) {
                break;
            }
            i_time = 0;
        }
    }
    std::cerr << "count:\t" << count << "\n";
    std::cerr << "update:\t" << update_count << "\n";
    std::cerr << "temp:\t" << temp << "\n";
}