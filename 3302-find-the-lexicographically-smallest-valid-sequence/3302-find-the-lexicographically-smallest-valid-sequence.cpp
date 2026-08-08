class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        
        int n = word1.size();
        int m = word2.size();

        // dp[i] = latest index in word1 from which
        // word2[i...] can be matched exactly
        vector<int> dp(m + 1, -1);

        // Empty string can always be matched
        dp[m] = n;

        int j = n - 1;

        // Build DP from right to left
        for (int i = m - 1; i >= 0; i--) {

            while (j >= 0 && word1[j] != word2[i]) {
                j--;
            }

            if (j < 0)
                break;

            dp[i] = j;
            j--;
        }

        vector<int> ans;

        j = 0;
        bool used = false;

        // Construct lexicographically smallest answer
        for (int i = 0; i < m; i++) {

            bool found = false;

            while (j < n) {

                // Characters match
                if (word1[j] == word2[i]) {
                    ans.push_back(j);
                    j++;
                    found = true;
                    break;
                }

                // Use the one allowed mismatch
                if (!used && j < dp[i + 1]) {
                    ans.push_back(j);
                    j++;
                    used = true;
                    found = true;
                    break;
                }

                j++;
            }

            if (!found)
                return {};
        }

        return ans;
    }
};