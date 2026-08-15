class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int count = 1;
        int val = nums[0];
        bool allZero = true;
        for(int i = 1; i<nums.size(); i++){
            if(nums[i]!=0){
                allZero = false;
            }
            val = val^nums[i];
            count++;
        }
        if(allZero == true && nums[0]==0){
            return 0;
        }
        else if(val!=0){
            return count;
        }
        else{
            return count-1;
        }
        
    }
};