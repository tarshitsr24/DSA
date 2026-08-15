class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int val = 0;
        bool allZero = true;
        int n = nums.size();
        for(int i = 0; i<n; i++){
            if(nums[i]!=0){
                allZero = false;
            }
            val = val^nums[i];
        }
        if(allZero == true ){
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