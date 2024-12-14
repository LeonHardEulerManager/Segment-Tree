#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define ll long long
#define sz(x) int((x).size())

const int maxn = 200005;

using namespace std;

// link video: https://www.youtube.com/watch?v=dRc5ySKB67U

// Bài toán: cho mảng a có n phần tử
// có 2 loại truy vấn sau u, v
// Yêu cầu: tính tổng các phần tử từ a[u] đến a[v] (u <= v)


// Segment tree thường xuất hiện trong các bài toán truy vấn dãy số
// Có thể thực hiện truy vấn [l, r]d
// Segment tree là 1 cây nhị phân đầy đủ
// Mảng A có n phần tử thì cây segment tree thì không quá 4N ô nhớ

// bộ nhớ cần: maxn * 4

int A[maxn];
ll SegmentTree[4 * maxn];
int n, q;

// Cài đặt segment tree
// Độ phức tạp: 
// Phân tích: để xây một nút thì phải xây 2 nút con
// O(n log n)
void build(int idx, int left, int right)
{
	if (left >= right) 
	{
		SegmentTree[idx] = A[left];
		return;
	} 
	else
	{
		int mid = (left + right) / 2;
		build(idx * 2 + 1, left, mid);
		build(idx * 2 + 2, mid + 1, right);
		SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
	}
}

// Thao tác truy vấn, độ phức tạp là O(log n)
// Tư tưởng: lấy cái đoạn mà nằm trong đoạn mà mình cần tính [u, v] (lớn nhất có thể)

// Độ phức tạp: 
// Phân tích: tách u, v thành nhiều đoạn
// Chứng minh được rằng mỗi tầng chỉ có tối đa 2 đoạn nằm trong u, v
// Gỉa sử phản chứng có 3 đoạn cùng tầng => không thể thành 3 đoạn tách nhau được
// (vì phải nằm sát nhau)
// TH2 => nếu 2 nút sát nhau => idx * 2 + 1, idx * 2 + 2

// Độ phức tạp: O(4 * log n)
ll query(int idx, int left, int right, int u, int v)
{
	// Các trường hợp cơ sở
	// Nếu đoạn nằm bên trái hoặc nằm bên phải (không giao)
	if (right < u || v < left) return 0;
	// Nếu nằm hoàn toàn trong đoạn thì trả về luôn
	if (u <= left && right <= v) return SegmentTree[idx];
	// Chắc chắn biết được có 1 đoạn nào đó ở bên trái hoặc
	// bên phải giao với đoạn u, v
	int mid = (left + right) / 2;
	ll t1 = query(2 * idx + 1, left, mid, u, v);
	ll t2 = query(2 * idx + 2, mid + 1, right, u, v);
	return t1 + t2;
}

// hàm update(thao tác cập nhật)
// O(log n)
void update(int idx, int left, int right, int pos, int val)
{
	// Trường hợp cơ sở
	// Trường hợp pos không nằm trong đoạn
	if (pos < left || right < pos) return;
	if (left == right) // == pos
	{
		SegmentTree[idx] = val;
		A[pos] = val;
		return;
	}
	// Trong các trương hợp còn lại
	int mid = (left + right) / 2;
	update(idx * 2 + 1, left, mid, pos, val);
	update(idx * 2 + 2, mid + 1, right, pos, val);
	// Cuối cùng là cập nhật
	SegmentTree[idx] = SegmentTree[2 * idx + 1] + SegmentTree[2 * idx + 2];
}

void solve()
{
	int type; cin >> type;
	if (type == 1)
	{
		int x, v; cin >> x >> v; x--;
		update(0, 0, n - 1, x, v);
	}
	else
	{
		int l, r; cin >> l >> r; l--; r--;
		cout << query(0, 0, n - 1, l, r) << "\n";
	}
}

int main()
{
	FAST_IO;
	cin >> n >> q;
	for (int i = 0; i < n; i++) cin >> A[i];
	build(0, 0, n - 1);
	while (q--) solve();
	return 0;
}