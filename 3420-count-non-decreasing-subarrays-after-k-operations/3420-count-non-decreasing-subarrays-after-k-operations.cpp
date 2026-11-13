class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        deque<int> dq;
        long long cost = 0;
        long long ans = 0;

        int j = n - 1;

        for (int i = n - 1; i >= 0; i--) {

            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                int left = dq.back();
                dq.pop_back();

                int right = dq.empty() ? j + 1 : dq.back();

                cost += 1LL * (right - left) *
                        (nums[i] - nums[left]);
            }

            dq.push_back(i);

            while (cost > k) {
                cost -= nums[dq.front()] - nums[j];

                if (dq.front() == j) {
                    dq.pop_front();
                }

                j--;
            }

            ans += j - i + 1;
        }

        return ans;
    }
};