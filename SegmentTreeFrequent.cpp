#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define maxn 100008
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

str s; int q;

struct Node {
	array<int, 26> frequency {};
} SegmentTree[4 * maxn];

Node operator + (const Node& left, const Node& right) {
	Node result;
	for(int i = 0; i < 26; i++) {
		result.frequency[i] = left.frequency[i] + right.frequency[i];
	}
	return result;
}

void build(int idx, int left, int right) {
	if(left == right) {
		Node result;
		result.frequency[s[left] - 'a'] = 1;
		SegmentTree[idx] = result;
		return;
	}
	int mid = (left + right) / 2;
	build(idx * 2 + 1, left, mid);
	build(idx * 2 + 2, mid + 1, right);
	SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

void update(int idx, int left, int right, int pos, char c) {
	if(left == right) {
		Node result;
		result.frequency[c - 'a']++;
		SegmentTree[idx] = result;
		return;
	}
	int mid = (left + right) / 2;
	if(pos <= mid) update(idx * 2 + 1, left, mid, pos, c);
	else update(idx * 2 + 2, mid + 1, right, pos, c);
	SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

Node query(int idx, int left, int right, int u, int v) {
	if(right < u || v < left) return Node();
	if(u <= left && right <= v) {
		return SegmentTree[idx];
	}
	int mid = (left + right) / 2;
	Node n1 = query(idx * 2 + 1, left, mid, u, v);
	Node n2 = query(idx * 2 + 2, mid + 1, right, u, v);
	return n1 + n2;
}

void solve() {
	int type; cin >> type;
	if(type == 1) {
		int pos; char c; cin >> pos >> c; pos--;
		update(0, 0, sz(s) - 1, pos, c);
	} else {
		int l, r; cin >> l >> r; l--; r--;
		Node result = query(0, 0, sz(s) - 1, l, r);
		int cnt = 0;
		for(int i = 0; i < 26; i++) {
			if(result.frequency[i] != 0) cnt++;
		}	
		cout << cnt << "\n";
	}
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    cin >> s >> q;
    build(0, 0, sz(s) - 1);
    while(q--) {
    	solve();
    }
    return 0;
}