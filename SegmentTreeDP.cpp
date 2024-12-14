#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define maxn 100005
#define ll long long
#define llint long long int
#define db long double
#define str string
#define fst first
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

const int K = 11; 
int n, k, A[maxn];
ll SegmentTree[4 * maxn], dp[maxn][K]; 

void update(int idx, int left, int right, int pos, ll val) {
    if (left == right) {
        SegmentTree[idx] += val; 
        return;
    }
    int mid = (left + right) / 2;
    if (pos <= mid) update(2 * idx + 1, left, mid, pos, val);
    else update(2 * idx + 2, mid + 1, right, pos, val);
    SegmentTree[idx] = SegmentTree[2 * idx + 1] + SegmentTree[2 * idx + 2];
}

// Hàm truy vấn tổng giá trị trong đoạn [u, v]
ll query(int idx, int left, int right, int u, int v) {
    if (right < u || v < left) return 0; 
    if (u <= left && right <= v) return SegmentTree[idx]; 
    int mid = (left + right) / 2;
    ll q1 = query(2 * idx + 1, left, mid, u, v);
    ll q2 = query(2 * idx + 2, mid + 1, right, u, v);
    return q1 + q2;
}

ll result = 0; 
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> A[i]; // Đọc mảng A

    // Cơ sở của quy hoạch động: mỗi phần tử tự tạo thành dãy con độ dài 1
    for (int i = 0; i < n; i++) {
        dp[i][1] = 1;   
    }

    // Tính toán các dãy con có độ dài từ 2 đến k+1
    for (int length = 2; length <= k + 1; length++) {
        // Xóa các giá trị cũ trong Segment Tree trước khi xử lý độ dài mới
        memset(SegmentTree, 0, sizeof(SegmentTree));
        for (int i = 0; i < n; i++) {
            // Query để tìm tổng số lượng dãy con có độ dài length - 1 kết thúc tại các phần tử < A[i]
            dp[i][length] = query(0, 0, n - 1, 0, A[i] - 1);
            // Cập nhật giá trị dp[i][length - 1] vào Segment Tree tại vị trí A[i]
            update(0, 0, n - 1, A[i], dp[i][length - 1]);
        }
    }

    for (int i = 0; i < n; i++) {
        result += dp[i][k + 1];
    }
    
    cout << result << "\n";
}

__PhungDucMinhSobad__()
{
    FAST_IO;
    solve();
    return 0;
}