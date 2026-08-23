class Solution {
public:
    bool sumGame(string num) {
        int len = num.size();
        int left = 0;
        int right = 0;
        int q_left=0;
        int q_right=0;
        int q_total=0;
        for(int i = 0; i<(len/2);i++){
            if(num[i]!= '?'){
                left += num[i] - '0';
            }else{
                q_left++;
            }
        }
        for(int i = (len/2); i<len;i++){
            if(num[i]!= '?'){
                right += num[i] - '0';
            }else{
                q_right++;
            }
        }
        return (left - right) * 2 != (q_right - q_left) * 9; 
    }
};