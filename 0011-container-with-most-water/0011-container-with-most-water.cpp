class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxWater = 0;
        int n = height.size();
        int left = 0;
        int right = n-1;
        int capacity = 0;
        while(left<right){
            capacity = (right-left) * min(height[left], height[right]);
            maxWater = max(maxWater, capacity);
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