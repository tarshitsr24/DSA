class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int half = n / 2;

        // Count characters
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Check if a palindrome is possible
        int odd = 0;
        int middle = -1;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                middle = i;
            }
        }

        if (odd > 1)
            return "";

        // Characters available in the left half
        vector<int> cnt(26);

        for (int i = 0; i < 26; i++) {
            cnt[i] = freq[i] / 2;
        }

        // Build palindrome from its left half
        auto build = [&](string left) {
            string ans = left;

            if (n % 2)
                ans += char('a' + middle);

            string right = left;
            reverse(right.begin(), right.end());

            ans += right;

            return ans;
        };

        string prefix = target.substr(0, half);

        /*
         * First check whether prefix itself can be the left half.
         */
        vector<int> remaining = cnt;
        bool canMakePrefix = true;

        for (char c : prefix) {
            if (remaining[c - 'a'] == 0) {
                canMakePrefix = false;
                break;
            }

            remaining[c - 'a']--;
        }

        /*
         * If prefix can be formed, the palindrome using exactly
         * this prefix is the smallest possible palindrome whose
         * left half is >= prefix.
         *
         * It might already be greater than target.
         */
        if (canMakePrefix) {
            string candidate = build(prefix);

            if (candidate > target)
                return candidate;
        }

        /*
         * Now find the smallest multiset permutation strictly
         * greater than prefix.
         *
         * We try to keep the prefix equal for as long as possible,
         * then increase one character.
         */
        for (int pos = half - 1; pos >= 0; pos--) {

            vector<int> available = cnt;
            string left;
            bool possible = true;

            // Match target prefix before pos
            for (int i = 0; i < pos; i++) {
                int c = prefix[i] - 'a';

                if (available[c] == 0) {
                    possible = false;
                    break;
                }

                left += prefix[i];
                available[c]--;
            }

            if (!possible)
                continue;

            /*
             * At pos, choose the smallest character that is
             * strictly greater than prefix[pos].
             */
            int wanted = prefix[pos] - 'a';
            int chosen = -1;

            for (int c = wanted + 1; c < 26; c++) {
                if (available[c] > 0) {
                    chosen = c;
                    break;
                }
            }

            if (chosen == -1)
                continue;

            left += char('a' + chosen);
            available[chosen]--;

            // Fill remaining positions with smallest characters
            for (int c = 0; c < 26; c++) {
                while (available[c] > 0) {
                    left += char('a' + c);
                    available[c]--;
                }
            }

            return build(left);
        }

        return "";
    }
};