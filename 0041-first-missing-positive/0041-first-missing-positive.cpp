class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int target = 1;
        for(int x : nums){
            if(x==target){
                target++;
            }
        }
        return target;
    }
};