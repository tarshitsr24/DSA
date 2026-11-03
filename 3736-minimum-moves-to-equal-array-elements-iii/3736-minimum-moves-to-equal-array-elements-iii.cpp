class Solution {
public:
    int minMoves(vector<int>& nums) {
        // sort(nums.begin(), nums.end());
        int max_num = *max_element(nums.begin(), nums.end());
        long long moves = 0;
        for(int i = 0; i<nums.size(); i++){
            moves += (max_num - nums[i]);
        }
return moves;
        
    }
};