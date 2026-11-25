class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        // Step 1: Build suffix array
        vector<int> sa(n), rank(n), newRank(n);
        iota(sa.begin(), sa.end(), 0);

        for (int i = 0; i < n; i++)
            rank[i] = nums[i];

        for (int k = 1; k < n; k *= 2) {
            sort(sa.begin(), sa.end(), [&](int a, int b) {
                if (rank[a] != rank[b])
                    return rank[a] < rank[b];

                int ra = (a + k < n) ? rank[a + k] : -1;
                int rb = (b + k < n) ? rank[b + k] : -1;

                return ra < rb;
            });

            newRank[sa[0]] = 0;

            for (int i = 1; i < n; i++) {
                int a = sa[i - 1];
                int b = sa[i];

                int a2 = (a + k < n) ? rank[a + k] : -1;
                int b2 = (b + k < n) ? rank[b + k] : -1;

                newRank[b] = newRank[a] +
                    (rank[a] != rank[b] || a2 != b2);
            }

            rank.swap(newRank);

            if (rank[sa[n - 1]] == n - 1)
                break;
        }

        // Step 2: Calculate LCP using Kasai's algorithm
        vector<int> pos(n), lcp(n, 0);

        for (int i = 0; i < n; i++)
            pos[sa[i]] = i;

        int h = 0;

        for (int i = 0; i < n; i++) {
            int p = pos[i];

            if (p == 0) {
                h = 0;
                continue;
            }

            int j = sa[p - 1];

            while (i + h < n && j + h < n &&
                   nums[i + h] == nums[j + h]) {
                h++;
            }

            lcp[p] = h;

            if (h > 0)
                h--;
        }

        // Step 3: Find shortest unique substring
        int ans = n;

        for (int p = 0; p < n; p++) {
            int leftLCP = lcp[p];
            int rightLCP = (p + 1 < n) ? lcp[p + 1] : 0;

            int maxLCP = max(leftLCP, rightLCP);

            int start = sa[p];
            int shortestUnique = maxLCP + 1;

            if (shortestUnique <= n - start)
                ans = min(ans, shortestUnique);
        }

        return ans;
    }
};