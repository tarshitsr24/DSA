class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        int ans = k;
        while(true){
            bool found = false;
            for(int num : nums){
                if(num == ans){
                    found = true;
                    break;
                }
            }
            if(!found){
                return ans;
            }
            ans += k;
        }
        return ans;
        
    }
};