/**
 *    author:  Phung Duc Minh
 *    created: 7.12.2024 15:42:31
**/

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

// Link: https://hnoj.edu.vn/problem/querybracket
// truy vấn dãy ngoặc

int IT[4 * 1000006];
string s;
int q; vector<int> prefix;

void build(int idx, int left, int right)
{
    if (left >= right) {
        IT[idx] = prefix[left];
        return;
    } 
    else
    {
        int mid = (left + right) / 2;
        build(idx * 2 + 1, left, mid);
        build(idx * 2 + 2, mid + 1, right);
        IT[idx] = min(IT[idx * 2 + 1], IT[idx * 2 + 2]);
    }
}

int query(int idx, int left, int right, int u, int v)
{
    if (right < u || v < left) return 1e9;
    if (u <= left && right <= v) return IT[idx];
    int mid = (left + right) / 2;
    int t1 = query(2 * idx + 1, left, mid, u, v);
    int t2 = query(2 * idx + 2, mid + 1, right, u, v);
    return min(t1, t2);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  //cin >> tt;
  while (tt--) {
    cin >> s >> q;
    prefix.resize(s.size());
    for(int i = 0; i < s.size(); i++) {
        if(i > 0) {
            if(s[i] == '(') prefix[i] = prefix[i - 1] + 1;
            else prefix[i] = prefix[i - 1] - 1;
        } else {
            if(s[i] == '(') prefix[i] = 1;
            else prefix[i] = -1;
        }
    }
    //for(auto x : prefix) cout << x << " ";
    //cout << endl;
    build(0, 0, s.size() - 1);
    while(q--) {
        int l, r; cin >> l >> r;
        l--; r--;
        if(l > 0) {
            //cout << query(0, 0, s.size() - 1, l, r) << endl;
            //cout << l << " " << r << endl;
            if(prefix[l - 1] != prefix[r]) cout << "NO" << "\n";
            else if(query(0, 0, s.size() - 1, l, r) >= prefix[l - 1]) cout << "YES" << "\n";
            else cout << "NO" << "\n";
        } else {
            if(prefix[r] != 0) cout << "NO" << "\n";
            else if(query(0, 0, s.size() - 1, 0, r) >= 0) cout << "YES" << "\n";
            else cout << "NO" << "\n";
            //cout << l << "  " << r << " ";
        }
    }
  }
  return 0;
}