class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        set <int> SetHuMein;

        for(int i = 0; i<nums.size(); i++){
            if(!SetHuMein.insert(nums[i]).second){
                return true;
            }
        }
        return false;
        
    }
};