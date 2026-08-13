class Solution {
public:

    struct Node {
        char leftChar, rightChar;
        int prefix, suffix, best, len;
    };

    vector<Node> tree;

    Node merge(Node a, Node b) {
        Node res;

        res.len = a.len + b.len;
        res.leftChar = a.leftChar;
        res.rightChar = b.rightChar;

        res.prefix = a.prefix;
        res.suffix = b.suffix;

        // Can the prefix continue into b?
        if (a.prefix == a.len && a.rightChar == b.leftChar) {
            res.prefix = a.len + b.prefix;
        }

        // Can the suffix continue into a?
        if (b.suffix == b.len && a.rightChar == b.leftChar) {
            res.suffix = b.len + a.suffix;
        }

        // Best answer is either completely in a,
        // completely in b, or crosses the middle
        res.best = max(a.best, b.best);

        if (a.rightChar == b.leftChar) {
            res.best = max(res.best, a.suffix + b.prefix);
        }

        return res;
    }

    void build(int node, int l, int r, string &s) {

        if (l == r) {
            tree[node] = {
                s[l],
                s[l],
                1,
                1,
                1,
                1
            };
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid, s);
        build(node * 2 + 1, mid + 1, r, s);

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {

        if (l == r) {
            tree[node] = {
                c,
                c,
                1,
                1,
                1,
                1
            };
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid) {
            update(node * 2, l, mid, idx, c);
        } else {
            update(node * 2 + 1, mid + 1, r, idx, c);
        }

        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {

        int n = s.size();
        int k = queryCharacters.size();

        tree.resize(4 * n);

        // Build segment tree
        build(1, 0, n - 1, s);

        vector<int> ans;

        for (int i = 0; i < k; i++) {

            int index = queryIndices[i];
            char c = queryCharacters[i];

            // Update string
            s[index] = c;

            // Update segment tree
            update(1, 0, n - 1, index, c);

            // Root contains answer for entire string
            ans.push_back(tree[1].best);
        }

        return ans;
    }
};