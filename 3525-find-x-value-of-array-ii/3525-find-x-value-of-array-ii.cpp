class Solution {
public:
    struct Node {
        int prod = 1;
        int pref[5] = {};
    };

    int k;

    Node mergeNode(const Node& a, const Node& b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        for (int i = 0; i < k; i++) {
            res.pref[i] = a.pref[i];
        }

        for (int i = 0; i < k; i++) {
            int rem = (a.prod * i) % k;
            res.pref[rem] += b.pref[i];
        }

        return res;
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        this->k = k;

        int n = nums.size();

        // Special case: modulo 1 is always 0
        if (k == 1) {
            vector<int> ans;

            for (auto& q : queries) {
                int start = q[2];

                // Every non-empty suffix remaining after start
                // has product % 1 == 0.
                ans.push_back(n - start);
            }

            return ans;
        }

        // Iterative segment tree
        int size = 1;
        while (size < n)
            size *= 2;

        vector<Node> tree(2 * size);

        // Build leaves
        for (int i = 0; i < n; i++) {
            int rem = nums[i] % k;

            tree[size + i].prod = rem;
            tree[size + i].pref[rem] = 1;
        }

        // Build tree
        for (int i = size - 1; i >= 1; i--) {
            tree[i] = mergeNode(tree[i * 2], tree[i * 2 + 1]);
        }

        auto update = [&](int pos, int value) {
            int p = size + pos;

            // Clear old node
            tree[p] = Node();

            int rem = value % k;

            tree[p].prod = rem;
            tree[p].pref[rem] = 1;

            p /= 2;

            while (p >= 1) {
                tree[p] = mergeNode(tree[p * 2], tree[p * 2 + 1]);
                p /= 2;
            }
        };

        auto query = [&](int left, int right) {
            Node leftNode;
            Node rightNode;

            bool hasLeft = false;
            bool hasRight = false;

            left += size;
            right += size;

            while (left <= right) {
                if (left % 2 == 1) {
                    if (!hasLeft) {
                        leftNode = tree[left];
                        hasLeft = true;
                    } else {
                        leftNode = mergeNode(leftNode, tree[left]);
                    }
                    left++;
                }

                if (right % 2 == 0) {
                    if (!hasRight) {
                        rightNode = tree[right];
                        hasRight = true;
                    } else {
                        rightNode = mergeNode(tree[right], rightNode);
                    }
                    right--;
                }

                left /= 2;
                right /= 2;
            }

            if (!hasLeft)
                return rightNode;

            if (!hasRight)
                return leftNode;

            return mergeNode(leftNode, rightNode);
        };

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(index, value);

            // Query nums[start ... n-1]
            Node res = query(start, n - 1);

            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};