#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define maxn 1000006
#define pb push_back
#define ll long long
#define str string
#define sz(x) int((x).size())

using namespace std;
/*Đề bài: Cho một dãy ngoặc có độ dài N
* Cho m truy vấn có dạng l, r
* Yêu cầu bài toán: với mỗi truy vấn, tìm một
* chuỗi con, không cần liên tiếp của chuỗi
* từ l, r, tạo thành dãy ngoặc đúng
*/

struct Node
{
	int optimal; // kết quả tốt nhất mà đoạn l, r có thể đạt được 
	int open; // Số dấu "(" chưa ghép cặp
	int close; // Số dấu ")" chưa ghép cặp
};

Node SegmentTree[maxn * 4]; str A;
// Hàm merge 2 node lại
Node operator + (const Node& left, const Node& right)
{
	Node result;
	// min số dấu "(" thừa ra ở cây con trái và số dấu ")" thừa ra ở cây con phải
	int tmp = min(left.open, right.close);
	// Để xây dựng kết quả tối ưu ở nút id, ta nối dãy ngoặc tối ưu ở 2 con, rồi thêm
	// min(số "(" thừa ra ở con trái, số ")" thừa ra ở con phải)
	// optimal là độ dài(không phải số cặp) nên phải cộng với tmp * 2
	result.optimal = left.optimal + right.optimal + tmp * 2;

	// cộng vào rồi trừ đi số "(" bị mất
	// cộng xong phải trừ đi
	result.open = left.open + right.open - tmp;

	// cộng vào rồi trừ đi số ")" bị mất
	// cộng xong phải trừ đi
	result.close = left.close + right.close - tmp;
	return result;
}

void build(int idx, int left, int right)
{
	if (left == right)
	{
		Node n;
		n.optimal = 0;
		if (A[left] == '(')
		{
			n.open = 1;
			n.close = 0;
		}
		else
		{
			n.open = 0;
			n.close = 1;
		}
		SegmentTree[idx] = n;
		return;
	}
	int mid = (left + right) / 2;
	build(idx * 2 + 1, left, mid);
	build(idx * 2 + 2, mid + 1, right);
	SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

Node query(int idx, int left, int right, int u, int v)
{
	if (right < u || v < left)
	{
		Node n; n.open = n.optimal = n.close = 0;
		return n;
	}
	if (right <= v && u <= left)
	{
		return SegmentTree[idx];
	}
	int mid = (left + right) / 2;
	return query(idx * 2 + 1, left, mid, u, v) + query(idx * 2 + 2, mid + 1, right, u, v);
}

void solve()
{
	cin >> A;
	int q; cin >> q;
	build(0, 0, sz(A) - 1);
	while (q--)
	{
		int l, r; cin >> l >> r;
		cout << query(0, 0, sz(A) - 1, l - 1, r - 1).optimal << "\n";
	}
}

int main()
{
	FAST_IO;
	solve();
	return 0;
}
