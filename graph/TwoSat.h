#include <bits/stdc++.h>

#include "kyopro-library/graph/SccGraph.h"

// 2-SAT
// NOTE: SccGraph required.
class TwoSat {
private:
    int n;
    SccGraph scc_graph;
    std::vector<int> scc_ord;

public:
    TwoSat(int n) : n(n), scc_graph(n * 2), scc_ord(n * 2) {}
    void add_clause(int i, bool f, int j, bool g) {
        scc_graph.add_edge((f ? i + n : i), (!g ? j + n : j));
        scc_graph.add_edge((g ? j + n : j), (!f ? i + n : i));
    }
    // complexity : O(n + m) (m : the number of clauses)
    bool satisfiable() {
        auto scc_res = scc_graph.scc();
        const int scc_sz = static_cast<int>(scc_res.size());
        for (int i = 0; i < scc_sz; i++)
            for (const auto& v : scc_res[i])
                scc_ord[v] = i;
        bool res = true;
        for (int i = 0; i < n; i++) {
            if (scc_ord[i] == scc_ord[i + n]) {
                res = false;
                break;
            }
        }
        return res;
    }
    // complexity : O(n)
    std::vector<bool> answer() {
        std::vector<bool> res(n);
        for (int i = 0; i < n; i++)
            if (scc_ord[i] > scc_ord[i + n]) res[i] = true;
        return res;
    }
};
