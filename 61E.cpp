/**
 *    author:  Phung Duc Minh
 *    created: 12.12.2024 18:38:31
**/

#include <bits/stdc++.h>

#define int long long

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

// Link: https://codeforces.com/problemset/problem/61/E

const int MAXN = 1e6 + 6;

vector<int> vec, compress;
vector<pair<int, int>> cnt;
unordered_map<int, int> m;
int IT[4 * MAXN];
int n, q;

int query(int idx, int left, int right, int u, int v)
{
    if (right < u || v < left) return 0;
    if (u <= left && right <= v) return IT[idx];
    int mid = (left + right) / 2;
    int t1 = query(2 * idx + 1, left, mid, u, v);
    int t2 = query(2 * idx + 2, mid + 1, right, u, v);
    return t1 + t2;
}

void update(int idx, int left, int right, int pos)
{
    if (pos < left || right < pos) return;
    if (left == right) {
        IT[idx]++;
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos);
    update(idx * 2 + 2, mid + 1, right, pos);
    IT[idx] = IT[2 * idx + 1] + IT[2 * idx + 2];
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        cin >> n; vec.resize(n); cnt.resize(n);
        for(auto &x : vec) cin >> x;
        compress = vec;
        sort(compress.begin(), compress.end());
        compress.erase(unique(compress.begin(), compress.end()), compress.end());
        for(int i = 0; i < compress.size(); i++) m[compress[i]] = i;
        for(int i = 0; i < vec.size(); i++) vec[i] = m[vec[i]];
        int sum = 0;
        //for(auto x : vec) cout << x << " ";
        // left
        for(int i = 0; i < n; i++) {
            int left = query(0, 0, vec.size() - 1, vec[i] + 1, compress.size() - 1);
            //int left = query(0, 0, vec.size() - 1, 0, vec[i] - 1);
            //sum += left * right;
            cnt[i].first = left;
            update(0, 0, vec.size() - 1, vec[i]);
            //cout << tmp << " " << i << " " << vec[i] << endl;
            //cout << tmp << endl;
        }   
        memset(IT, 0, sizeof(IT));
        // right
        for(int i = n - 1; i >= 0; i--) {
            int right = query(0, 0, vec.size() - 1, 0, vec[i] - 1);
            //int left = query(0, 0, vec.size() - 1, 0, vec[i] - 1);
            //sum += left * right;
            cnt[i].second = right;
            update(0, 0, vec.size() - 1, vec[i]);
            //cout << tmp << " " << i << " " << vec[i] << endl;
            //cout << tmp << endl;
        }
        //for(auto x : cnt) cout << x.first << " " << x.second << endl;
        for(auto x : cnt) sum += x.first * x.second;
        cout << sum;
    }
    return 0;
}