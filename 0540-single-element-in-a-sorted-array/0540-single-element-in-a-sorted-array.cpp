class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        set<int> s;
        set<int> duplicates;

        for (int x : nums) {
            if (!s.insert(x).second) {
                duplicates.insert(x);
            }
        }

        for (int x : s) {
            if (duplicates.find(x) == duplicates.end()) {
                return x;
            }
        }

        return -1;
    }
};