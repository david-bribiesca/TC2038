#include <iostream>
#include <vector>
using namespace std;



int main(){
    int n, T;
    cin >> n >> T;
    vector<vector<int>> dp(n+1, vector<int>(T+1, 0));
    vector<int> time(n + 1), value(n + 1);

    for(int i = 1 ; i<=n ; i++){
        cin >> time[i];
    }
    for(int i = 1 ; i<=n ; i++){
        cin >> value[i];
    }
    for(int i = 1 ; i<=n ; i++){
        for(int j = 1 ; j<=T ; j++){
            if(time[i] > j){
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-time[i]] + value[i]);
            }
        }
    }
    cout << dp[n][T] << endl;
}