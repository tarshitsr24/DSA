
class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;

        vector<vector<int>> cost(n, vector<int>(n, INF));

        // Precompute semi-palindrome costs
        for (int l = 0; l < n; l++) {
            for (int r = l + 1; r < n; r++) {

                int len = r - l + 1;

                for (int d = 1; d < len; d++) {

                    if (len % d != 0) continue;

                    int changes = 0;

                    for (int offset = 0; offset < d; offset++) {

                        int left = l + offset;
                        int right = r - d + 1 + offset;

                        while (left < right) {

                            if (s[left] != s[right]) {
                                changes++;
                            }

                            left += d;
                            right -= d;
                        }
                    }

                    cost[l][r] = min(cost[l][r], changes);
                }
            }
        }

        // DP
        vector<vector<int>> dp(
            n + 1, vector<int>(k + 1, INF)
        );

        dp[0][0] = 0;

        for (int j = 1; j <= k; j++) {
            for (int i = 2 * j; i <= n; i++) {

                for (int t = 2 * (j - 1); t < i; t++) {

                    if (dp[t][j - 1] == INF) continue;

                    dp[i][j] = min(
                        dp[i][j],
                        dp[t][j - 1] + cost[t][i - 1]
                    );
                }
            }
        }

        return dp[n][k];
    }
};
