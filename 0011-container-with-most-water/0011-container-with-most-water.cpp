class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxWater = 0;
        int n = height.size();
        int left = 0;
        int right = n-1;
        while(left<right){
            maxWater = max(maxWater, ((right-left) * min(height[left], height[right])));
            if(height[left]<height[right]){
                left++;
            }
            else{
                right--;
            }
            
        }
        return maxWater;
    }
};