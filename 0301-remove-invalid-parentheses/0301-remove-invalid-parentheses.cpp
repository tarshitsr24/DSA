class Solution {
public:
    bool isValid(string s) {
        int count = 0;

        for(char c : s) {
            if(c == '(') {
                count++;
            }
            else if(c == ')') {
                count--;

                if(count < 0)
                    return false;
            }
        }

        return count == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;

        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while(!q.empty()) {
            string curr = q.front();
            q.pop();

            // If this string is valid, add it to answer
            if(isValid(curr)) {
                ans.push_back(curr);
                found = true;
            }

            // Don't remove more parentheses if we already
            // found valid strings at this level
            if(found)
                continue;

            // Try removing each parenthesis
            for(int i = 0; i < curr.size(); i++) {

                if(curr[i] != '(' && curr[i] != ')')
                    continue;

                string next = curr.substr(0, i) + curr.substr(i + 1);

                if(visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};