#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define TIME cerr << "\n" << "TIME: " << clock() << " ms\n"
#define maxn 200005
#define int long long
#define llint long long int
#define db long double
#define str string
#define ff first
#define ss second
#define pb push_back
#define mkp make_pair

#define sz(x) (x).size()
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

vector<tuple<int, int, int>> queries;
vector<int> pos;
int t, n, p, k, SegmentTree[4 * maxn], Lazy[4 * maxn];
unordered_map<int, int> m; 

void push(int idx, int left, int right) {
    if(Lazy[idx] != 0) {
        SegmentTree[idx] += (right - left + 1) * Lazy[idx];
        if(left != right) {
            Lazy[idx * 2 + 1] += Lazy[idx];
            Lazy[idx * 2 + 2] += Lazy[idx];
        }
        Lazy[idx] = 0;
    }
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
    cin >> n >> p >> k;
    for(int i = 0; i < p; i++) {
        int l, r, x; cin >> l >> r >> x; l--; r--; 
        pos.pb(l);
        pos.pb(r + 1);
        queries.pb({l, r, x});
    }
    pos.pb(0);
    pos.pb(n);
    sort(ALL(pos));
    pos.erase(unique(ALL(pos)), pos.end());

    for(int i = 0; i < sz(pos); i++) {
        m[pos[i]] = i;
    }

    for(auto &i : queries) {
        int l = m[get<0>(i)];
        int r = m[get<1>(i) + 1] - 1; 
        int x = get<2>(i);   
        RangeUpdate(0, 0, sz(pos) - 1, l, r, x);
    }

    int cnt = 0;
    for(int i = 0; i + 1 < sz(pos); i++) {
        int val = query(0, 0, sz(pos) - 1, i, i);
        int len = pos[i + 1] - pos[i];
        if(val % k == 0) {
            cnt += len;
        }
    }
    cout << cnt << "\n";
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    int t = 1;
    // cin >> t; 
    while(t--) solve();   
    return 0;
}
