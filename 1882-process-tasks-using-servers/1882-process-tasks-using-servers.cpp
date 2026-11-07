class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {

        priority_queue<
            pair<int,int>,
            vector<pair<int,int>>,
            greater<pair<int,int>>
        > available;

        priority_queue<
            tuple<long long,int,int>,
            vector<tuple<long long,int,int>>,
            greater<tuple<long long,int,int>>
        > busy;

        int n = servers.size();
        int m = tasks.size();

        // Initially, all servers are available
        for(int i = 0; i < n; i++) {
            available.push({servers[i], i});
        }

        vector<int> ans(m);

        long long time = 0;

        for(int i = 0; i < m; i++) {

            time = max(time, (long long)i);

            // Move all free servers into available heap
            while(!busy.empty() && get<0>(busy.top()) <= time) {

                auto [freeTime, weight, index] = busy.top();
                busy.pop();

                available.push({weight, index});
            }

            // If no server is available, jump time forward
            if(available.empty()) {

                time = get<0>(busy.top());

                // Move all servers that become free at this time
                while(!busy.empty() && get<0>(busy.top()) <= time) {

                    auto [freeTime, weight, index] = busy.top();
                    busy.pop();

                    available.push({weight, index});
                }
            }

            // Select the server with smallest weight and index
            auto [weight, index] = available.top();
            available.pop();

            ans[i] = index;

            // Calculate when this server becomes free
            busy.push({time + tasks[i], weight, index});
        }

        return ans;
    }
};