#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, T;
    cin >> n >> T;

    vector<int> time(n + 1);
    vector<ll> value(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> time[i] >> value[i];
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(T + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= T; j++) {
            if (time[i] > j) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - time[i]] + value[i]);
            }
        }
    }

    cout << dp[n][T] << "\n";

    return 0;
}