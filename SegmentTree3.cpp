#include <bits/stdc++.h>

#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define maxn 100005
#define MOD 1000000007
#define ll long long
#define infinity -(MOD + 1)

using namespace std;

ll n, m, A[maxn];

// để hiểu được segement tree thì phải hiểu thông tin mà nó chứa
// và hiểu được cách hợp 2 thông tin lại => done

// https://codeforces.com/gym/458672

struct Node {
    ll max1;
    ll max2;
};

Node SegmentTree[4 * maxn];

ll Multiply_mod(ll a, ll b, ll mod) {
    if (b == 1) return a % mod;
    if (b % 2 == 0) return Multiply_mod((a * 2) % mod, b / 2, mod) % mod;
    else return (Multiply_mod((a * 2) % mod, b / 2, mod) + a) % mod;
}

Node Merge(Node n1, Node n2) {
    vector<ll> v = { n1.max1, n1.max2, n2.max1, n2.max2 };
    sort(v.begin(), v.end(), greater<ll>());
    return Node{ v[0], v[1] };
}

void build(ll idx, ll left, ll right) {
    if (left == right) {
        SegmentTree[idx].max1 = A[left];
        SegmentTree[idx].max2 = infinity;
        return;
    }
    ll mid = (left + right) / 2;
    build(2 * idx + 1, left, mid);
    build(2 * idx + 2, mid + 1, right);
    SegmentTree[idx] = Merge(SegmentTree[2 * idx + 1], SegmentTree[2 * idx + 2]);
}

void update(ll idx, ll left, ll right, ll pos, ll val) {
    if (pos < left || right < pos) {
        return;
    }
    if (left == right) {
        SegmentTree[idx].max1 = val;
        SegmentTree[idx].max2 = infinity;
        return;
    }
    ll mid = (left + right) / 2;
    update(2 * idx + 1, left, mid, pos, val);
    update(2 * idx + 2, mid + 1, right, pos, val);
    SegmentTree[idx] = Merge(SegmentTree[2 * idx + 1], SegmentTree[2 * idx + 2]);
}

Node query(ll idx, ll left, ll right, ll u, ll v) {
    if (right < u || v < left) {
        return Node{ infinity, infinity };
    }
    if (u <= left && right <= v) {
        return SegmentTree[idx];
    }
    ll mid = (left + right) / 2;
    Node leftNode = query(2 * idx + 1, left, mid, u, v);
    Node rightNode = query(2 * idx + 2, mid + 1, right, u, v);
    return Merge(leftNode, rightNode);
}

void solve() {
    ll type; cin >> type;
    if (type == 0) {
        ll x, v; cin >> x >> v;
        update(0, 0, n - 1, x - 1, v);
    }
    else {
        ll l, r, mod;
        cin >> l >> r >> mod;
        Node q = query(0, 0, n - 1, l - 1, r - 1);
        if (l == r) {
            cout << q.max1 % mod << "\n";
        }
        else {
            cout << Multiply_mod(q.max1, q.max2, mod) << "\n";
        }
    }
}

int main() {
    FAST_IO;
    cin >> n;
    for (ll i = 0; i < n; i++) cin >> A[i];
    build(0, 0, n - 1);
    cin >> m;
    while (m--) solve();
    return 0;
}
