#include <bits/stdc++.h>

// スライド最小値
// 長さNの数列 a[0], ..., a[N - 1]について区間[i, i + K), i = 0, ..., N -
// Kにおける 最小値を格納した配列 y[i] を返す 時間計算量 : O(N)
template <typename T>
std::vector<T> slide_min(const std::vector<T>& vec, int k) {
    int vecl = static_cast<int>(vec.size());
    std::vector<T> res(vecl - k + 1);
    std::deque<T> deq;
    for (int i = 0; i < k; ++i) {
        while (!deq.empty() && vec[deq.back()] >= vec[i]) deq.pop_back();
        deq.push_back(i);
    }
    res[0] = vec[deq.front()];
    for (int i = k; i < vecl; ++i) {
        while (!deq.empty() && vec[deq.back()] >= vec[i]) deq.pop_back();
        deq.push_back(i);
        if (deq.front() == i - k) deq.pop_front();
        res[i - k + 1] = vec[deq.front()];
    }
    return res;
}