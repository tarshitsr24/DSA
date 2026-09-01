class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();

        int sr = -1, sc = -1;
        int litterCount = 0;

        vector<vector<int>> id(m, vector<int>(n, -1));

        // Find S and assign an ID to every L
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (classroom[i][j] == 'S') {
                    sr = i;
                    sc = j;
                }

                if (classroom[i][j] == 'L') {
                    id[i][j] = litterCount++;
                }
            }
        }

        int totalMasks = 1 << litterCount;
        int target = totalMasks - 1;

        // maxEnergy[r][c][mask]
        // Maximum remaining energy with which we reached this state.
        vector<vector<vector<int>>> maxEnergy(
            m,
            vector<vector<int>>(
                n,
                vector<int>(totalMasks, -1)
            )
        );

        // {row, col, mask, remainingEnergy}
        queue<array<int, 4>> q;

        q.push({sr, sc, 0, energy});
        maxEnergy[sr][sc][0] = energy;

        int moves = 0;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int sz = q.size();

            while (sz--) {
                auto [r, c, mask, e] = q.front();
                q.pop();

                if (mask == target)
                    return moves;

                // If energy is 0, we cannot make another move.
                if (e == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];

                    if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                        continue;

                    if (classroom[nr][nc] == 'X')
                        continue;

                    int newEnergy = e - 1;
                    int newMask = mask;

                    // Collect litter
                    if (classroom[nr][nc] == 'L') {
                        int bit = id[nr][nc];
                        newMask |= (1 << bit);
                    }

                    // Reset energy
                    if (classroom[nr][nc] == 'R') {
                        newEnergy = energy;
                    }

                    /*
                        If we have already reached this exact
                        (position, mask) with MORE energy,
                        this state is useless.
                    */
                    if (maxEnergy[nr][nc][newMask] >= newEnergy)
                        continue;

                    maxEnergy[nr][nc][newMask] = newEnergy;

                    q.push({
                        nr,
                        nc,
                        newMask,
                        newEnergy
                    });
                }
            }

            moves++;
        }

        return -1;
    }
};