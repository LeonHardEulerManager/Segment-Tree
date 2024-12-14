/**
 *    author:  tourist
 *    created: 27.11.2024 14:06:09
**/

#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

const int BIT = 30;

int A[100005], IT[4 * 100005], l[100005], r[100005], prefix[100005], q[100005];

void build(int idx, int left, int right)
{
    if (left == right) {
        IT[idx] = A[left];
        return;
    } 
    else {
        int mid = (left + right) / 2;
        build(idx * 2 + 1, left, mid);
        build(idx * 2 + 2, mid + 1, right);
        IT[idx] = IT[idx * 2 + 1] & IT[idx * 2 + 2];
    }
}

int query(int idx, int left, int right, int u, int v)
{
    if (right < u || v < left) return ((1 << BIT) - 1);
    if (u <= left && right <= v) return IT[idx];
    int mid = (left + right) / 2;
    int t1 = query(2 * idx + 1, left, mid, u, v);
    int t2 = query(2 * idx + 2, mid + 1, right, u, v);
    return t1 & t2;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  //cin >> tt;
  while (tt--) {
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
      cin >> l[i] >> r[i] >> q[i];
      l[i]--; r[i]--;
    }
    for(int bit = 0; bit < BIT; bit++) {
      //diff array
      memset(prefix, 0, sizeof(prefix));
      for(int i = 0; i < m; i++) {
        if((q[i] >> bit) & 1) {
          prefix[l[i]]++;
          prefix[r[i] + 1]--;
        }
      }
      for(int i = 0; i < n; i++) {
        if(i > 0) prefix[i] = prefix[i] + prefix[i - 1];
        if(prefix[i] > 0) A[i] |= (1 << bit);
        //cout << prefix[i] << " ";
      }
    }
    build(0, 0, n - 1);
    for(int i = 0; i < m; i++) {
      if(query(0, 0, n - 1, l[i], r[i]) != q[i]) {
        cout << "NO"; return 0;
        //cout << query(0, 0, n - 1, l[i], r[i]) << " " << q[i] << endl;
      }
    }
    cout << "YES" << "\n";
    for(int i = 0; i < n; i++) {
      cout << A[i] << " ";
    }
    // for(int i = 0; i < 40; i++) {
    //   cout << IT[i] << endl;
    // }
  }
  return 0;
}