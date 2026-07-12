class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sorted = arr;

        // Sort the copied array
        sort(sorted.begin(), sorted.end());

        // Map each unique value to its rank
        unordered_map<int, int> rank;
        int r = 1;

        for (int x : sorted) {
            if (rank.find(x) == rank.end()) {
                rank[x] = r++;
            }
        }

        // Replace each element with its rank
        for (int i = 0; i < arr.size(); i++) {
            arr[i] = rank[arr[i]];
        }

        return arr;
    }
};