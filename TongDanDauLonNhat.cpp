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

// Link: https://codeforces.com/contest/1420/problem/C2

const long long INF = 1e9 + 69;
const int MAXN = 3e5 + 69;

int n, q; vector<long long> vec;

struct Node {
    long long dp[2][2];
    Node() {} // construct
    Node(long long x) {
        dp[0][0] = -x;
        dp[1][1] = x;
        dp[0][1] = dp[1][0] = -INF;
    }
} IT[4 * MAXN];

Node operator+(const Node& left, const Node& right) {
    Node result;
    // trang thai ban dau
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            result.dp[i][j] = max(left.dp[i][j], right.dp[i][j]);
        }
    }
    // dp
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int x = 0; x < 2; x++) {
                for(int y = 0; y < 2; y++) {
                    if(j != x) {
                        result.dp[i][y] = max(result.dp[i][y], left.dp[i][j]
                            + right.dp[x][y]);
                    }
                }
            }
        }
    }
    return result;
}

void Reset() {
    for (int i = 0; i < 4 * MAXN; i++) IT[i] = Node();
}

void build(int idx, int left, int right) {
    if(left == right) {
        IT[idx] = Node(vec[left]);
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right); 
    IT[idx] = IT[idx * 2 + 1] + IT[idx * 2 + 2];
}

void update(int idx, int left, int right, int pos, int val) {
    if(right < pos || pos < left) return;
    if(left == right) {
        IT[idx] = Node(val);
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos, val);
    update(idx * 2 + 2, mid + 1, right, pos, val);
    IT[idx] = IT[idx * 2 + 1] + IT[idx * 2 + 2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    cin >> tt;
    while (tt--) {
        cin >> n >> q; vec.resize(n);
        for(auto &x : vec) cin >> x;
        build(0, 0, n - 1);
        cout << IT[0].dp[1][1] << "\n";
        while(q--) {
            int l, r; cin >> l >> r; l--; r--;
            int v1 = vec[l], v2 = vec[r];
            swap(vec[l], vec[r]);
            update(0, 0, n - 1, l, v2);
            update(0, 0, n - 1, r, v1);
            cout << IT[0].dp[1][1] << "\n";
        } 
    }
    return 0;
}