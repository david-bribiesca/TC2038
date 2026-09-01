#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll mergeCount(int l, int mid, int r, vector<ll>& nums){
    int n = mid - l + 1, m = r - mid;
    vector<ll> left(n), right(m);
    for(int i = 0 ; i<n ; i++){
        left[i] = nums[l + i];
    }
    for(int i = 0 ; i<m ; i++){
        right[i] = nums[mid + 1 + i];
    }

    int i = 0, j = 0, k = l;
    ll ans = 0; 

    while(i<n && j<m){
        if (left[i] <= right[j]){
            nums[k++] = left[i++];
        } else {
            nums[k++] = right[j++];
            ans += (n - i);
        }
    }

    while (i < n)
        nums[k++] = left[i++];

    while (j < m)
        nums[k++] = right[j++];

    return ans;
}

ll mergeSort(int l, int r, vector<ll>& nums){

    if(l >= r){
        return 0;
    }

    ll mid = (l+r)/2;
    ll ans = 0;

    ans += mergeSort(l, mid, nums);
    ans += mergeSort(mid+1, r, nums);

    ans += mergeCount(l, mid, r, nums);
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    cin >> n;

    vector<ll> a(n);

    for (int i = 0; i < n; i++) cin >> a[i];

    ll inv = 0;
    inv = mergeSort(0, n-1, a);

    cout << inv << "\n";

    return 0;

}