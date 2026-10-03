class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;

        function<void(string, int, int)> backtrack =
            [&](string s, int open, int close) {

                // We used all brackets
                if (open == n && close == n) {
                    ans.push_back(s);
                    return;
                }

                // Add '('
                if (open < n) {
                    backtrack(s + "(", open + 1, close);
                }

                // Add ')' only if it won't make the string invalid
                if (close < open) {
                    backtrack(s + ")", open, close + 1);
                }
            };

        backtrack("", 0, 0);

        return ans;
    }
};