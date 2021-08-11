#include <bits/stdc++.h>

struct XorShift {
    uint32_t x = 123456789;
    uint32_t y = 362436069;
    uint32_t z = 521288629;
    uint32_t w = 88675123;
    double urand(void) noexcept {
        uint32_t t;
        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        w ^= t ^ (t >> 8) ^ (w >> 19);
        return w / 4294967296.0;
    }
    // note: [a, b]
    int randint(int a, int b) noexcept {
        return static_cast<int>(urand() * (b - a + 1)) + a;
    }
};

template <class T>
class TSP {
private:
    std::vector<int> sol, vers;
    T sol_cost;
    const std::vector<std::vector<T>> DIST;
    const int N;
    XorShift random;
    static constexpr T INF = std::numeric_limits<T>::max();
    static constexpr int TH_EXACTLY = 18;

public:
    explicit TSP(int n, const std::vector<std::vector<T>>& dist)
        : DIST(dist), N(n) {
        sol.resize(N);
        iota(sol.begin(), sol.end(), 0);
        vers.resize(N);
        iota(vers.begin(), vers.end(), 0);
    }

    const std::vector<int>& get_sol() const noexcept { return sol; }
    T get_cost() const noexcept { return sol_cost; }

    void solve_exactly() {
        std::vector dp(1u << N, std::vector<T>(N, INF));
        std::vector pre(1u << N, std::vector<int>(N, -1));
        dp[0][0] = T(0);
        for (uint32_t mask = 0; mask < 1u << N; mask++) {
            for (int i = 0; i < N; i++) {
                if (~mask >> i & 1) continue;
                for (int j = 0; j < N; j++) {
                    if (i == j) continue;
                    uint32_t pre_mask = mask & ~(1u << i);
                    T pre_cost = dp[pre_mask][j];
                    if (pre_cost == INF) continue;
                    if (dp[mask][i] > pre_cost + DIST[j][i]) {
                        dp[mask][i] = pre_cost + DIST[j][i];
                        pre[mask][i] = j;
                    }
                }
            }
        }
        {
            uint32_t mask = (1u << N) - 1;
            int cur = 0;
            for (int i = N - 1; i >= 0; i--) {
                sol[i] = pre[mask][cur];
                mask &= ~(1u << cur);
                cur = sol[i];
            }
        }
        sol_cost = dp[(1u << N) - 1][0];
    }
    // arguments:
    //   time_limit: [ms]
    void solve_heuristic(int time_limit) {
        const auto t_start = std::chrono::system_clock::now();
        const auto time_limit_chrono = std::chrono::milliseconds(time_limit);
        T cost = calc_cost();
        T best_cost = cost;
        auto best_sol = sol;
        while (std::chrono::system_clock::now() - t_start < time_limit_chrono) {
            auto pre = sol;
            T diff = double_bridge();
            while (true) {
                bool update = false;
                for (int i = 0; i < N; i++) {
                    for (int j = i + 1; j < N; j++) {
                        T d = calc_diff_two_opt(i, j);
                        if (d < 0) {
                            update = true;
                            apply_two_opt(i, j);
                            diff += d;
                        }
                    }
                }
                if (!update) {
                    break;
                }
            }
            if (diff < 0) {
                cost += diff;
                if (cost < best_cost) {
                    best_sol = sol;
                    best_cost = cost;
                }
            } else {
                sol = std::move(pre);
            }
        }
        std::swap(sol, best_sol);
        sol_cost = best_cost;
    }
    // arguments:
    //   timei_limit: [ms]
    void solve(int time_limit) {
        if (N <= TH_EXACTLY) {
            solve_exactly();
        } else {
            solve_heuristic(time_limit);
        }
    }

private:
    std::array<int, 4> choose_4() {
        std::array<int, 4> res;
        for (int i = 0; i < 4; i++) {
            int j = random.randint(i, N - 1);
            std::swap(vers[i], vers[j]);
            res[i] = vers[i];
        }
        return res;
    }

    T calc_diff_two_opt(int i, int j) const {
        if (i > j) std::swap(i, j);
        if (i == 0 && j == N - 1) {
            return T(0);
        }
        int ii = i - 1, jj = j + 1;
        if (ii < 0) ii = N - 1;
        if (jj == N) jj = 0;
        T res = T(0);
        res += DIST[sol[ii]][sol[j]] + DIST[sol[i]][sol[jj]];
        res -= DIST[sol[ii]][sol[i]] + DIST[sol[j]][sol[jj]];
        return res;
    }

    void apply_two_opt(int i, int j) {
        if (i > j) std::swap(i, j);
        std::reverse(sol.begin() + i, sol.begin() + j + 1);
    }

    T double_bridge() {
        auto chosen = choose_4();
        std::sort(chosen.begin(), chosen.end());
        const auto [x0, x1, x2, x3] = chosen;
        int y0 = x0 + 1, y1 = x1 + 1, y2 = x2 + 1, y3 = x3 + 1;
        if (y3 == N) y3 = 0;
        T res = T(0);
        res += DIST[sol[x0]][sol[y2]] + DIST[sol[x1]][sol[y3]] + DIST[sol[x2]][sol[y0]] + DIST[sol[x3]][sol[y1]];
        res -= DIST[sol[x0]][sol[y0]] + DIST[sol[x1]][sol[y1]] + DIST[sol[x2]][sol[y2]] + DIST[sol[x3]][sol[y3]];
        std::vector<int> sol_tmp(N);
        if (y3 == 0) y3 = N;
        auto itr = sol_tmp.begin();
        itr = std::copy(sol.begin(), sol.begin() + x0 + 1, itr);
        itr = std::copy(sol.begin() + y2, sol.begin() + x3 + 1, itr);
        itr = std::copy(sol.begin() + y1, sol.begin() + x2 + 1, itr);
        itr = std::copy(sol.begin() + y0, sol.begin() + x1 + 1, itr);
        itr = std::copy(sol.begin() + y3, sol.end(), itr);
        std::swap(sol, sol_tmp);
        return res;
    }

    T calc_cost() const {
        T res = T(0);
        for (int i = 0; i + 1 < N; i++) {
            res += DIST[sol[i]][sol[i + 1]];
        }
        res += DIST[sol[N - 1]][sol[0]];
        return res;
    }
};
