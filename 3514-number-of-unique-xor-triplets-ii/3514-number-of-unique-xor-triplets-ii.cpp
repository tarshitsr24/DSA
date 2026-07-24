class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<bool> dp(MAXX, false);
        dp[0] = true;

        for (int step = 0; step < 3; step++) {
            vector<bool> ndp(MAXX, false);

            for (int x = 0; x < MAXX; x++) {
                if (!dp[x]) continue;

                for (int v : nums) {
                    ndp[x ^ v] = true;
                }
            }

            dp = move(ndp);
        }

        int ans = 0;
        for (bool ok : dp)
            if (ok) ans++;

        return ans;
    }
};