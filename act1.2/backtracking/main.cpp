#include <iostream>
#include <vector>
using namespace std;

int m, n;
vector<vector<bool>> grid, ans;

bool valid(int x, int y){
    return( 
        x < m && x>=0 && y<n && y>=0 && // limits in the matrix to prevent Seg fault 
        grid[x][y] == 1 &&              // the path is valid
        ans[x][y] == 0                  // we have not visited the position
    );
}

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

void dfs(int x, int y){
    for(int k = 0 ; k<4 ; k++){
        int new_x = x + dx[k], new_y = y + dy[k];
        if(valid(new_x, new_y)){
            ans[new_x][new_y] = 1;
            dfs(new_x, new_y);
            if(ans[m-1][n-1]){
                return;
            }
            ans[new_x][new_y] = 0;
        }
    }
}

int main(){

    cin >> m >> n;
    grid.resize(m, vector<bool>(n));
    ans.resize(m, vector<bool>(n));
    bool t;
    for(int i = 0 ; i < m ; i++){
        for(int j = 0 ; j<n ; j++){
            cin >> t;
            grid[i][j] = t;
        }
    }
    cout << endl;
    dfs(0,0);
    ans[0][0] = 1;
    for(int i = 0 ; i<m ; i++, cout << endl){
        for(int j = 0 ; j<n ; j++){
            cout << ans[i][j] << " ";
        }
    }
}