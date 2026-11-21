class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        // Step 1: Build the original tree
        vector<vector<int>> children(n);

        for (int i = 1; i < n; i++) {
            children[parent[i]].push_back(i);
        }

        vector<int> newParent(n, -1);
        vector<int> last(26, -1);

        // Iterative DFS events: {node, entering?, previous ancestor}
        vector<array<int, 3>> st;
        st.push_back({0, 1, -1});

        // Step 2: Find new parents using the original tree
        while (!st.empty()) {
            auto event = st.back();
            st.pop_back();

            int node = event[0];
            int entering = event[1];
            int previous = event[2];

            int c = s[node] - 'a';

            if (entering) {
                // Closest ancestor with the same character
                if (last[c] != -1) {
                    newParent[node] = last[c];
                } else {
                    newParent[node] = parent[node];
                }

                // Save the previous ancestor of this character
                int old = last[c];

                // Current node becomes the latest node of this character
                last[c] = node;

                // Exit event restores the previous value
                st.push_back({node, 0, old});

                // Visit original children
                for (int i = children[node].size() - 1; i >= 0; i--) {
                    st.push_back({children[node][i], 1, -1});
                }
            } 
            else {
                // Restore ancestor tracking after leaving this subtree
                last[c] = previous;
            }
        }

        // Step 3: Build the modified tree
        vector<vector<int>> newChildren(n);

        for (int i = 1; i < n; i++) {
            newChildren[newParent[i]].push_back(i);
        }

        // Step 4: Get traversal order of the modified tree
        vector<int> order;
        vector<int> stack = {0};

        while (!stack.empty()) {
            int node = stack.back();
            stack.pop_back();

            order.push_back(node);

            for (int child : newChildren[node]) {
                stack.push_back(child);
            }
        }

        // Calculate subtree sizes in reverse order
        vector<int> ans(n, 1);

        for (int i = n - 1; i >= 0; i--) {
            int node = order[i];

            if (newParent[node] != -1) {
                ans[newParent[node]] += ans[node];
            }
        }

        return ans;
    }
};