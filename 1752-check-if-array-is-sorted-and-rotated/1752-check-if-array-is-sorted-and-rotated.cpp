class Solution {
public:
    bool check(vector<int>& nums) {
        int n = nums.size();
        vector<int> duplicate = nums;
        sort(duplicate.begin(), duplicate.end());
        int temp = 0;
        bool ans = false;
        for(int i = 0; i<n;i++){
            temp = duplicate[0];
            for(int j = 0; j<n-1;j++){
                    duplicate[j] = duplicate[j+1]; 
            }
            duplicate[n-1] = temp;
            
            if(duplicate == nums){
                ans = true;
                break;
            }
        }
        if(ans == true){
            return true;
        }else{
            return false;
        }
        
    }
};