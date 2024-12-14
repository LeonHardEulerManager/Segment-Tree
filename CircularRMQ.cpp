/**
 *    author:  Phung Duc Minh
 *    created: 6.12.2024 19:35:04
**/

#include <bits/stdc++.h>

#define int long long

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

// Link: https://codeforces.com/contest/52/problem/C

const int MAXN = 2e5;

int n, m, IT[4 * MAXN], lazy[4 * MAXN];
vector<int> vec;

void build(int idx, int left, int right) {
    if(left == right) {
        IT[idx] = vec[left];
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    IT[idx] = min(IT[idx * 2 + 1], IT[idx * 2 + 2]);
}

void push(int idx, int left, int right) {
    if(lazy[idx] != 0) {
        IT[idx] += lazy[idx];
        if(left != right) {
            lazy[idx * 2 + 1] += lazy[idx];
            lazy[idx * 2 + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }
}

void update(int idx, int left, int right, int u, int v, int val) {
    push(idx, left, right);
    if(right < u || v < left) return;
    if(u <= left && right <= v) {
        lazy[idx] += val;
        push(idx, left, right);
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, u, v, val);
    update(idx * 2 + 2, mid + 1, right, u, v, val);
    IT[idx] = min(IT[idx * 2 + 1], IT[idx * 2 + 2]);
}

int query(int idx, int left, int right, int u, int v) {
    push(idx, left, right);
    if(right < u || v < left) return 1e9 + 15;
    if(u <= left && right <= v) return IT[idx];
    int mid = (left + right) / 2;
    int q1 = query(idx * 2 + 1, left, mid, u, v);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return min(q1, q2);
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  //cin >> tt;
  while (tt--) {
    cin >> n; vec.resize(n);
    for(auto &x : vec) cin >> x;
    build(0, 0, n - 1);
    cin >> m;
    cin.ignore();
    while(m--) {
        int l, r, v;
        string s;
        getline(cin, s);
        stringstream st(s);
        st >> l; st >> r;
        // increase
        if(st >> v) {
            if(r < l) {
                update(0, 0, n - 1, l, n - 1, v);
                update(0, 0, n - 1, 0, r, v);
            } else update(0, 0, n - 1, l, r, v);
        } else {
            if(r < l) {
                cout << min(query(0, 0, n - 1, l, n - 1), query(0, 0, n - 1, 0, r)) << "\n";
            } else cout << query(0, 0, n - 1, l, r) << "\n";
        }
    }
  }
  return 0;
}