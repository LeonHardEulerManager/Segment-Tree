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
#define maxn 300000
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

// Đề bài: https://cses.fi/problemset/task/1619/
// Dùng nén tọa độ kết hợp chặt nhị phân để giải

struct Node { 
    int value;
    int maxVal;
    Node() : value(0), maxVal(0) {}
} SegmentTree[4 * maxn];

int Lazy[4 * maxn], t;
vector<int> positions;
vector<pair<int, int>> updates;

int n;  

Node operator+ (const Node& left, const Node& right) {
    Node result;
    result.value = left.value + right.value;
    result.maxVal = max(left.maxVal, right.maxVal);
    return result;
}

void push(int idx, int left, int right) {
    if(!Lazy[idx]) return;
    SegmentTree[idx].value += (right - left + 1) * Lazy[idx];
    SegmentTree[idx].maxVal += Lazy[idx];
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

void solve() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b; a--; b--;
        positions.pb(a);
        positions.pb(b);
        updates.pb({a, b});
    }
    sort(ALL(positions));
    positions.erase(unique(ALL(positions)), positions.end());
    int m = sz(positions);
    for(auto x : updates) {
        int left = x.first;
        int right = x.second;
        int compressValuel = lower_bound(ALL(positions), left) - positions.begin();
        int compressValuer = lower_bound(ALL(positions), right) - positions.begin();
        RangeUpdate(0, 0, m - 1, compressValuel, compressValuer, 1);
    }

    cout << SegmentTree[0].maxVal;
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    int t = 1;
    //cin >> t;
    while(t--) solve();   
    return 0;
}