class Solution {
public:
    int reverseDegree(string s) {
        int ans = 1;
        for(int i = 0; i<s.size(); i++){
            if(s[i]=='a'){
                ans += 26 * (i+1);
            }
            else if(s[i]=='b'){
                ans += 25 * (i+1);
            }
            else if(s[i]=='c'){
                ans += 24 * (i+1);
            }else if(s[i]=='d'){
                ans += 23 * (i+1);
            }else if(s[i]=='e'){
                ans += 22 * (i+1);
            }else if(s[i]=='f'){
                ans += 21 * (i+1);
            }else if(s[i]=='g'){
                ans += 20 * (i+1);
            }else if(s[i]=='h'){
                ans += 19 * (i+1);
            }else if(s[i]=='i'){
                ans += 18 * (i+1);
            }else if(s[i]=='j'){
                ans += 17 * (i+1);
            }else if(s[i]=='k'){
                ans += 16 * (i+1);
            }else if(s[i]=='l'){
                ans += 15 * (i+1);
            }else if(s[i]=='m'){
                ans += 14 * (i+1);
            }else if(s[i]=='n'){
                ans += 13 * (i+1);
            }else if(s[i]=='o'){
                ans += 12 * (i+1);
            }else if(s[i]=='p'){
                ans += 11 * (i+1);
            }else if(s[i]=='q'){
                ans += 10 * (i+1);
            }else if(s[i]=='r'){
                ans += 9 * (i+1);
            }else if(s[i]=='s'){
                ans += 8 * (i+1);
            }else if(s[i]=='t'){
                ans += 7 * (i+1);
            }else if(s[i]=='u'){
                ans += 6 * (i+1);
            }else if(s[i]=='v'){
                ans += 5 * (i+1);
            }else if(s[i]=='w'){
                ans += 4 * (i+1);
            }else if(s[i]=='x'){
                ans += 3 * (i+1);
            }else if(s[i]=='y'){
                ans += 2 * (i+1);
            }else if(s[i]=='z'){
                ans += 1 * (i+1);
            }

        }
        return ans-1;
    }
};