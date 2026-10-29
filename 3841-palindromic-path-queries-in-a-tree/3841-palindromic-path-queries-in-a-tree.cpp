class Solution {
public:
    vector<vector<int>> adj;
    vector<int> tin, tout, depth, parent;
    vector<vector<int>> up;
    vector<int> bit;
    int timer = 0;

    void dfs(int u, int p) {
        tin[u] = ++timer;
        parent[u] = p;
        up[0][u] = p;

        for (int i = 1; i < up.size(); i++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
        }

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }

        tout[u] = timer;
    }

    void updateBIT(int i, int val) {
        while (i < bit.size()) {
            bit[i] ^= val;
            i += i & -i;
        }
    }

    int queryBIT(int i) {
        int ans = 0;
        while (i > 0) {
            ans ^= bit[i];
            i -= i & -i;
        }
        return ans;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int diff = depth[u] - depth[v];

        for (int i = 0; i < up.size(); i++) {
            if (diff & (1 << i)) {
                u = up[i][u];
            }
        }

        if (u == v) return u;

        for (int i = (int)up.size() - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u];
                v = up[i][v];
            }
        }

        return parent[u];
    }

    vector<bool> palindromePath(
        int n,
        vector<vector<int>>& edges,
        string s,
        vector<string>& queries
    ) {
        adj.assign(n, {});

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        tin.resize(n);
        tout.resize(n);
        depth.assign(n, 0);
        parent.resize(n);

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        up.assign(LOG, vector<int>(n, 0));
        bit.assign(n + 2, 0);

        dfs(0, 0);

        // Each node's character contributes to its subtree.
        for (int u = 0; u < n; u++) {
            int mask = 1 << (s[u] - 'a');
            updateBIT(tin[u], mask);
            updateBIT(tout[u] + 1, mask);
        }

        vector<bool> ans;

        for (string& q : queries) {
            stringstream ss(q);
            string type;
            int u, v;
            ss >> type >> u;

            if (type == "update") {
                char c;
                ss >> c;

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');

                updateBIT(tin[u], oldMask ^ newMask);
                updateBIT(tout[u] + 1, oldMask ^ newMask);

                s[u] = c;
            } else {
                ss >> v;

                int w = lca(u, v);

                int maskU = queryBIT(tin[u]);
                int maskV = queryBIT(tin[v]);
                int maskW = queryBIT(tin[w]);
                int maskParentW = (w == 0)
                    ? 0
                    : queryBIT(tin[parent[w]]);

                int pathMask = maskU ^ maskV ^ maskW ^ maskParentW;

                // At most one bit may be set.
                ans.push_back((pathMask & (pathMask - 1)) == 0);
            }
        }

        return ans;
    }
};