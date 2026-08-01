class Solution {
public:
    int dp[21][21];

    int solve(vector<int>& nums, int left, int right) {
        if (left == right)
            return nums[left];

        if (dp[left][right] != -1)
            return dp[left][right];

        int takeLeft = nums[left] - solve(nums, left + 1, right);
        int takeRight = nums[right] - solve(nums, left, right - 1);

        return dp[left][right] = max(takeLeft, takeRight);
    }

    bool predictTheWinner(vector<int>& nums) {
        memset(dp, -1, sizeof(dp));
        return solve(nums, 0, nums.size() - 1) >= 0;
    }
};