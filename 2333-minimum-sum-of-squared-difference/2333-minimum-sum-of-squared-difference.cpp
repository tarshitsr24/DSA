
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        vector<int> diff;
        long long k = 1LL * k1 + k2;
        long long total = 0;
        int maxDiff = 0;

        for (int i = 0; i < nums1.size(); i++) {
            int d = abs(nums1[i] - nums2[i]);
            diff.push_back(d);
            total += d;
            maxDiff = max(maxDiff, d);
        }

        if (total <= k) return 0;

        int low = 0, high = maxDiff;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long needed = 0;

            for (int d : diff) {
                if (d > mid) {
                    needed += d - mid;
                }
            }

            if (needed > k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        long long ans = 0;
        long long used = 0;

        for (int d : diff) {
            int reduced = min(d, low);
            ans += 1LL * reduced * reduced;
            used += d - reduced;
        }

        for (int d : diff) {
            if (used == k) break;

            if (d >= low && low > 0) {
                ans -= 1LL * low * low;
                ans += 1LL * (low - 1) * (low - 1);
                used++;
            }
        }

        return ans;
    }
};
