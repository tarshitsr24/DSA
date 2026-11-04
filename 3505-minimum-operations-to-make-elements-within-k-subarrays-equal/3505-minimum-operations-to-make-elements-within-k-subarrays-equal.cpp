
class Solution {
public:
    multiset<int> left, right;
    long long sumLeft = 0, sumRight = 0;

    void add(int num) {
        if (left.empty() || num <= *left.rbegin()) {
            left.insert(num);
            sumLeft += num;
        } else {
            right.insert(num);
            sumRight += num;
        }

        balance();
    }

    void remove(int num) {
        auto it = left.find(num);

        if (it != left.end()) {
            left.erase(it);
            sumLeft -= num;
        } else {
            it = right.find(num);
            right.erase(it);
            sumRight -= num;
        }

        balance();
    }

    void balance() {
        while (left.size() > right.size() + 1) {
            int val = *left.rbegin();

            left.erase(left.find(val));
            sumLeft -= val;

            right.insert(val);
            sumRight += val;
        }

        while (left.size() < right.size()) {
            int val = *right.begin();

            right.erase(right.find(val));
            sumRight -= val;

            left.insert(val);
            sumLeft += val;
        }
    }

    long long getCost() {
        long long median = *left.rbegin();

        return median * left.size() - sumLeft
             + sumRight - median * right.size();
    }

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<long long> cost(n - x + 1);

        // Calculate cost of every window of size x
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // DP
        const long long INF = 1e18;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            dp[i][0] = 0;

            for (int j = 1; j <= k; j++) {

                // Don't choose a window ending here
                dp[i][j] = dp[i - 1][j];

                // Choose a window of size x
                if (i >= x && dp[i - x][j - 1] != INF) {
                    dp[i][j] = min(
                        dp[i][j],
                        dp[i - x][j - 1] + cost[i - x]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
