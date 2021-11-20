#include <bits/stdc++.h>

// T: 半群
// F: 二項演算 T x T -> T
template <class T, class F>
class SWAG {
private:
    using P = std::pair<T, T>;
    std::vector<P> fr, ba;
    F f;

public:
    explicit SWAG(F f) noexcept : f(f) {}
    // Push an element to the back of the sequence.
    void push(const T& a) noexcept {
        T c;
        if (ba.empty())
            c = a;
        else
            c = f(ba.back().second, a);
        ba.emplace_back(a, c);
    }
    // Pop an element from the front of the sequence.
    void pop(void) noexcept {
        if (fr.empty()) {
            while (!ba.empty()) {
                T a = ba.back().first;
                ba.pop_back();
                T c;
                if (fr.empty())
                    c = a;
                else
                    c = f(a, fr.back().second);
                fr.emplace_back(a, c);
            }
        }
        fr.pop_back();
    }
    T agg(void) const noexcept {
        if (fr.empty() && ba.empty()) {
            assert(false);
        } else if (fr.empty()) {
            return ba.back().second;
        } else if (ba.empty()) {
            return fr.back().second;
        } else {
            return f(fr.back().second, ba.back().second);
        }
    }
    void clear(void) noexcept {
        fr.clear();
        ba.clear();
    }
    size_t size(void) noexcept {
        return fr.size() + ba.size();
    }
};
