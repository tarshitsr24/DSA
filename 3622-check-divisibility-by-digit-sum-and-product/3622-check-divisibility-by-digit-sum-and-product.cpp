class Solution {
public:
    bool checkDivisibility(int n) {
        int sum = 0;
        int pro = 1;
        int m = n;
        while(true){
            sum += m%10;
            pro = pro * (m%10);
            m = m/10;
            if(m==0){
                break;
            } 
        }
        if( n%(sum+pro) == 0){
            return true;
        }else{
            return false;
        }
    }
};