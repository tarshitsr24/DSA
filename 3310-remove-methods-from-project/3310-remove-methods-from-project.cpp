class Solution {
public:
    void dfs(int node, vector<vector<int>>& graph, vector<bool>& suspicious)
    {
        suspicious[node] = true;

        for(int next : graph[node])
        {
            if(!suspicious[next])
                dfs(next, graph, suspicious);
        }
    }

    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {

        vector<vector<int>> graph(n);

        for(auto &e : invocations)
        {
            graph[e[0]].push_back(e[1]);
        }

        // Find all suspicious methods
        vector<bool> suspicious(n, false);
        dfs(k, graph, suspicious);

        // Check if any outside method invokes a suspicious method
        for(auto &e : invocations)
        {
            int u = e[0];
            int v = e[1];

            if(!suspicious[u] && suspicious[v])
            {
                vector<int> ans;
                for(int i = 0; i < n; i++)
                    ans.push_back(i);
                return ans;
            }
        }

        // Remove suspicious methods
        vector<int> ans;

        for(int i = 0; i < n; i++)
        {
            if(!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};