class Solution {
    struct Group {
        int start, end, len;
    };

public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        
        // 1. Calculate the total baseline '1's in the ENTIRE string.
        // A trade only mutates bits inside s[l...r]. 
        // The net change in the number of '1's inside s[l...r] directly applies to the whole string.
        int total_ones = 0;
        for (char c : s) {
            if (c == '1') total_ones++;
        }

        // 2. Identify all contiguous blocks of '0's in the string
        vector<Group> zero_groups;
        for (int i = 0; i < n; ) {
            if (s[i] == '0') {
                int j = i;
                while (j < n && s[j] == '0') j++;
                zero_groups.push_back({i, j - 1, j - i});
                i = j;
            } else {
                i++;
            }
        }

        int m = zero_groups.size();

        // 3. Precompute mappings for O(1) index bounds lookup
        vector<int> zero_at_or_after(n, m);
        vector<int> zero_at_or_before(n, -1);

        int g_idx = 0;
        for (int i = 0; i < n; ++i) {
            while (g_idx < m && zero_groups[g_idx].end < i) {
                g_idx++;
            }
            zero_at_or_after[i] = g_idx;
        }

        g_idx = m - 1;
        for (int i = n - 1; i >= 0; --i) {
            while (g_idx >= 0 && zero_groups[g_idx].start > i) {
                g_idx--;
            }
            zero_at_or_before[i] = g_idx;
        }

        // 4. Build a Sparse Table over the pairs of adjacent zero blocks
        // A trade turning a '1' block to '0's merges two adjacent zero blocks. 
        // Turning them to '1's yields a net gain equal to the sum of their initial '0' lengths.
        int m_pairs = max(0, m - 1);
        int K = 0;
        while ((1 << K) <= m_pairs) K++;
        K = max(1, K); // Ensure at least size 1 for empty/small cases
        
        vector<vector<int>> st(K, vector<int>(m_pairs, 0));

        for (int i = 0; i < m_pairs; ++i) {
            st[0][i] = zero_groups[i].len + zero_groups[i + 1].len;
        }

        for (int j = 1; j < K; ++j) {
            for (int i = 0; i + (1 << j) <= m_pairs; ++i) {
                st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }

        auto query_st = [&](int L, int R) {
            if (L > R) return 0;
            int j = 31 - __builtin_clz(R - L + 1);
            return max(st[j][L], st[j][R - (1 << j) + 1]);
        };

        // Helper to get the length of a zero group clamped strictly within [l, r]
        auto get_len = [&](int idx, int l, int r) {
            int start = max(zero_groups[idx].start, l);
            int end = min(zero_groups[idx].end, r);
            return max(0, end - start + 1);
        };

        vector<int> ans;
        ans.reserve(queries.size());

        // 5. Answer each query
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];

            int first = zero_at_or_after[l];
            int last = zero_at_or_before[r];

            // If there are fewer than 2 zero blocks intersecting [l, r], no valid trade is possible.
            // Baseline 1s in the entire string is the answer.
            if (first >= last) {
                ans.push_back(total_ones);
                continue;
            }

            int max_gain = 0;

            // Candidate 1: Leftmost adjacent pair (Group `first` and `first+1`)
            max_gain = max(max_gain, get_len(first, l, r) + get_len(first + 1, l, r));

            // Candidate 2: Rightmost adjacent pair (Group `last-1` and `last`)
            max_gain = max(max_gain, get_len(last - 1, l, r) + get_len(last, l, r));

            // Candidate 3: Any entirely unclipped internal adjacent pairs
            if (first + 1 <= last - 2) {
                max_gain = max(max_gain, query_st(first + 1, last - 2));
            }

            // The final answer is the baseline 1s over the whole string + max trade net gain
            ans.push_back(total_ones + max_gain);
        }

        return ans;
    }
};