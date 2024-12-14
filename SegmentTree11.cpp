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

/* Đề bài: https://cses.fi/problemset/result/10791282/
n tòa nhà trên 1 con phố
Nhập vào giá pizza
Gía để đặt từ tòa nhà a đến b là:
pa + |a - b|

1. Thay đổi giá pizza
2. Từ tòa nhà k và muốn đặt pizza -> giá thấp nhất

Cách giải:
xét các tòa bé hơn a và các tòa lớn hơn a với mọi truy vấn loại 2
nếu tòa nhà bé hơn a - left=> b giá để đặt là
pb + a - b
Với a là hang số => ta cần tối u pb - b
Sau đó phải + lại a
Tương tự, xét các tòa nhà lớn hơn a - right với mọi truy vấn loại 2
pb - a + b => tối ưu pb + b sau đó trừ đi a
cuối cùng lấy min 
query từ 0 -> a - 1 sau đó lấy. left, sau đó + a
tương tự
*/

const int INF = 1e9 + 1;
int n, q, A[maxn];

struct Node {
    int first;
    int second;
} SegmentTree[4 * maxn];

Node operator+(const Node& left, const Node& right) {
    Node result;
    result.first = min(left.first, right.first);
    result.second = min(left.second, right.second);
    return result;
}

void build(int idx, int left, int right) {
    if(left == right) {
        Node result;
        result.first = A[left] - left;
        result.second = A[left] + left;
        SegmentTree[idx] = result;
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

void update(int idx, int left, int right, int pos, int val) {
    if(right < pos || pos < left) return;
    if(left == right) {
        Node result;
        result.first = val - left;
        result.second = val + left;
        SegmentTree[idx] = result;
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos, val);
    update(idx * 2 + 2, mid + 1, right, pos, val);
    SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

Node query(int idx, int left, int right, int u, int v) {
    if(right < u || v < left) return {INF, INF};
    if(u <= left && right <= v) return SegmentTree[idx];
    int mid = (left + right) / 2;
    Node q1 = query(idx * 2 + 1, left, mid, u, v);
    Node q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return {min(q1.first, q2.first), min(q1.second, q2.second)};
}

void solve() {
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }
    build(0, 0, n - 1);
    while(q--) {
        int type; cin >> type;
        if(type == 1) {
            int k, x; cin >> k >> x; k--;
            update(0, 0, n - 1, k, x);
        } else {
            int k; cin >> k; k--;
            cout << min(query(0, 0, n - 1, 0, k).first + k, query(0, 0, n - 1, k + 1, n - 1).second - k) << "\n";
        }
    }
}

__PhungDucMinhSobad__()
{
    FAST_IO;    
    solve();
    return 0;
}