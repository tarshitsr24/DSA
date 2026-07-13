class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        
        string s = "123456789";
        vector<int> nums;
        for(int i = 2; i<=9; i++){
            for(int j = 0; (i+j)<=9; j++){
                int num = stoi(s.substr(j, i));
                if(num>= low && num<=high){
                    nums.push_back(num);
                }
            }
        }
    return nums;   
        
    }
};