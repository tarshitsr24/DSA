class Solution {
public:
    static const int MOD = 1e9 + 7;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {

        int n = s.size();

        vector<int> pos;
        vector<long long> digit;

        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                digit.push_back(s[i] - '0');
            }
        }

        int k = pos.size();

        vector<long long> prefSum(k + 1, 0);
        vector<long long> prefHash(k + 1, 0);

        for (int i = 0; i < k; i++) {
            prefSum[i + 1] = prefSum[i] + digit[i];
            prefHash[i + 1] = (prefHash[i] * 10 + digit[i]) % MOD;
        }

        vector<long long> pow10(k + 1, 1);
        for (int i = 1; i <= k; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0], r = q[1];

            auto it1 = lower_bound(pos.begin(), pos.end(), l);
            auto it2 = upper_bound(pos.begin(), pos.end(), r);

            if (it1 == it2) {
                ans.push_back(0);
                continue;
            }

            int L = it1 - pos.begin();
            int R = (it2 - pos.begin()) - 1;

            long long sum = prefSum[R + 1] - prefSum[L];

            int len = R - L + 1;

            long long x =
                (prefHash[R + 1] -
                 prefHash[L] * pow10[len] % MOD +
                 MOD) % MOD;

            ans.push_back((x * sum) % MOD);
        }

        return ans;
    }
};