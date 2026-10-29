class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> spiral;
        int top = 0;
        int bottom = m - 1;
        int left = 0;
        int right = n - 1;

        while(top<=bottom && left<=right){
            
            for(int j = left; j <= right; j++) {
            spiral.push_back(matrix[top][j]);
            }
            top++;

             // 2. Down
    for(int i = top; i <= bottom; i++) {
        spiral.push_back(matrix[i][right]);
    }
    right--;

    // 3. Left
    if(top <= bottom) {
        for(int j = right; j >= left; j--) {
            spiral.push_back(matrix[bottom][j]);
        }
        bottom--;
    }

    // 4. Up
    if(left <= right) {
        for(int i = bottom; i >= top; i--) {
            spiral.push_back(matrix[i][left]);
        }
        left++;
    }
            

        }

        return spiral;
        
        
    }
};