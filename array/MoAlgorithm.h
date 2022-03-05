#include <bits/stdc++.h>

// Mo's Algorithm
// Complexity
//     O(a(NB + Q(N/B)))
//         N: Length of array
//         Q: Number of queries
//         B: Number of blocks
//         a: Complexity of add, del
// sample: https://atcoder.jp/contests/abc242/submissions/29905225
class MoAlgo {
private:
    std::vector<int> query_l, query_r;
    std::vector<int> order;
    int block_size = 0;

public:
    MoAlgo() noexcept {}
    // query: [l, r)
    void set_queries(const std::vector<int>& ls, const std::vector<int>& rs, int block_size) noexcept {
        assert(ls.size() == rs.size());
        query_l = ls;
        query_r = rs;
        this->block_size = block_size;
        sort_order();
    }
    // query: [l, r)
    void set_queries(const std::vector<std::pair<int, int>>& queries, int block_size) noexcept {
        query_l.reserve(queries.size());
        query_r.reserve(queries.size());
        for (const auto& [l, r] : queries) {
            query_l.emplace_back(l);
            query_r.emplace_back(r);
        }
        this->block_size = block_size;
        sort_order();
    }
    // T: type of output
    // Add, Del: functon T(int idx, T& val)
    // initial_value: the value for the query [0, 0)
    template <class T, class Add, class Del>
    std::vector<T> run(const T& initial_value, const Add& add, const Del& del) const noexcept {
        std::vector<T> res(order.size());
        T val = initial_value;
        int cur_l = 0, cur_r = 0;
        for (const auto& i : order) {
            int l = query_l[i];
            int r = query_r[i];
            while (cur_l > l)
                add(--cur_l, val);
            while (cur_r < r)
                add(cur_r++, val);
            while (cur_l < l)
                del(cur_l++, val);
            while (cur_r > r)
                del(--cur_r, val);
            res[i] = val;
        }
        return res;
    }

private:
    void sort_order() noexcept {
        order.resize(query_l.size());
        std::iota(order.begin(), order.end(), 0);
        std::sort(order.begin(), order.end(), [this](int i, int j) {
            if (query_l[i] / block_size != query_l[j] / block_size)
                return query_l[i] < query_l[j];
            return query_r[i] < query_r[j];
        });
    }
};
