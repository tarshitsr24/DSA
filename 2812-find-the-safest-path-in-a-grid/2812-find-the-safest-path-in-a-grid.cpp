class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {

        int n = grid.size();

        // If start or end has a thief, answer is 0.
        if(grid[0][0] == 1 || grid[n-1][n-1] == 1)
            return 0;

        // Step 1: Distance of every cell to nearest thief.
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

        queue<pair<int,int>> q;

        // Push every thief into the queue.
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    dist[i][j]=0;
                    q.push({i,j});
                }
            }
        }

        int dr[4]={-1,1,0,0};
        int dc[4]={0,0,-1,1};

        // Multi-source BFS
        while(!q.empty()){

            auto [r,c]=q.front();
            q.pop();

            for(int k=0;k<4;k++){

                int nr=r+dr[k];
                int nc=c+dc[k];

                if(nr>=0 && nr<n && nc>=0 && nc<n &&
                   dist[nr][nc]==INT_MAX){

                    dist[nr][nc]=dist[r][c]+1;
                    q.push({nr,nc});
                }
            }
        }

        // Step 2: Modified Dijkstra (maximum minimum value)

        priority_queue<vector<int>> pq;

        vector<vector<int>> best(n, vector<int>(n,-1));

        pq.push({dist[0][0],0,0});
        best[0][0]=dist[0][0];

        while(!pq.empty()){

            auto curr=pq.top();
            pq.pop();

            int safe=curr[0];
            int r=curr[1];
            int c=curr[2];

            if(r==n-1 && c==n-1)
                return safe;

            for(int k=0;k<4;k++){

                int nr=r+dr[k];
                int nc=c+dc[k];

                if(nr>=0 && nr<n && nc>=0 && nc<n){

                    int newSafe=min(safe,dist[nr][nc]);

                    if(newSafe>best[nr][nc]){

                        best[nr][nc]=newSafe;
                        pq.push({newSafe,nr,nc});
                    }
                }
            }
        }

        return 0;
    }
};