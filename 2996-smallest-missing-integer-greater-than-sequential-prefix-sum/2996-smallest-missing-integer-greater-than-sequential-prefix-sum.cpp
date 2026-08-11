class Solution {
public:
    int missingInteger(vector<int>& nums) {
        // sort(nums.begin(), nums.end());
        int n = nums.size();
        int sum = nums[0];
        int k = nums[0];
        for(int i = 1; i<n;i++){
            if(nums[i] == (k+1)){
                k++;
                sum += nums[i];
            }else{
                break;
            }   
        }
        // int ans = sum
        while(find(nums.begin(), nums.end(), sum) != nums.end()){
            sum++;
        }
     return sum;   
    }
};