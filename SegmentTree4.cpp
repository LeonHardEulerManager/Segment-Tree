#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define maxn 300005
#define ll long long
#define db double
#define pb push_back

using namespace std;

int n, m;
char input[maxn];
struct Node {
    int cnt; // số cặp
    char first, last; // bắt đầu, kết thúc
} SegmentTree[4 * maxn];

// thao tác hợp
// gán cnt
// trong trường hợp giao của last trái và fist phải đều bằng '.' thì
// cnt++(thêm 1 cặp)
Node merge(const Node& left, const Node& right) {
    Node result;
    result.cnt = left.cnt + right.cnt;
    result.first = left.first;
    result.last = right.last;
    if (left.last == '.' && right.first == '.') {
        result.cnt++;
    }
    return result;
}

void build(int idx, int left, int right) {
    if (left == right) {
        SegmentTree[idx].cnt = 0;
        SegmentTree[idx].first = SegmentTree[idx].last = input[left];
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    SegmentTree[idx] = merge(SegmentTree[idx * 2 + 1], SegmentTree[idx * 2 + 2]);
}

void update(int idx, int left, int right, int pos, char val) {
    if (pos < left || pos > right) return;
    if (left == right) {
        SegmentTree[idx].first = SegmentTree[idx].last = val;
        SegmentTree[idx].cnt = 0;
        return;
    }
    int mid = (left + right) / 2;
    update(idx * 2 + 1, left, mid, pos, val);
    update(idx * 2 + 2, mid + 1, right, pos, val);
    SegmentTree[idx] = merge(SegmentTree[idx * 2 + 1], SegmentTree[idx * 2 + 2]);
}

void solve() {
    int pos;
    char val;
    cin >> pos >> val;
    pos--;
    update(0, 0, n - 1, pos, val);
    cout << SegmentTree[0].cnt << "\n";
}

int main() {
    FAST_IO;
    cin >> n >> m;
    cin >> input;
    build(0, 0, n - 1);
    while (m--) {
        solve();
    }
    return 0;
}
