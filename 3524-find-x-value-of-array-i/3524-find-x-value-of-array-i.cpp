class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> result(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> ndp(k, 0);

            int rem = num % k;

            // Start a new subarray
            ndp[rem]++;

            // Extend previous subarrays
            for (int r = 0; r < k; r++) {
                if (dp[r] > 0) {
                    int newRem = (r * rem) % k;
                    ndp[newRem] += dp[r];
                }
            }

            // Add all subarrays ending at current position
            for (int r = 0; r < k; r++) {
                result[r] += ndp[r];
            }

            dp = ndp;
        }

        return result;
    }
};