class Solution {
public:
    set<string> combine(set<string> &a, set<string> &b) {
        set<string> result;

        for (string x : a) {
            for (string y : b) {
                result.insert(x + y);
            }
        }

        return result;
    }

    set<string> solve(string &s, int &i) {
        set<string> result;
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                // Union: add current possibilities to result
                for (string x : current) {
                    result.insert(x);
                }

                current = {""};
                i++;
            }

            else {
                set<string> next;

                if (s[i] == '{') {
                    i++; // skip '{'
                    next = solve(s, i);
                    i++; // skip '}'
                }
                else {
                    // Single letter
                    next.insert(string(1, s[i]));
                    i++;
                }

                // Concatenation
                current = combine(current, next);
            }
        }

        // Add the final part
        for (string x : current) {
            result.insert(x);
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;

        set<string> ans = solve(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};