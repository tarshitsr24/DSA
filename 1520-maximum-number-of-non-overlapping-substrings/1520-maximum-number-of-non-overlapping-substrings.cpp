class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int n = s.size();

        // First and last occurrence of every character
        vector<int> first(26, n);
        vector<int> last(26, -1);

        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            first[c] = min(first[c], i);
            last[c] = i;
        }

        // Store valid intervals [start, end]
        vector<pair<int, int>> intervals;

        for (int c = 0; c < 26; c++) {
            if (last[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];
            bool valid = true;

            // Expand interval if it contains another character
            // whose complete range is outside the current interval
            for (int i = l; i <= r; i++) {
                int x = s[i] - 'a';

                if (first[x] < l) {
                    valid = false;
                    break;
                }

                r = max(r, last[x]);
            }

            if (valid)
                intervals.push_back({l, r});
        }

        // Sort by ending position
        sort(intervals.begin(), intervals.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.second < b.second;
             });

        vector<string> ans;
        int prevEnd = -1;

        // Greedy: choose interval with earliest ending position
        for (auto [l, r] : intervals) {
            if (l > prevEnd) {
                ans.push_back(s.substr(l, r - l + 1));
                prevEnd = r;
            }
        }

        return ans;
    }
};