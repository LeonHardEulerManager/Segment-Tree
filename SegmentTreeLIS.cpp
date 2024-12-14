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
int t, SegmentTree[4 * maxn], n, dp[maxn]; 
vector<int> vec;
unordered_map<int, int> m;

void update(int idx, int left, int right, int pos, int val) {
    if(pos < left || right < pos) return;
    if(left == right) {
        if(SegmentTree[idx] == 0LL) SegmentTree[idx] = val;
        else maximize(SegmentTree[idx], val);
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos, val);
    update(idx * 2 + 2, mid + 1, right, pos, val);
    SegmentTree[idx] = max(SegmentTree[idx * 2 + 1], SegmentTree[idx * 2 + 2]);
}
 
int query(int idx, int left, int right, int u, int v) {
    if(right < u || v < left) return 0;
    if(u <= left && right <= v) return SegmentTree[idx];
    int mid = (left + right) / 2;
    int q1 = query(idx * 2 + 1, left, mid, u, v);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return max(q1, q2);
}

void solve() {
    cin >> n;
    vec.resize(n);
    for(auto &x : vec) cin >> x;
    vector<int> compress(vec);
    sort(ALL(compress));
    compress.erase(unique(ALL(compress)), compress.end());
    for(int i = 0; i < sz(compress); i++) m[compress[i]] = i;
    //for(auto x : vec) cout << x << " ";
    //cout << endl;
    for(auto &x : vec) x = m[x];
    //for(auto x : vec) cout << x << " ";
    dp[0] = 1;
    update(0, 0, n - 1, vec[0], 1); 
    for(int i = 1; i < n; i++) {
        dp[i] = query(0, 0, n - 1, 0, vec[i] - 1) + 1;
        update(0, 0, n - 1, vec[i], dp[i]);
    }
    cout << *max_element(dp, dp + n);
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    int t = 1;
    //cin >> t;
    while(t--) solve();   
    return 0;
}