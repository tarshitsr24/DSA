class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        string ans = "";

        for (int i = 0; i < target.size(); i++) {

            // Try to keep the current character equal to target[i]
            if (freq[target[i] - 'a'] > 0) {
                ans += target[i];
                freq[target[i] - 'a']--;
            }
            else {
                // We cannot continue matching target.
                // So go back and find a position where
                // we can put something greater.
                break;
            }
        }

        // If we matched the entire target,
        // the answer must be a permutation strictly greater.
        // So we need to backtrack.
        if (ans.size() == target.size()) {
            for (int i = ans.size() - 1; i >= 0; i--) {

                freq[ans[i] - 'a']++;

                // Find the smallest character greater than target[i]
                for (int c = target[i] - 'a' + 1; c < 26; c++) {

                    if (freq[c] > 0) {
                        string res = ans.substr(0, i);
                        res += char('a' + c);
                        freq[c]--;

                        // Append remaining characters smallest first
                        for (int j = 0; j < 26; j++) {
                            while (freq[j] > 0) {
                                res += char('a' + j);
                                freq[j]--;
                            }
                        }

                        return res;
                    }
                }
            }

            return "";
        }

        // We couldn't completely match target.
        // ans currently contains the longest matching prefix.
        int i = ans.size();

        // Find smallest character greater than target[i]
        for (int c = target[i] - 'a' + 1; c < 26; c++) {

            if (freq[c] > 0) {
                string res = ans;
                res += char('a' + c);
                freq[c]--;

                // Append remaining characters in sorted order
                for (int j = 0; j < 26; j++) {
                    while (freq[j] > 0) {
                        res += char('a' + j);
                        freq[j]--;
                    }
                }

                return res;
            }
        }

        // Couldn't make current position greater,
        // so backtrack.
        for (int j = ans.size() - 1; j >= 0; j--) {

            freq[ans[j] - 'a']++;

            for (int c = target[j] - 'a' + 1; c < 26; c++) {

                if (freq[c] > 0) {
                    string res = ans.substr(0, j);
                    res += char('a' + c);
                    freq[c]--;

                    for (int k = 0; k < 26; k++) {
                        while (freq[k] > 0) {
                            res += char('a' + k);
                            freq[k]--;
                        }
                    }

                    return res;
                }
            }
        }

        return "";
    }
};