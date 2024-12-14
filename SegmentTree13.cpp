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

// Đề bài CSES: https://cses.fi/problemset/task/1188

str s; int q;
// prefix phải bắt đầu từ kí tự const
// prefix chỉ được phép bắt đầu từ 1 kí tự const
// sufix cũng vậy, từ đó ta có công thức
// length: độ dài của nút trong segment tree
struct Node {
    int prefix;
    int suffix;
    int largest;
    int length;
    Node() : prefix(0), suffix(0), largest(0) {}
} SegmentTree0[4 * maxn], SegmentTree1[4 * maxn];

Node operator+(const Node& left, const Node& right) {
    Node result;
    if(left.prefix == left.length) result.prefix = left.length + right.prefix;
    else result.prefix = left.prefix;
    if(right.suffix == right.length) result.suffix = right.length + left.suffix;
    else result.suffix = right.suffix;
    // left.sufix + right.prefix(trong trường hợp đoạn con merge cùng số(thông nhau))
    result.largest = max({left.largest, right.largest, left.suffix + right.prefix});
    result.length = left.length + right.length;
    return result;
}

void build(int idx, int left, int right) {
    if(left == right) {
        Node result0, result1;
        result0.length = result1.length = 1;
        if(s[left] == '0') {
            result0.prefix = 1;
            result0.suffix = 1;
            result0.largest = 1;
        } else {
            result1.prefix = 1;
            result1.suffix = 1;
            result1.largest = 1;
        }
        SegmentTree0[idx] = result0;
        SegmentTree1[idx] = result1;
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    SegmentTree0[idx] = SegmentTree0[idx * 2 + 1] + SegmentTree0[idx * 2 + 2];
    SegmentTree1[idx] = SegmentTree1[idx * 2 + 1] + SegmentTree1[idx * 2 + 2];
}

void update(int idx, int left, int right, int pos) {
    if(pos < left || right < pos) return;
    if(left == right) {
        Node result0, result1;
        SegmentTree0[idx].prefix ^= 1;    
        SegmentTree0[idx].suffix ^= 1;
        SegmentTree0[idx].largest ^= 1;
        SegmentTree1[idx].prefix ^= 1;
        SegmentTree1[idx].suffix ^= 1;
        SegmentTree1[idx].largest ^= 1;
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos);
    update(idx * 2 + 2, mid + 1, right, pos);
    SegmentTree0[idx] = SegmentTree0[idx * 2 + 1] + SegmentTree0[idx * 2 + 2];
    SegmentTree1[idx] = SegmentTree1[idx * 2 + 1] + SegmentTree1[idx * 2 + 2];
}

void solve() {
    cin >> s >> q;
    build(0, 0, sz(s) - 1);
    while(q--) {
        int pos; cin >> pos; pos--;
        update(0, 0, sz(s) -1, pos);
        cout << max(SegmentTree0[0].largest, SegmentTree1[0].largest) << " ";
    }
}

__PhungDucMinhSobad__()
{
    FAST_IO;   
    solve(); 
    return 0;
}