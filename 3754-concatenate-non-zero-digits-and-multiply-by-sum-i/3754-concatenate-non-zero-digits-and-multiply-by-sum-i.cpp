class Solution {
public:
    long long sumAndMultiply(int n) {
        long long x = 0;
        long long temp = n;
        long long digit;
        long long multiplier = 1;
        long long zero_count = 0;
        long long sum = 0;
        while(temp>0){
            digit = temp%10;
            temp = temp /10;
            if(digit != 0){
                sum = sum + digit;
                x = x + (digit*multiplier);
                multiplier = multiplier * 10;
            } 
            else{
                zero_count = zero_count + 1;
            }         
        }
        if (zero_count == 0){
            return x*sum;
        }
        else{
            return x*sum;
        }
    }
};