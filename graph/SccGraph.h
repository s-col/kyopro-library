#include <bits/stdc++.h>

// 強連結成分分解
// 計算量: O(|E| + |V|)
class SccGraph {
private:
    int n;
    std::vector<std::vector<int>> g, rg;

public:
    SccGraph(int n) : n(n), g(n), rg(n) {}
    void add_edge(int a, int b) {
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    std::vector<std::vector<int>> scc() {
        std::vector<std::vector<int>> res;
        std::vector<int> vs;
        vs.reserve(n);
        std::vector<bool> used(n);
        auto dfs1 = [&](auto&& self, int idx) noexcept -> void {
            used[idx] = true;
            for (const auto& v : g[idx])
                if (!used[v])
                    self(self, v);
            vs.emplace_back(idx);
        };
        auto dfs2 = [&](auto&& self, int idx) noexcept -> void {
            used[idx] = true;
            res.back().emplace_back(idx);
            for (const auto& v : rg[idx])
                if (!used[v])
                    self(self, v);
        };
        for (int i = 0; i < n; i++) {
            if (!used[i])
                dfs1(dfs1, i);
        }
        used.assign(n, false);
        for (int i = n - 1; i >= 0; i--) {
            if (!used[vs[i]]) {
                res.emplace_back();
                dfs2(dfs2, vs[i]);
            }
        }
        return res;
    }
};