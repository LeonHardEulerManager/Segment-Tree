#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define TIME cerr << "\n" << "TIME: " << clock() << " ms\n"
#define maxn 100005
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
int t, n, m; vector<int> vec;
multiset<int> SegmentTree[4 * maxn];
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

void combine(int idx) {
    SegmentTree[idx] = SegmentTree[2*idx + 1];
    for(auto x : SegmentTree[2 * idx + 2]) SegmentTree[idx].insert(x);
}

void build(int idx, int left, int right) {
    if(left == right) {
        SegmentTree[idx].insert(vec[left]);
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    combine(idx);
}

// multiset auto sort
void update(int idx, int left, int right, int pos, int old, int val) {
    if(right < pos || pos < left) return;
    if(left == right) {
        SegmentTree[idx].clear();
        SegmentTree[idx].insert(val);
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos, old, val);
    update(idx * 2 + 2, mid + 1, right, pos, old, val);
    SegmentTree[idx].erase(SegmentTree[idx].find(old)); // specific iterator
    SegmentTree[idx].insert(val); 
}

// min value >= k
int query(int idx, int left, int right, int u, int v, int k) {
    if(right < u || v < left) return 1e18;
    if(u <= left && right <= v) {
        auto it = SegmentTree[idx].lower_bound(k);
        if(it == SegmentTree[idx].end()) return 1e18;
        return *it;
    }
    int mid = (left + right) / 2;
    int q1 = query(idx * 2 + 1, left, mid, u, v, k);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v, k);
    return min(q1, q2);
}

void solve() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int tmp; cin >> tmp;
        vec.pb(tmp);
    }
    build(0, 0, n - 1);

    while(m--) {
        int type;
        cin >> type;
        if(type == 1) {
            int i, v; cin >> i >> v; i--;
            update(0, 0, n - 1, i, vec[i], v);
            vec[i] = v;
        } else {
            int l, r, k; cin >> l >> r >> k; l--; r--;
            int tmp = query(0 ,0, n - 1, l, r, k);
            if(tmp == 1e18) cout << -1 << "\n";
            else cout << query(0, 0, n - 1, l, r, k) << "\n";
        }
    }
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    int t = 1;
    //cin >> t;
    while(t--) solve();   
    return 0;
}
