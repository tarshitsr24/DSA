class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        const int INF = 1e9;

        // best[i] = minimum length of a target-sum subarray
        // ending at or before index i
        vector<int> best(n, INF);

        int left = 0;
        long long sum = 0;

        int minLen = INF;
        int ans = INF;

        for (int right = 0; right < n; right++) {

            sum += arr[right];

            // Shrink window if sum becomes greater than target
            while (sum > target && left <= right) {
                sum -= arr[left];
                left++;
            }

            // Found a subarray [left ... right] with sum = target
            if (sum == target) {

                int currentLen = right - left + 1;

                // If another valid subarray exists completely
                // before this one
                if (left > 0 && best[left - 1] != INF) {
                    ans = min(ans, currentLen + best[left - 1]);
                }

                minLen = min(minLen, currentLen);
            }

            best[right] = minLen;
        }

        return ans == INF ? -1 : ans;
    }
};