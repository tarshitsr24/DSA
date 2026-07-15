class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int odd_sum = n*n;
        int even_sum = n*(n+1);
        int temp;
        while(odd_sum!=0){
            temp = odd_sum;
            odd_sum = even_sum % odd_sum;
        }
        return temp;
        
    }
};