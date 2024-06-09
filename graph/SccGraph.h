#include <bits/stdc++.h>

// 強連結成分分解
// 計算量: O(|E| + |V|)
class SccGraph {
private:
    using Graph = std::vector<std::vector<int>>;
    int n;
    Graph g, rg;

public:
    SccGraph(int n) : n(n), g(n), rg(n) {}
    void add_edge(int a, int b) {
        g[a].emplace_back(b);
        rg[b].emplace_back(a);
    }
    /**
     * Return strongly connected components in topological order.
     *
     * Time complexity: O(V + E)
     */
    std::vector<std::vector<int>> scc() const noexcept {
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
    /**
     * Returns a pair with the following components:
     *   - first: the contracted graph
     *   - second: the strongly connected components in topological order
     *
     * The i-th vertex of the contracted graph corresponds to the i-th component in the strongly connected components.
     *
     * Time complexity: O(V + E)
     */
    std::pair<Graph, std::vector<std::vector<int>>> contracted_graph() const noexcept {
        const auto vg = scc();
        std::vector<int> comp_index(n);
        const int num_components = vg.size();
        for (int i_comp = 0; i_comp < num_components; i_comp++) {
            for (const auto& u : vg[i_comp]) {
                comp_index[u] = i_comp;
            }
        }
        Graph contracted_graph(num_components);
        for (int to = 0; to < n; to++) {
            const int to_comp = comp_index[to];
            for (const auto& fr : rg[to]) {
                const int fr_comp = comp_index[fr];
                if (fr_comp != to_comp) {
                    contracted_graph[fr_comp].emplace_back(to_comp);
                }
            }
        }
        for (int i = 0; i < num_components; i++) {
            contracted_graph[i].erase(unique(contracted_graph[i].begin(), contracted_graph[i].end()), contracted_graph[i].end());
        }
        return {contracted_graph, vg};
    }
};
