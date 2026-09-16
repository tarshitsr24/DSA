class Solution {
public:
    int numberOfSets(int n, int k) {
        const int MOD = 1e9 + 7;

        // dp[i][j] = number of ways to make j segments
        // using points from 0 to i
        vector<vector<long long>> dp(n, vector<long long>(k + 1, 0));

        // prefix[i][j] = dp[0][j] + dp[1][j] + ... + dp[i][j]
        vector<vector<long long>> prefix(n, vector<long long>(k + 1, 0));

        // 0 segments can always be formed in exactly 1 way
        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
            prefix[i][0] = i + 1;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i < n; i++) {

                // Case 1:
                // Don't use point i as the ending of a new segment
                dp[i][j] = dp[i - 1][j];

                // Case 2:
                // Make a new segment ending at i.
                //
                // Its starting point can be 0 ... i-1.
                // prefix helps us calculate all those possibilities.
                dp[i][j] = (dp[i][j] + prefix[i - 1][j - 1]) % MOD;

                prefix[i][j] =
                    (prefix[i - 1][j] + dp[i][j]) % MOD;
            }
        }

        return dp[n - 1][k];
    }
};