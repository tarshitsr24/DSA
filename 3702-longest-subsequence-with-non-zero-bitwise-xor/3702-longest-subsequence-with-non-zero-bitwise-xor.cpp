class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int val = nums[0];
        bool allZero = true;
        int n = nums.size();
        for(int i = 1; i<n; i++){
            if(nums[i]!=0){
                allZero = false;
            }
            val = val^nums[i];
        }
        if(allZero == true && nums[0]==0){
            return 0;
        }
        else if(val!=0){
            return n;
        }
        else{
            return n-1;
        }
        
    }
};