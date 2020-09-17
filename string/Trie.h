// Trie木
// add: O(|S|)
// search: O(|S|)
// 参考: https://algo-logic.info/trie-tree/#:~:text=Trie%E6%9C%A8%E3%81%AF%E3%80%81%E5%8A%B9%E7%8E%87%E7%9A%84,%E3%81%95%E3%82%92M%20%E3%81%A8%E3%81%97%E3%81%BE%E3%81%97%E3%81%9F%E3%80%82%EF%BC%89
template <int char_num, char base>
class Trie {
private:
    struct Node {
        std::array<int, char_num> children;
        std::vector<int> accept;
        int common = 0;
        int c;
        Node(int c) : c(c) {
            children.fill(-1);
        }
    };

    std::vector<Node> nodes;
    const int root = 0;

public:
    Trie() {
        nodes.emplace_back(root);
    }
    void add(const string& str, int str_id) {
        int node_id = 0;
        int sz = static_cast<int>(str.size());
        for (int i = 0; i < sz; i++) {
            int c = static_cast<int>(str[i] - base);
            int next_id = nodes[node_id].children[c];
            if (next_id == -1) {
                next_id = static_cast<int>(nodes.size());
                nodes[node_id].children[c] = next_id;
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.emplace_back(str_id);
    }
    void add(const string& str) {
        add(str, nodes[0].common);
    }
    bool search(const string& str, bool prefix = false) {
        int node_id = 0;
        int sz = static_cast<int>(str.size());
        for (int i = 0; i < sz; i++) {
            int c = static_cast<int>(str[i] - base);
            int next_id = nodes[node_id].children[c];
            if (next_id == -1) {
                return false;
            }
            node_id = next_id;
        }
        return prefix ? true : nodes[node_id].accept.size() > 0;
    }
    bool search_prefix(const string& str) {
        return search(str, true);
    }
    int count() {
        return nodes[0].common;
    }
    int size() {
        return static_cast<int>(nodes.size());
    }
};
