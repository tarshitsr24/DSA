class Solution {
public:
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int median = nums[n/2];
        long long total_moves = 0;
        for(int x : nums){
            total_moves += abs(x-median);
        }
        return total_moves;
    }
};