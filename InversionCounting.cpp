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
int t, n; int SegmentTree[4 * maxn]; vector<int> p;


void update(int idx, int left, int right, int pos, int val) {
    if(pos < left || right < pos) return;
    if(left == right) {
        SegmentTree[idx] += val;
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos, val);
    update(idx * 2 + 2, mid + 1, right, pos, val);
    SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

int query(int idx, int left, int right, int u, int v) {
    if(right < u || v < left) return 0;
    if(u <= left && right <= v) return SegmentTree[idx];
    int mid = (left + right) / 2;
    int q1 = query(idx * 2 + 1, left, mid, u, v);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return q1 + q2;
}

void solve() {
    p.clear();
    cin >> n;
    // Nén tọa độ
    vector<int> tmp(n);
    for(int i = 0; i < n; i++) {
        cin >> tmp[i];
    }

    vector<int> b = tmp;
    // nén tọa độ
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    map<int, int> valToIdx;
    for(int i = 0; i < b.size(); i++) {
        valToIdx[b[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        tmp[i] = valToIdx[tmp[i]];
    }

    int maxVal = b.size();

    p.resize(n);
    for(int i = 0; i < n; i++) {
        p[i] = tmp[i];
    }

    memset(SegmentTree, 0, sizeof(SegmentTree));

    int cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += query(0, 0, maxVal - 1, p[i] + 1, maxVal - 1);
        update(0, 0, maxVal - 1, p[i], 1);
    }
    cout << cnt << " ";
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    int t = 1; cin >> t;
    while(t--) solve();   
    return 0;
}
