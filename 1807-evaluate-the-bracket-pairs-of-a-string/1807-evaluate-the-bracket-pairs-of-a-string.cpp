class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;
        
        // Store key -> value
        for (auto &x : knowledge) {
            mp[x[0]] = x[1];
        }
        
        string ans;
        
        for (int i = 0; i < s.size(); i++) {
            
            if (s[i] == '(') {
                int j = i + 1;
                
                // Find closing bracket
                while (s[j] != ')') {
                    j++;
                }
                
                // Extract key
                string key = s.substr(i + 1, j - i - 1);
                
                // Check if key exists
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }
                
                // Skip everything up to ')'
                i = j;
            }
            else {
                ans += s[i];
            }
        }
        
        return ans;
    }
};