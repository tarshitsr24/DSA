class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        const int MOD = 1e9 + 7;

        int odd = 0;
        int even = 1;  // Empty prefix sum is 0 (even)
        int sum = 0;
        int ans = 0;

        for (int num : arr) {
            sum += num;

            if (sum % 2 == 0) {
                ans += odd;
                even++;
            }
            else {
                ans += even;
                odd++;
            }

            ans %= MOD;
        }

        return ans;
    }
};