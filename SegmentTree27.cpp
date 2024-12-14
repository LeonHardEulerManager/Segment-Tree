/**
 *    author:  Phung Duc Minh
 *    created: 26.11.2024 09:51:36
**/

#include <bits/stdc++.h>
#define maxn 100005

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

// chú ý a ^ a = 0
// Link submit: https://codeforces.com/contest/1872/problem/E

int SegmentTree[4 * maxn], n, q;
string s;
vector<long long> vec;

void build(int idx, int left, int right) {
    if(left == right) {
        SegmentTree[idx] = vec[left];
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    SegmentTree[idx] = SegmentTree[idx * 2 + 1] ^ SegmentTree[idx * 2 + 2];
}

int query(int idx, int left, int right, int u, int v) {
    if(right < u || v < left) return 0;
    if(u <= left && right <= v) return SegmentTree[idx];
    int mid = (left + right) / 2;
    int q1 = query(idx * 2 + 1, left, mid, u, v);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return q1 ^ q2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt;
  cin >> tt;
  while (tt--) {
    long long xor0 = 0;
    long long xor1 = 0;
    cin >> n; vec.resize(n);
    for(auto &x : vec) cin >> x;
    cin >> s;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') xor0 ^= vec[i];
        else xor1 ^= vec[i];
    }   
    build(0, 0, n - 1);
    cin >> q;
    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int l, r; cin >> l >> r; l--; r--;
            long long tmp = query(0, 0, n - 1, l, r);
            xor0 ^= tmp;
            xor1 ^= tmp;
        } else {
            int g; cin >> g;
            if(g == 0) cout << xor0 << " ";
            else cout << xor1 << " ";
        }
    }
    cout << "\n";
    vec.clear();
    memset(SegmentTree, 0, sizeof(SegmentTree));
  }
  return 0;
}