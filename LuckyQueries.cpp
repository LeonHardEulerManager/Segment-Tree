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

const int MAXN = 1e6 + 6;
const int INF = 1e9 + 69;

int n, m, lazy[4 * MAXN];
string s;
vector<int> vec;

// Link: https://codeforces.com/problemset/problem/145/E

// 00, 01, 10, 11
struct Node {
    int dp[2][2];
    Node() {}
    Node(int x) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 2; j++) {
                dp[i][j] = 0;
            }
        }
        dp[x][x] = 1; 
    }
} IT[4 * MAXN];

Node operator+(const Node& left, const Node& right) {
    Node result;
    result.dp[0][0] = left.dp[0][0] + right.dp[0][0];
    result.dp[0][1] = max({left.dp[0][0]+ right.dp[0][1]
        , left.dp[0][0] + right.dp[1][1],   
        left.dp[0][1] + right.dp[1][1]});
    result.dp[1][0] = max({left.dp[1][0] + right.dp[0][0], 
        left.dp[1][1] + right.dp[1][0], left.dp[1][1] + right.dp[0][0]});
    result.dp[1][1] = left.dp[1][1] + right.dp[1][1];
    return result;
}

void push(int idx, int left, int right) {
    if(lazy[idx]) {
        lazy[idx * 2 + 1] ^= 1;
        lazy[idx * 2 + 2] ^= 1;
        swap(IT[idx * 2 + 1].dp[0][0], IT[idx * 2 + 1].dp[1][1]);
        swap(IT[idx * 2 + 1].dp[0][1], IT[idx * 2 + 1].dp[1][0]);
        swap(IT[idx * 2 + 2].dp[0][0], IT[idx * 2 + 2].dp[1][1]);
        swap(IT[idx * 2 + 2].dp[0][1], IT[idx * 2 + 2].dp[1][0]);
        lazy[idx] = 0;
    }
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

void update(int idx, int left, int right, int u, int v) {
    //push(idx, left, right);
    if(right < u ||v < left) return;
    if(u <= left && right <= v) {
        lazy[idx] ^= 1;
        swap(IT[idx].dp[0][0], IT[idx].dp[1][1]);
        swap(IT[idx].dp[0][1], IT[idx].dp[1][0]);
        return;
    }
    push(idx, left, right);
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, u, v);
    update(idx * 2 + 2, mid + 1, right, u, v);
    IT[idx] = IT[idx * 2 + 1] + IT[idx * 2 + 2];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        cin >> n >> m; vec.resize(n);
        cin >> s;
        for(int i = 0; i < n; i++) {
            if(s[i] == '7') vec[i] = 1;
        }
        build(0, 0, n - 1);
        /*for(int k = 0; k < 15; k++) {
            for(int i = 0; i < 2; i++) {
                for(int j = 0; j < 2; j++) {
                    cout << IT[k].dp[i][j] << " ";
                }
            }
            cout << endl;
        }*/
        while(m--) {
            string type; cin >> type;
            if(type == "switch") {
                int l, r; cin >> l >> r; l--; r--;
                update(0, 0, n - 1, l, r);
            } else cout << max({IT[0].dp[0][0], IT[0].dp[0][1], IT[0].dp[1][1]}) << "\n";
        }
    }   
    return 0;
}