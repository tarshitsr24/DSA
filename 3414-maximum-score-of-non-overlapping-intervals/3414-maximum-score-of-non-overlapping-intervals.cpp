class Solution {
public:
    struct State {
        long long score = 0;
        vector<int> idx;
    };

    // Return the better state:
    // 1. Larger score
    // 2. If same score, lexicographically smaller indices
    State better(const State& a, const State& b) {
        if (a.score != b.score)
            return (a.score > b.score) ? a : b;

        return (a.idx < b.idx) ? a : b;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {right, left, weight, original index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][1],
                intervals[i][0],
                intervals[i][2],
                i
            });
        }

        // Sort by ending position
        sort(a.begin(), a.end());

        // Store ends separately for binary search
        vector<long long> ends(n);
        for (int i = 0; i < n; i++) {
            ends[i] = a[i][0];
        }

        /*
            dp[i][k] =
            best answer using first i intervals
            while choosing at most k intervals.

            i ranges 0...n
            k ranges 0...4
        */
        vector<vector<State>> dp(n + 1, vector<State>(5));

        for (int i = 1; i <= n; i++) {
            long long r = a[i - 1][0];
            long long l = a[i - 1][1];
            long long w = a[i - 1][2];
            int originalIndex = (int)a[i - 1][3];

            /*
                Find number of intervals ending strictly before l.

                Non-overlap requires:
                    previous.right < current.left

                lower_bound(l) gives first end >= l.
            */
            int p = lower_bound(ends.begin(), ends.begin() + (i - 1), l)
                    - ends.begin();

            for (int k = 1; k <= 4; k++) {

                // Option 1: Don't take current interval
                State skip = dp[i - 1][k];

                // Option 2: Take current interval
                State take = dp[p][k - 1];

                take.score += w;
                take.idx.push_back(originalIndex);

                // Indices must be in increasing order for lexicographic comparison
                sort(take.idx.begin(), take.idx.end());

                dp[i][k] = better(skip, take);
            }
        }

        return dp[n][4].idx;
    }
};