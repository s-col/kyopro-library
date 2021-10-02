#include <bits/stdc++.h>

// 最小費用流
// flow, slope : O(F(|V|+|E|)log|V|)
template <typename Cap, typename Cost>
class MinCostFlowGraph {
private:
    struct _Edge {
        const int to, rev;
        Cap cap;
        const Cost cost;
        _Edge() noexcept {}
        _Edge(int to, Cap cap, Cost cost, int rev) noexcept
            : to(to), rev(rev), cap(cap), cost(cost) {}
    };
    std::vector<std::vector<_Edge>> g;
    std::vector<std::pair<int, int>> pos;

public:
    MinCostFlowGraph(int n) noexcept : g(n) {}
    int add_edge(int from, int to, Cap cap, Cost cost) noexcept {
        const int m = static_cast<int>(pos.size());
        const int from_id = static_cast<int>(g[from].size());
        int to_id = static_cast<int>(g[to].size());
        pos.emplace_back(from, static_cast<int>(g[from].size()));
        if (from == to)
            ++to_id;
        g[from].emplace_back(to, cap, cost, to_id);
        g[to].emplace_back(from, 0, -cost, from_id);
        return m;
    }
    struct Edge {
        const int from, to;
        const Cap cap, flow;
        const Cost cost;
        Edge() noexcept {}
        Edge(int from, int to, Cap cap, Cap flow, Cost cost) noexcept
            : from(from), to(to), cap(cap), flow(flow), cost(cost) {}
    };
    Edge get_edge(int i) const noexcept {
        const auto e = g[pos[i].first][pos[i].second];
        const auto re = g[e.to][e.rev];
        return Edge(pos[i].first, e.to, e.cap + re.cap, re.cap, e.cost);
    }
    std::vector<Edge> edges() const noexcept {
        const int m = static_cast<int>(pos.size());
        std::vector<Edge> res;
        res.reserve(m);
        for (int i = 0; i < m; i++)
            res.emplace_back(get_edge(i));
        return res;
    }
    std::pair<Cap, Cost> flow(int s, int t) noexcept {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }
    std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) noexcept {
        return slope(s, t, flow_limit).back();
    }
    std::vector<std::pair<Cap, Cost>> slope(int s, int t) noexcept {
        return slope(s, t, std::numeric_limits<Cap>::max());
    }
    std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) noexcept {
        constexpr Cost C_INF = std::numeric_limits<Cost>::max();
        const int n = static_cast<int>(g.size());
        std::vector<Cost> h(n), dist(n);
        std::vector<int> prevv(n), preve(n);
        std::vector<std::pair<Cap, Cost>> res;
        struct Q {
            Cost key;
            int to;
            Q(Cost key, int to) noexcept : key(key), to(to) {}
            bool operator>(const Q& r) const noexcept {
                return key > r.key;
            }
        };
        Cap flow = 0;
        Cost cost = 0, prev_cost = -1;
        res.emplace_back(flow, cost);
        while (flow < flow_limit) {
            std::priority_queue<Q, std::vector<Q>, std::greater<Q>> que;
            dist.assign(n, C_INF);
            dist[s] = 0;
            que.emplace(0, s);
            while (!que.empty()) {
                const auto [d, v] = que.top();
                que.pop();
                if (dist[v] < d)
                    continue;
                const int m = static_cast<int>(g[v].size());
                for (int i = 0; i < m; i++) {
                    const _Edge& e = g[v][i];
                    Cost cn = dist[v] + e.cost + h[v] - h[e.to];
                    if (e.cap > 0 && dist[e.to] > cn) {
                        dist[e.to] = cn;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.emplace(cn, e.to);
                    }
                }
            }
            if (dist[t] == C_INF)
                break;
            for (int i = 0; i < n; i++)
                h[i] += dist[i];
            Cap f = flow_limit - flow;
            for (int i = t; i != s; i = prevv[i]) {
                f = std::min(f, g[prevv[i]][preve[i]].cap);
            }
            for (int i = t; i != s; i = prevv[i]) {
                _Edge& e = g[prevv[i]][preve[i]];
                e.cap -= f;
                g[i][e.rev].cap += f;
            }
            Cost d = h[t];
            flow += f;
            cost += f * d;
            if (prev_cost == d)
                res.pop_back();
            res.emplace_back(flow, cost);
            prev_cost = d;
        }
        return res;
    }
};
