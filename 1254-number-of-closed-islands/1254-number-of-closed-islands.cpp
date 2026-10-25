class Solution {
private:
    int dfs(int r, int c, const vector<vector<int>>& grid, vector<vector<bool>>& visit) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Hitting a boundary means the land is connected to an edge (not closed)
        if (r < 0 || c < 0 || r == rows || c == cols) {
            return 0;
        }

        // Hitting water or an already explored part of this component
        if (grid[r][c] == 1 || visit[r][c]) {
            return 1;
        }

        visit[r][c] = true;

        // std::min evaluates all four branches completely, preventing short-circuiting
        // so the entire island is traversed and marked in visit
        return min({
            dfs(r + 1, c, grid, visit),
            dfs(r - 1, c, grid, visit),
            dfs(r, c + 1, grid, visit),
            dfs(r, c - 1, grid, visit)
        });
    }

public:
    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visit(rows, vector<bool>(cols, false));

        int res = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 0 && !visit[r][c]) {
                    res += dfs(r, c, grid, visit);
                }
            }
        }
        return res;
    }
};