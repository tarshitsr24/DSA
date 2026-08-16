class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        // If there are no stones with remainder 1 or 2,
        // Alice cannot avoid losing / Bob wins.
        if (cnt[1] == 0 && cnt[2] == 0)
            return false;

        // If number of remainder-0 stones is even,
        // Alice wins if either side (1 or 2) has enough stones
        // to create a winning sequence.
        if (cnt[0] % 2 == 0) {
            return cnt[1] >= 1 && cnt[2] >= 1;
        }

        // If cnt[0] is odd, Alice needs an imbalance
        // between the number of 1s and 2s.
        return abs(cnt[1] - cnt[2]) > 2;
    }
};