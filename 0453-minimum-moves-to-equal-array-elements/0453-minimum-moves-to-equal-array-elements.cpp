class Solution {
public:
    int minMoves(vector<int>& nums) {
        int small = *min_element(nums.begin(), nums.end());
        long long total_moves = 0;

        for(int x : nums){
            total_moves += (x - small);
        }

        return total_moves;
        
    }
};