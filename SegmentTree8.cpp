#include <iostream>
#include <string>
#include <array>
#include <vector>

#pragma GCC optimize("Ofast")
#pragma GCC target("sse4")

#define str string    
#define sz(x) int((x).size())
#define FAST_IO cin.tie(0)->sync_with_stdio(0);
#define pb push_back
#define maxn 200005

template<typename T> void maximize(T& res, const T& val) { if (res < val) res = val; }
template<typename T> void minimize(T& res, const T& val) { if (res > val) res = val; }
typedef long long ll;

using namespace std;

// Đề bài: https://codeforces.com/contest/1791/problem/D

struct Node
{
    array<int, 26> freq;
    Node() { freq.fill(0); }
};

Node SegmentTree[4 * maxn];

Node operator+(const Node& left, const Node& right)
{
    Node result;
    for (int i = 0; i < 26; i++)
    {
        result.freq[i] = left.freq[i] + right.freq[i];
    }
    return result;
}

str s;
int n;

void build(int idx, int left, int right)
{
    if (left == right)
    {
        Node result;
        result.freq[s[left] - 'a'] = 1;
        SegmentTree[idx] = result;
        return;
    }
    int mid = (left + right) / 2;
    build(idx * 2 + 1, left, mid);
    build(idx * 2 + 2, mid + 1, right);
    SegmentTree[idx] = SegmentTree[idx * 2 + 1] + SegmentTree[idx * 2 + 2];
}

Node query(int idx, int left, int right, int u, int v)
{
    if (right < u || v < left) return Node();
    if (u <= left && right <= v)
    {
        return SegmentTree[idx];
    }
    int mid = (left + right) >> 1;
    Node n1 = query(idx * 2 + 1, left, mid, u, v);
    Node n2 = query(idx * 2 + 2, mid + 1, right, u, v);
    return n1 + n2;
}

int countDistinct(const Node& node)
{
    int distinctCount = 0;
    for (int i = 0; i < 26; i++)
    {
        if (node.freq[i] > 0) distinctCount++;
    }
    return distinctCount;
}

void solve()
{
    cin >> n >> s;
    int maxfreq = 0;
    build(0, 0, n - 1);
    for (int i = 1; i < n; i++)
    {
        Node n1 = query(0, 0, n - 1, 0, i - 1);
        Node n2 = query(0, 0, n - 1, i, n - 1);
        int distinctSum = countDistinct(n1) + countDistinct(n2);
        maximize(maxfreq, distinctSum);
    }
    cout << maxfreq << endl;
}

int main()
{
    FAST_IO;
    int t; cin >> t;
    while (t--) { solve(); }
    return 0;
}
