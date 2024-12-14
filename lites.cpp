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

/* Note:
    turn on
    turn off
    Chú ý:
    nhấn vào công tắc 2 lần -> không nhấn
    chú ý vị trí của thao tác push
*/

const int MAXN = 1e5 + 5;

int n, m, IT[4 * MAXN], lazy[4 * MAXN];

void push(int idx, int left, int right) {
    if(lazy[idx]) {
        int mid = (left + right) / 2;
        IT[idx * 2 + 1] = (mid - left + 1) - IT[idx * 2 + 1];
        IT[idx * 2 + 2] = (right - mid) - IT[idx * 2 + 2];
        lazy[idx * 2 + 1] ^= 1;
        lazy[idx * 2 + 2] ^= 1;
        lazy[idx] = 0;
    }
}

void update(int idx, int left, int right, int u, int v) {
    if(right < u || v < left) return;
    if(u <= left && right <= v) {
        IT[idx] = right - left + 1 - IT[idx]; 
        lazy[idx] ^=1;
        return;
    }
    push(idx, left, right);
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, u, v);
    update(idx * 2 + 2, mid + 1, right, u, v);
    IT[idx] = IT[idx * 2 + 1] + IT[idx * 2 + 2];
}

int query(int idx, int left, int right, int u, int v) {
    if(right < u || v < left) return 0;
    if(u <= left && right <= v) return IT[idx];
    push(idx, left, right);
    int mid = (left + right) / 2;
    int q1 = query(idx * 2 + 1, left, mid, u, v);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return q1 + q2;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        cin >> n >> m;
        while(m--) {
            int type, l, r; cin >> type >> l >> r;
            l--; r--;
            if(!type) update(0, 0, n - 1, l, r);
            else cout << query(0, 0, n - 1, l, r) << "\n";
        }
    }
    return 0;
}