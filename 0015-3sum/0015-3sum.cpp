class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set <vector<int>> result;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for(int i = 0; i<n-2; i++){
            int left = i+1;
        int right = n-1;
        while(left<right){
            int sum = nums[i]+nums[left]+nums[right];
            if(sum==0){
                result.insert({nums[i],nums[left],nums[right]});
                left++;
                right--;
           }else if(sum<0){
            left++;
           }else if(sum>0){
            right--;
           }
           
        }
        }
        
        return {result.begin(), result.end()};
        
    }
};