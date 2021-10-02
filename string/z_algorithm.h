#include <bits/stdc++.h>

// Z-algorithm
// string
// Sに対して、各iについてSとS[i:|S|]の「最長共通接頭辞の長さ」を記録した配列Aを作成する
// 時間計算量 : O(|S|)
std::vector<int> z_algorithm(const std::string& s) {
    int sl = static_cast<int>(s.size());
    std::vector<int> res(sl);
    res[0] = sl;
    int i = 1, j = 0;
    while (i < sl) {
        while (i + j < sl && s[j] == s[i + j])
            ++j;
        res[i] = j;
        if (j == 0) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < sl && k + res[k] < j) {
            res[i + k] = res[k];
            ++k;
        }
        i += k;
        j -= k;
    }
    return res;
}