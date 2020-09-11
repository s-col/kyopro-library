#include <bits/stdc++.h>

#include "template.h"

// トポロジカルソート
// 時間計算量：O(V + E);
// arguments:
//     (O) res: ソート結果を格納する配列
//     (I) g: グラフ
// return:
//     true: 閉路なし，ソート成功
//     false:  閉路あり，ソート失敗(resはclearされる)
bool topological_sort(std::vector<int>& res, const Graph& g) {
    const int n = static_cast<int>(g.size());
    res.resize(n);
    int e = 0;
    std::vector<int> indeg(n);
    for (const auto& ch : g) {
        for (const auto& to : ch) {
            ++indeg[to];
            ++e;
        }
    }
    std::stack<int> st;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) st.push(i);
    }
    int idx = 0;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        res[idx++] = u;
        for (const auto& to : g[u]) {
            --indeg[to];
            --e;
            if (indeg[to] == 0) st.push(to);
        }
    }
    if (e > 0) {
        res.clear();
        return false;
    }
    return true;
}