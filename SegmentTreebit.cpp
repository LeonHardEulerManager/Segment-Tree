#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define maxn 17
#define ll long long
#define llint long long int
#define db long double
#define str string
#define fst frist
#define snd second

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
#define __PhungDucMinhSobad__ signed main

template<typename T> void maximize(T& res, const T& val) { if (res < val) res = val; }
template<typename T> void minimize(T& res, const T& val) { if (res > val) res = val; }
using namespace std;

// Đề bài: https://codeforces.com/problemset/problem/339/D
// Ý tưởng của bài này:
// Xây dựng cây segment tree dựa trên KHOẢNG CÁCH ĐẾN NÚT LÁ
// sử dụng kĩ thuật if, else để làm giảm thời gian chạy, tăng độ chính xác cho 
// Segment Tree

int A[1 << maxn], n, m;

struct Node {
	int value;
	int LengthToLeaf;
} SegmentTree[(1 << (maxn + 1)) - 1];

Node operator +(const Node& left, const Node& right) {
	Node result;
	result.LengthToLeaf = left.LengthToLeaf + 1;
	if(result.LengthToLeaf % 2) result.value = left.value | right.value;
	else result.value = left.value ^ right.value;
	return result;
}

void build(int idx, int left, int right) {
	if(left == right) {
		Node result;
		result.LengthToLeaf = 0;
		result.value = A[left];
		SegmentTree[idx] = result;
		return;
	}

	int mid = (left + right) / 2;
	build(idx * 2 + 1, left, mid);
	build(idx * 2 + 2, mid + 1, right);
	SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

void update(int idx, int left ,int right, int pos, int val) {
	if(left == right) {
		SegmentTree[idx].value = val;
		return;
	}

	// Tối ưu độ phức tạp, làm giảm độ sai
	int mid = (left + right) / 2;
	if(pos<= mid) update(idx * 2 + 1, left, mid, pos, val);
	else update(idx * 2 + 2, mid + 1, right, pos, val);
	SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

void Input() {
	cin >> n >> m;
	for(int i = 0; i < (1 << n); i++) {
		cin >> A[i];
	}
}

void solve()
{
	Input();
	build(0, 0, (1 << n) - 1);
	while(m--) {
		int p, b; cin >> p >> b; p--;
		update(0, 0, (1 << n) - 1, p, b);
		cout << SegmentTree[0].value << "\n";
	}
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    solve();
    return 0;
}