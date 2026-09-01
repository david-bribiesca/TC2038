#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int m, n;
vector<vector<int>> grid;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int heuristic(int x, int y){
    return (m - 1 - x) + (n - 1 - y);
}

struct Node {
    int x, y;
    int cost;
    int bound;
    vector<vector<bool>> path;
};

struct CompareBound {
    bool operator()(const Node& a, const Node& b) const {
        return a.bound > b.bound;
    }
};

int main(){
    cin >> m >> n;
    grid.assign(m, vector<int>(n));
    for(int a = 0; a < m; a++)
        for(int b = 0; b < n; b++)
            cin >> grid[a][b];

    vector<vector<bool>> result(m, vector<bool>(n, false));

    if(grid[0][0] == 1){
        priority_queue<Node, vector<Node>, CompareBound> pq;

        Node root;
        root.x = 0; root.y = 0; root.cost = 0;
        root.bound = heuristic(0, 0);
        root.path.assign(m, vector<bool>(n, false));
        root.path[0][0] = true;
        pq.push(root);

        while(!pq.empty()){
            Node current = pq.top();
            pq.pop();

            if(current.x == m - 1 && current.y == n - 1){
                result = current.path;
                break;
            }

            for(int k = 0; k < 4; k++){
                int nx = current.x + dx[k];
                int ny = current.y + dy[k];

                bool inside = (nx >= 0 && nx < m && ny >= 0 && ny < n);
                if(inside && grid[nx][ny] == 1 && !current.path[nx][ny]){
                    Node child;
                    child.x = nx; child.y = ny;
                    child.cost = current.cost + 1;
                    child.bound = child.cost + heuristic(nx, ny);
                    child.path = current.path;
                    child.path[nx][ny] = true;
                    pq.push(child);
                }
            }
        }
    }
    cout << endl;
    for(int a = 0; a < m; a++){
        for(int b = 0; b < n; b++)
            cout << result[a][b] << " ";
        cout << endl;
    }

    return 0;
}