#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
 
int main() {
 
    ios::sync_with_stdio(false);
 
    cin.tie(nullptr);
 
    int m;
 
    cin >> m;
    vector<pair<ll,ll>> meetings(m);
 
    for (int i = 0; i < m; i++) {
        long long s, e;
        cin >> s >> e;
        meetings[i] = {s, e};
    }

    vector<ll> starts(m), ends(m);
    for (int i = 0; i < m; i++) {
        starts[i] = meetings[i].first;
        ends[i]   = meetings[i].second;
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());
 
    int rooms = 0;
    int maxRooms = 0;
    int si = 0, ei = 0;
 
    while (si < m) {
        if (starts[si] < ends[ei]) {
            rooms++;
            maxRooms = max(maxRooms, rooms);
            si++;
        } else {
            rooms--;
            ei++;
        }
    }
 
    cout << maxRooms << "\n";
 
    return 0;
 
}
 