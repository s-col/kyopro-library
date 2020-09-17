#include <bits/stdc++.h>

// Suffix Array
// 構築: O(|S|)
template <typename Vec>
class SuffixArray {
    using vec_val_t = typename Vec::value_type;

private:
    const Vec src;
    const vec_val_t base;
    const int char_num;
    std::vector<int> sa;

public:
    SuffixArray(const Vec& src, vec_val_t base, int char_num) noexcept
        : src(src), base(base), char_num(char_num) {}
    void build() noexcept {
        const int n = static_cast<int>(src.size());
        std::vector<int> s(n + 1);
        for (int i = 0; i < n; i++)
            s[i] = static_cast<int>(src[i] - base) + 1;
        sa = sa_is(s, char_num + 1);
    }
    int lower_bound(const Vec& vec) const noexcept {
        const int n = static_cast<int>(src.size());
        int left = -1, right = n + 1;
        while (right - left > 1) {
            int mid = (right + left) >> 1;
            if (le_comp(vec, sa[mid]) >= 0)
                right = mid;
            else
                left = mid;
        }
        return right;
    }
    int upper_bound(const Vec& vec) const noexcept {
        const int n = static_cast<int>(src.size());
        int left = -1, right = n + 1;
        while (right - left > 1) {
            int mid = (right + left) >> 1;
            if (le_comp(vec, sa[mid]) > 0)
                right = mid;
            else
                left = mid;
        }
        return right;
    }
    int count(const Vec& vec) const noexcept {
        return upper_bound(vec) - lower_bound(vec);
    }
    const Vec& get_src() const noexcept { return src; }
    const int& operator[](int i) const noexcept { return sa[i]; }
    size_t size() const noexcept { return sa.size(); };
    std::vector<int>::const_iterator cbegin() const noexcept { return sa.cbegin(); }
    std::vector<int>::const_iterator cend() const noexcept { return sa.cend(); }

private:
    int le_comp(const Vec& a, int sh) const noexcept {
        const int d = static_cast<int>(a.size());
        const int n = static_cast<int>(src.size());
        for (int i = 0; i < d; i++) {
            if (a[i] < src[sh + i])
                return 1;
            else if (a[i] > src[sh + i])
                return -1;
            if (sh + i == n) return 1;
        }
        return 0;
    }
    bool is_LMS(const std::vector<bool>& t, int i) const noexcept {
        return i > 0 && t[i] && !t[i - 1];
    }
    std::vector<int> induced_sort(const std::vector<int>& s, const std::vector<bool>& t,
                                  const std::vector<int>& seed, int k) const noexcept {
        const int n = static_cast<int>(s.size());
        const int n_seed = static_cast<int>(seed.size());
        std::vector<int> res(n, -1);
        std::vector<int> bin(k + 1);
        for (const auto& ch : s) ++bin[ch + 1];
        for (int i = 1; i < k + 1; i++) bin[i] += bin[i - 1];
        std::vector<int> count(k);
        for (int i = n_seed - 1; i >= 0; i--) {
            const int& idx = seed[i];
            const int& ch = s[idx];
            res[bin[ch + 1] - 1 - count[ch]] = idx;
            ++count[ch];
        }
        count.assign(k, 0);
        for (int i = 0; i < n; i++) {
            const int& idx = res[i];
            if (idx > 0 && !t[idx - 1]) {
                const int& ch = s[idx - 1];
                res[bin[ch] + count[ch]] = idx - 1;
                ++count[ch];
            }
        }
        count.assign(k, 0);
        for (int i = n - 1; i >= 0; i--) {
            const int& idx = res[i];
            if (idx > 0 && t[idx - 1]) {
                const int& ch = s[idx - 1];
                res[bin[ch + 1] - 1 - count[ch]] = idx - 1;
                ++count[ch];
            }
        }
        return res;
    }
    std::vector<int> sa_is(const std::vector<int>& s, int k) const noexcept {
        const int n = static_cast<int>(s.size());
        std::vector<bool> t(n);  // false: L-type, true: S-type
        t[n - 1] = true;
        for (int i = n - 2; i >= 0; i--) {
            if (s[i] < s[i + 1])
                t[i] = true;
            else if (s[i] > s[i + 1])
                t[i] = false;
            else
                t[i] = t[i + 1];
        }
        std::vector<int> lmss;
        for (int i = 0; i < n; i++)
            if (is_LMS(t, i)) lmss.emplace_back(i);
        const int n_lms = static_cast<int>(lmss.size());
        std::vector<int> seed = lmss;
        auto sa = induced_sort(s, t, seed, k);
        std::vector<int> sa_lms;
        sa_lms.reserve(n_lms);
        for (const auto& idx : sa)
            if (is_LMS(t, idx)) sa_lms.emplace_back(idx);
        std::vector<int> dic(n, -1);
        int nt = 0;
        dic[sa_lms[0]] = 0;
        for (int i = 0; i < n_lms - 1; i++) {
            const int& x = sa_lms[i];
            const int& y = sa_lms[i + 1];
            bool is_diff = false;
            for (int d = 0;; d++) {
                bool fx = is_LMS(t, x + d), fy = is_LMS(t, y + d);
                if (d > 0 && fx && fy) break;
                if (s[x + d] != s[y + d] || (d > 0 && (fx || fy))) {
                    is_diff = true;
                    break;
                }
            }
            if (is_diff) ++nt;
            dic[y] = nt;
        }
        {
            auto itr = std::remove_if(dic.begin(), dic.end(), [](int x) { return x == -1; });
            dic.erase(itr, dic.end());
        }
        if (n_lms > nt + 1)
            seed = sa_is(dic, nt + 1);
        else
            for (int i = 0; i < n_lms; i++) seed[dic[i]] = i;
        for (int i = 0; i < n_lms; i++) seed[i] = lmss[seed[i]];
        sa = induced_sort(s, t, seed, k);
        return sa;
    }
};


// Longest Common Prefix Array
//　構築： O(|S|)
template <typename Vec>
class LCPArray {
    using value_type = typename Vec::value_type;

private:
    SuffixArray<Vec> sa;
    const Vec& src;
    const value_type base;
    const int char_num;
    std::vector<int> lcp;

public:
    LCPArray(const Vec& src, value_type base, int char_num) noexcept
        : sa(src, base, char_num), src(sa.get_src()), base(base), char_num(char_num) {}
    void build() noexcept {
        sa.build();
        const int n = static_cast<int>(src.size());
        lcp.resize(n);
        std::vector<int> rank(n + 1);
        for (int i = 0; i <= n; i++) rank[sa[i]] = i;
        int h = 0;
        lcp[0] = 0;
        for (int i = 0; i < n; i++) {
            int j = sa[rank[i] - 1];
            if (h > 0) --h;
            for (; i + h < n && j + h < n; h++) {
                if (src[i + h] != src[j + h]) break;
            }
            lcp[rank[i] - 1] = h;
        }
    }
    const Vec& get_src() const noexcept { return src; }
    const SuffixArray<Vec>& get_sa() const noexcept { return sa; }
    const int& operator[](int i) const noexcept { return lcp[i]; }
    size_t size() const noexcept { return lcp.size(); }
    std::vector<int>::const_iterator begin() { return lcp.cbegin(); };
    std::vector<int>::const_iterator end() { return lcp.cend(); }
};
