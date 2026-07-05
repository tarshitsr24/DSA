class Solution {
public:
    const int MOD = 1e9 + 7;

    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();

        // score[i][j] = maximum score to reach (i,j)
        vector<vector<int>> score(n, vector<int>(n, -1));

        // ways[i][j] = number of maximum-score paths
        vector<vector<long long>> ways(n, vector<long long>(n, 0));

        score[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (board[i][j] == 'X') continue;
                if (i == n - 1 && j == n - 1) continue;

                int best = -1;
                long long cnt = 0;

                // From below
                if (i + 1 < n && score[i + 1][j] != -1) {
                    if (score[i + 1][j] > best) {
                        best = score[i + 1][j];
                        cnt = ways[i + 1][j];
                    } else if (score[i + 1][j] == best) {
                        cnt = (cnt + ways[i + 1][j]) % MOD;
                    }
                }

                // From right
                if (j + 1 < n && score[i][j + 1] != -1) {
                    if (score[i][j + 1] > best) {
                        best = score[i][j + 1];
                        cnt = ways[i][j + 1];
                    } else if (score[i][j + 1] == best) {
                        cnt = (cnt + ways[i][j + 1]) % MOD;
                    }
                }

                // From bottom-right (diagonal)
                if (i + 1 < n && j + 1 < n && score[i + 1][j + 1] != -1) {
                    if (score[i + 1][j + 1] > best) {
                        best = score[i + 1][j + 1];
                        cnt = ways[i + 1][j + 1];
                    } else if (score[i + 1][j + 1] == best) {
                        cnt = (cnt + ways[i + 1][j + 1]) % MOD;
                    }
                }

                if (best == -1) continue;

                score[i][j] = best;

                if (board[i][j] >= '1' && board[i][j] <= '9')
                    score[i][j] += board[i][j] - '0';

                ways[i][j] = cnt % MOD;
            }
        }

        if (ways[0][0] == 0) return {0, 0};

        return {score[0][0], (int)ways[0][0]};
    }
};