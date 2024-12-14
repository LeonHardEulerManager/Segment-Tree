#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define maxn 100006
#define ll long long
#define llint long long int
#define db long double
#define str string
#define fst first
#define snd second

#define sz(x) int((x).size())
#define pb push_back
#define ins insert 
#define eb emplace_back
#define ft front()
#define bk back()

#define FOR(i,a,b) for (int i = (a); i < (b); ++i)
#define F0R(i,a) FOR(i,0,a)
#define ROF(i,a,b) for (int i = (b)-1; i >= (a); --i)
#define R0F(i,a) ROF(i,0,a)
#define rep(a) F0R(,a)
#define each(a,x) for (auto& a: x)
#define __PhungDucMinhSobad__ signed main

template<typename T> void maximize(T& res, const T& val) { if (res < val) res = val; }
template<typename T> void minimize(T& res, const T& val) { if (res > val) res = val; }
using namespace std;

int n, q;
ll A[maxn];
ll SegmentTree[4 * maxn][21]; // Lưu từng bit của số nguyên
ll lazy[4 * maxn];  

// Xây dựng cây phân đoạn, phân tách từng bit
void build(int idx, int left, int right) {
    if (left == right) {
        for (int i = 0; i < 21; ++i) {
            SegmentTree[idx][i] = (A[left] >> i) & 1;  // Lưu từng bit của A[left]
        }
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    for (int i = 0; i < 21; ++i) {
        SegmentTree[idx][i] = SegmentTree[idx * 2 + 1][i] + SegmentTree[idx * 2 + 2][i];
    }
}

// Đẩy giá trị lười xuống các nút con
void pushDown(int idx, int left, int right) {
    if (lazy[idx] == 0) return;

    for (int i = 0; i < 21; ++i) {
        if ((lazy[idx] >> i) & 1) {
            int len = (right - left + 1);
            SegmentTree[idx][i] = len - SegmentTree[idx][i];  // Đảo bit i
        }
    }

    if (left != right) {
        lazy[idx * 2 + 1] ^= lazy[idx];  
        lazy[idx * 2 + 2] ^= lazy[idx];  
    }

    lazy[idx] = 0;  
}

void update(int idx, int left, int right, int u, int v, ll val) {
    pushDown(idx, left, right);
    if (v < left || right < u) return;
    if (u <= left && right <= v) {
        lazy[idx] ^= val;
        pushDown(idx, left, right);
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, u, v, val);
    update(idx * 2 + 2, mid + 1, right, u, v, val);
    for (int i = 0; i < 21; ++i) {
        SegmentTree[idx][i] = SegmentTree[idx * 2 + 1][i] + SegmentTree[idx * 2 + 2][i];
    }
}

ll query(int idx, int left, int right, int u, int v) {
    pushDown(idx, left, right);
    if (v < left || right < u) return 0;
    if (u <= left && right <= v) {
        ll res = 0, add = 1;
        for (int i = 0; i < 21; ++i) {
            res += SegmentTree[idx][i] * add;  // Cộng giá trị từng bit
            add *= 2;
        }
        return res;
    }
    int mid = (left + right) / 2;
    ll q1 = query(idx * 2 + 1, left, mid, u, v);
    ll q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return q1 + q2;
}

void solve() {
    int type;
    cin >> type;
    if (type == 1) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        ll result = query(0, 0, n - 1, l, r);
        cout << result << "\n";
    } else {    
        int l, r, x;
        cin >> l >> r >> x;
        l--; r--;
        update(0, 0, n - 1, l, r, x);
    }
}

__PhungDucMinhSobad__() {
    FAST_IO;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    build(0, 0, n - 1);
    cin >> q;
    while (q--) {
        solve();
    }
    return 0;
}
