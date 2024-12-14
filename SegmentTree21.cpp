#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define TIME cerr << "\n" << "TIME: " << clock() << " ms\n"
#define maxn 400005
#define int long long
#define llint long long int
#define db long double
#define str string
#define ff first
#define ss second
#define pb push_back
#define mkp make_pair

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
#define ALL(v) (v).begin(), (v).end()

#define yep cout<<"YES\n"
#define nope cout<<"NO\n"

#define MASK(i) (1LL << (i))
#define BIT(x, i) (((x) >> (i)) & 1)
#define div   ___div
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
#define __PhungDucMinhSobad__ signed main

template<typename T> void maximize(T& res, const T& val) { 
    if (res < val) res = val; 
}
template<typename T> void minimize(T& res, const T& val) { 
    if (res > val) res = val; 
}

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif
using namespace std;
int t;
int power(int a, int b, int m) {
    int res = 1;
    a %= m;

    while(b > 0) {
        if(b % 2) {
            res = (res * a) % m;
        }
        b /= 2;
        a = (a * a) % m;
    }
    return res;
}

int mod_inverse(int a, int m) {
    return power(a, m - 2, m);
}

// sharing: kĩ thuật nén tọa độ Segment Tree
vector<int> positions;
vector<tuple<int, int, int>> updates;
vector<pair<int, int>> queries;
int SegmentTree[4 * maxn], n, q, Lazy[4 * maxn];

void push(int idx, int left, int right) {
    if(Lazy[idx] == 0) return;
    // hàm push được modify để tính được khoảng cách
    // O(1)
    int length = positions[right + 1] - positions[left];
    SegmentTree[idx] += length * Lazy[idx]; 
    if(left != right) {
        Lazy[idx * 2 + 1] += Lazy[idx];
        Lazy[idx * 2 + 2] += Lazy[idx];
    }
    Lazy[idx] = 0;
}

void RangeUpdate(int idx, int left, int right, int u, int v, int val) {
    push(idx, left, right);
    if(right < u || v < left) return;
    if(u <= left && right <= v) {
        Lazy[idx] += val;
        push(idx, left, right);
        return;
    }
    int mid = (left + right) / 2;
    RangeUpdate(idx * 2 + 1, left, mid, u, v, val);
    RangeUpdate(idx * 2 + 2, mid + 1, right, u, v, val);
    SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

int query(int idx, int left, int right, int u, int v) {
    push(idx, left, right);
    if(right < u || v < left) return 0;
    if(u <= left && right <= v) return SegmentTree[idx];
    int mid = (left + right) / 2;
    int q1 = query(idx * 2 + 1, left, mid, u, v);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return q1 + q2;
}

void solve() {
    cin >> n >> q;

    // Cho tất c ả các tọa độ: update, query vào mảng
    for(int i = 0; i < n; i++) {
        int l, r, v; cin >> l >> r >> v;
        updates.pb({l, r, v});
        positions.pb(l);
        positions.pb(r);
    }
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries.pb({l, r});
        positions.pb(l);
        positions.pb(r);
    }
    sort(ALL(positions));
    positions.erase(unique(ALL(positions)), positions.end());
    for(auto x : positions) cout << x << " ";
    cout << endl;
    int m = positions.size();
    for(auto& x : updates) {
        // lấy ra các truy vấn
        int l = get<0>(x);
        int r = get<1>(x);
        int v = get<2>(x);
        int lidx = lower_bound(ALL(positions), l) - positions.begin();
        int ridx = lower_bound(ALL(positions), r) - positions.begin();
        cout << l << " " << r << " " << v << " " << lidx << " " << ridx << endl;
        RangeUpdate(0, 0, m - 2, lidx, ridx - 1, v);
    }
    for(auto& x : queries) {
        int l = x.first;
        int r = x.second;
        int lidx = lower_bound(ALL(positions), l) - positions.begin();
        int ridx = lower_bound(ALL(positions), r) - positions.begin();
        cout << query(0, 0, m - 2, lidx, ridx - 1) << " " << lidx << " " << ridx << "\n";
    }
    // for(int i = 0; i < 17; i++) {
    //     cout << SegmentTree[i] << " ";
    // }
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    int t = 1;
    //cin >> t;
    while(t--) solve();
    TIME;   
    return 0;
}
