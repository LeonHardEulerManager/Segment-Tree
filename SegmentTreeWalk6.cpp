#include <bits/stdc++.h> 

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define TIME cerr << "\n" << "TIME: " << clock() << " ms\n"
#define maxn 15000
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
int t, dp[maxn], n, SegmentTree[4 * maxn];
vector<pair<int, int>> vec;

// Đề bài: https://oj.vnoi.info/problem/nkrez
// Ý tưởng: sử dụng Segment Tree walk kết hợp với dp để AC

bool cmp(pair<int, int> p1, pair<int, int> p2) {
    return p1.second < p2.second;
}

void build(int idx, int left, int right) {
    if(left == right) {
        SegmentTree[idx] = vec[left].second;
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    SegmentTree[idx] = min(SegmentTree[idx * 2 + 1], SegmentTree[idx * 2 + 2]);
}

int query(int idx, int left, int right, int val) {
    if (vec[left].second > val) return -1;
    if (vec[right].second <= val) return right;
    int mid = (left + right) / 2;
    if (query(idx * 2 + 2, mid + 1, right, val) != -1) return query(idx * 2 + 2, mid + 1, right, val);
    else return query(idx * 2 + 1, left, mid, val);
}

void solve() {
    cin >> n;
    vec.resize(n);
    for(auto &[x, y] : vec) cin >> x >> y;
    sort(ALL(vec), cmp);
    build(0, 0, n - 1);
    dp[0] = vec[0].second - vec[0].first;
    for(int i = 1; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[query(0, 0, i - 1, vec[i].first)] + vec[i].second - vec[i].first);
    }
    cout << dp[n - 1];
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    int t = 1;
    //cin >> t;
    while(t--) solve();   
    return 0;
}
