
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();

        vector<int> freq(n + 1, 0);

        int minPrice = INT_MAX;

        for (auto &item : items) {
            freq[item[0]]++;
            minPrice = min(minPrice, item[1]);
        }

        // Count items whose factors are multiples of f.
        vector<int> cnt(n + 1, 0);

        for (int f = 1; f <= n; f++) {
            for (int j = f; j <= n; j += f) {
                cnt[f] += freq[j];
            }
        }

        // Store {price, number of possible free items}.
        vector<pair<int, int>> v;

        for (auto &item : items) {
            int factor = item[0];
            int price = item[1];

            int freeCount = cnt[factor] - 1;

            if (price < 2LL * minPrice && freeCount > 0) {
                v.push_back({price, freeCount});
            }
        }

        // Cheapest items first.
        sort(v.begin(), v.end());

        long long ans = 0;
        long long remaining = budget;

        // Buy items that generate free copies.
        for (auto &[price, freeCount] : v) {
            long long take = min(
                (long long)freeCount,
                remaining / price
            );

            ans += 2 * take;
            remaining -= take * price;
        }

        // Spend remaining budget on the cheapest item.
        ans += remaining / minPrice;

        return (int)ans;
    }
};
