class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<vector<int>> places;
           for(int i = 0; i<rows; i++){
            for(int j = 0; j<cols; j++){
                if(matrix[i][j] == 0){
                    places.push_back({i, j});
                }
            }
        }
        int prows = places.size();
        int pcols = 2;
        for (int i = 0; i < prows; i++) {
            for (int k = 0; k < cols; k++) {
                matrix[places[i][0]][k] = 0;
            }

            for (int k = 0; k < rows; k++) {
                matrix[k][places[i][1]] = 0;
            }
        }       
    }
};