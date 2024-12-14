/**
 *    author:  Phung Duc Minh
 *    created: 12.12.2024 18:38:31
**/

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

#include <bits/stdc++.h>
#define int long long

using namespace std;

// Link: https://hnoj.edu.vn/problem/jump

const int MAXN = 1e5 + 15;
int n, p, IT[MAXN * 4];
vector<int> vec;

void update(int idx, int l, int r, int pos, int val) {
    if (pos < l || pos > r) return;
    if (l == r) {
        IT[idx] = val;
        return;
    }
    int mid = (l + r) / 2;
    update(idx * 2 + 1, l, mid, pos, val);
    update(idx * 2 + 2, mid + 1, r, pos, val);
    IT[idx] = min(IT[idx * 2 + 1], IT[idx * 2 + 2]);
}

int query(int idx, int l, int r, int u, int v) {
    if (v < l || u > r) return 1e18;
    if (u <= l && r <= v) return IT[idx];
    int mid = (l + r) / 2;
    return min(query(idx * 2 + 1, l, mid, u, v),
               query(idx * 2 + 2, mid + 1, r, u, v));
}

int binsearch(int idx, int l, int r, int u, int v, int val) {
    if (l > v || r < u || IT[idx] > val) return -1; 
    if (l == r) return l;
    int mid = (l + r) / 2;
    int res = binsearch(idx * 2 + 1, l, mid, u, v, val);
    if (res != -1) return res;
    return binsearch(idx * 2 + 2, mid + 1, r, u, v, val);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> p;
    vec.resize(n);
    
    for(int i = 0; i < n; i++) {
        cin >> vec[i];
        update(0, 0, n - 1, i, vec[i]);
    }
    
    int len = 0;
    for(int j = 0; j < n; j++) {
        int tmp = vec[j] - p;
        if(tmp < 0) continue; 
        int pos = binsearch(0, 0, n - 1, 0, j, tmp);
        if(pos != -1) len = max(len, j - pos);
    }
    
    cout << len;
    return 0;
}
