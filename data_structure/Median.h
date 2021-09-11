#include <bits/stdc++.h>

// Data structure that allows adding and removing elements and retrieving the median value.
// Complexity:
//   insert: O(log N)
//   erase:  O(log N)
//   get:    O(1)
template <class T>
class Median {
private:
    std::multiset<T> lst, rst;

public:
    Median() noexcept {}
    // mode:
    //   Specifies the definition of the median value when the number of elements is even.
    //     -1: left
    //      0: (left + right) / 2 (default)
    //      1: right
    T get(int mode = 0) const noexcept {
        if ((lst.size() + rst.size()) % 2 == 0) {
            if (mode == -1) {
                return *prev(lst.end());
            } else if (mode == 1) {
                return *rst.begin();
            } else {
                return (*prev(lst.end()) + *rst.begin()) / 2;
            }
        } else {
            return *prev(lst.end());
        }
    }
    void insert(const T& v) noexcept {
        rst.emplace(v);
        if (!lst.empty()) {
            rst.emplace(*prev(lst.end()));
            lst.erase(prev(lst.end()));
        }
        while (lst.size() < rst.size()) {
            lst.emplace(*rst.begin());
            rst.erase(rst.begin());
        }
    }
    void erase(const T& v) noexcept {
        if (auto itr = lst.find(v); itr != lst.end()) {
            lst.erase(itr);
            while (lst.size() < rst.size()) {
                lst.emplace(*rst.begin());
                rst.erase(rst.begin());
            }
        } else if (auto itr = rst.find(v); itr != rst.end()) {
            rst.erase(itr);
            while (lst.size() + 1u > rst.size()) {
                rst.emplace(*prev(lst.end()));
                lst.erase(prev(lst.end()));
            }
        }
    }
};