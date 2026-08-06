class Solution {
public:
    int smallestNumber(int n, int t) {
        bool e = true;
        int num = n;
        int pro = 1;
        
        while(e == true){
            int temp = num;
            string str = to_string(temp);
            int len = str.length();          
            for(int i = 0; i<len; i++){
                pro = pro * (temp%10);
                temp = temp/10;
            }
            if(pro%t==0){
                e = false;
            }else{
                num += 1;
                pro=1;
            }
        }
        return num;
    }
};






