/**
 *    author:  Phung Duc Minh
 *    created: 5.12.2024 16:52:12
**/

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

// Link: https://codeforces.com/contest/1632/problem/D

vector<int> vec;
int IT[4 * 100005], n;

void build(int idx, int left, int right)
{
    if (left == right) {
        IT[idx] = vec[left];
        return;
    } 
    else
    {
        int mid = (left + right) / 2;
        build(idx * 2 + 1, left, mid);
        build(idx * 2 + 2, mid + 1, right);
        IT[idx] = gcd(IT[idx * 2 + 1], IT[idx * 2 + 2]);
    }
}

int query(int idx, int left, int right, int u, int v)
{
    if (right < u || v < left) return 0;
    if (u <= left && right <= v) return IT[idx];
    int mid = (left + right) / 2;
    int t1 = query(2 * idx + 1, left, mid, u, v);
    int t2 = query(2 * idx + 2, mid + 1, right, u, v);
    return gcd(t1, t2);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  //cin >> tt;
  while (tt--) {
    cin >> n;
    vec.resize(n); for(auto &x : vec) cin >> x;
    build(0, 0, n - 1);
    vector<vector<int>> segments(n);
    for(int i = 0; i < n; i++) {
        int lo = i + 1, hi = n - 1, ans = i; // min ans = i
        while(lo <= hi) {
            int mid = (lo + hi) / 2;
            if(query(0, 0, n - 1, i, mid) >= (mid - i + 1)) {
                ans = mid;
                lo = mid + 1;
            } else hi = mid - 1;
        }
        // ans > i - bé nhất là i, có khả năng i = 1s
        if(query(0,0, n - 1, i, ans) == (ans - i + 1)) segments[ans].push_back(i);
    }
    int ans = 0, monopos = -1;
    for(int i = 0; i < n; i++) {
        for(auto x : segments[i]) {
            if(x > monopos) {
                monopos = i;
                ans++;
            }
        }
        cout << ans << " ";
    }
  }
  return 0;
}