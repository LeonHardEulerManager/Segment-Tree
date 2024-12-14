/*Kỉ niệm là thứ giết chết mọi thứ*/
/*PhungDucMinhSobad*/

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

// Đề bài: https://leetcode.com/problems/count-good-triplets-in-an-array/solutions/1783199/python-balanced-bst-count-smaller-before-and-greater-after/?envType=problem-list-v2&envId=segment-tree
// Ý tưởng: xét từng giá trị, sau đó xét các trường hợp nhỏ/ lớn hơn, sau đó sử dụng
// quy tắc nhân, sau đó là quy tắt cộng để tính result

int n;
vector<int> vec1, vec2, pos2, NhoHon;
int SegmentTree[4 * maxn], result;

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
    int q1 = query(idx * 2 + 1, left, mid ,u, v);
    int q2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return q1 + q2;
}

void solve() {
    cin >> n;
    vec1.resize(n);
    vec2.resize(n);
    pos2.resize(maxn);
    NhoHon.resize(n, 0);

    for(auto &x : vec1) {
        cin >> x;
    }

    for(auto &x : vec2) {
        cin >> x;
    }
    // Truy vấn theo giá trị
    for(int i = 0; i < n; i++) {
        pos2[vec2[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        int pos = pos2[vec1[i]]; 
        // xác định vị trí pos(không cố định như i) =>SegmentTree
        // phải trong khoảng pos mới thỏa mãn, nếu pos ngoài tầm không sao vì được update là 0
        NhoHon[i] = query(0, 0, n - 1, 0, pos - 1); // đếm số phần tử nhỏ hơn
        update(0, 0, n - 1, pos, 1);
    } 

    memset(SegmentTree, 0, sizeof(SegmentTree));
    //Duyệt ngược lại:
    for(int i = n - 1; i >= 0; i--) {
        int pos = pos2[vec1[i]];
        result += NhoHon[i] * query(0, 0, n - 1, pos + 1, n - 1);
        update(0, 0, n - 1, pos, 1);
    }
    cout << result;
}

__PhungDucMinhSobad__()
{
    FAST_IO; 
    solve();   
    return 0;
}
