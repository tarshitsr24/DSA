class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int count = 0;

        // Frequency of each digit
        vector<int> freq(10, 0);

        for (int d : digits) {
            freq[d]++;
        }

        for (int num = 100; num <= 998; num += 2) {
            int n = num;

            int a = n / 100;          // hundreds digit
            int b = (n / 10) % 10;    // tens digit
            int c = n % 10;           // units digit

            // Check whether we have enough copies
            vector<int> need(10, 0);
            need[a]++;
            need[b]++;
            need[c]++;

            bool possible = true;

            for (int d = 0; d <= 9; d++) {
                if (need[d] > freq[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                count++;
            }
        }

        return count;
    }
};