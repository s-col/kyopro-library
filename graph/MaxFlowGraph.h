#include <bits/stdc++.h>

// MaxFlowGraph
// flow : O(V^2 E)
template <typename Cap>
class MaxFlowGraph {
private:
    struct _Edge {
        int to, rev;
        Cap cap;
        _Edge() noexcept {}
        _Edge(int to, Cap cap, int rev) noexcept : to(to), rev(rev), cap(cap) {}
    };
    std::vector<std::vector<_Edge>> g;
    std::vector<std::pair<int, int>> pos;

public:
    MaxFlowGraph(int n) noexcept : g(n) {}
    int add_edge(int from, int to, Cap cap) noexcept {
        const int m = static_cast<int>(pos.size());
        const int from_id = static_cast<int>(g[from].size());
        int to_id = static_cast<int>(g[to].size());
        pos.emplace_back(from, static_cast<int>(g[from].size()));
        if (from == to) ++to_id;
        g[from].emplace_back(to, cap, to_id);
        g[to].emplace_back(from, 0, from_id);
        return m;
    }
    struct Edge {
        int from, to;
        Cap cap, flow;
        Edge() noexcept {}
        Edge(int from, int to, Cap cap, Cap flow) noexcept
            : from(from), to(to), cap(cap), flow(flow) {}
    };
    Edge get_edge(int i) const noexcept {
        const auto e = g[pos[i].first][pos[i].second];
        const auto re = g[e.to][e.rev];
        return Edge(pos[i].first, e.to, e.cap + re.cap, re.cap);
    }
    std::vector<Edge> edges() const noexcept {
        const int m = static_cast<int>(pos.size());
        std::vector<Edge> res;
        res.reserve(m);
        for (int i = 0; i < m; i++) res.emplace_back(get_edge(i));
        return res;
    }
    void change_edge(int i, Cap new_cap, Cap new_flow) noexcept {
        auto& e = g[pos[i].first][pos[i].second];
        auto& re = g[e.to][e.rev];
        e.cap = new_cap - new_flow;
        re.cap = new_flow;
    }
    Cap flow(int s, int t) noexcept {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }
    Cap flow(int s, int t, Cap flow_limit) noexcept {
        const int n = static_cast<int>(g.size());
        std::vector<int> level(n), iter(n);
        std::deque<int> que;
        auto bfs = [&](void) noexcept -> void {
            level.assign(n, -1);
            que.clear();
            level[s] = 0;
            que.emplace_back(s);
            while (!que.empty()) {
                int v = que.front();
                que.pop_front();
                int sz = static_cast<int>(g[v].size());
                for (int i = 0; i < sz; i++) {
                    const _Edge& e = g[v][i];
                    if (e.cap > 0 && level[e.to] < 0) {
                        level[e.to] = level[v] + 1;
                        if (e.to == t) return;
                        que.emplace_back(e.to);
                    }
                }
            }
        };
        auto dfs = [&](auto&& self, int v, Cap f) noexcept -> Cap {
            if (v == s) return f;
            const int sz = static_cast<int>(g[v].size());
            const int level_v = level[v];
            Cap res = 0;
            for (int& i = iter[v]; i < sz; i++) {
                _Edge& e = g[v][i];
                _Edge& re = g[e.to][e.rev];
                if (level_v > level[e.to] && re.cap > 0) {
                    int d = self(self, e.to, std::min(f - res, re.cap));
                    if (d > 0) {
                        re.cap -= d;
                        e.cap += d;
                        res += d;
                        if (res == f) break;
                    }
                }
            }
            return res;
        };
        Cap flow = 0;
        while (flow < flow_limit) {
            bfs();
            if (level[t] < 0) return flow;
            iter.assign(n, 0);
            while (flow < flow_limit) {
                Cap f = dfs(dfs, t, flow_limit - flow);
                if (f == 0) break;
                flow += f;
            }
        }
        return flow;
    }
    std::vector<bool> min_cut(int s) const noexcept {
        const int n = static_cast<int>(g.size());
        std::vector<bool> res(n);
        std::deque<int> que;
        res[s] = true;
        que.emplace_back(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop_front();
            for (const auto& edge : g[v]) {
                if (edge.cap > 0 && !res[edge.to]) {
                    res[edge.to] = true;
                    que.emplace_back(edge.to);
                }
            }
        }
        return res;
    }
};
