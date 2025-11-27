#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

const int INF = 1e9 + 7;
const int MAXN = 1e5 + 7;

int n, q;
int a[MAXN];
int st[4 * MAXN]; // Segment tree array (4x size for safety)

// Build segment tree
void build(int id, int l, int r) {
    if (l == r) {
        st[id] = a[l];
        return;
    }

    int mid = l + r >> 1;
    build(2 * id, l, mid);
    build(2 * id + 1, mid + 1, r);
    st[id] = min(st[2 * id], st[2 * id + 1]);
}

// Update element at position i
void update(int id, int l, int r, int i, int val) {
    if (l > i || r < i) return;

    if (l == r) {
        st[id] = val;
        return;
    }

    int mid = l + r >> 1;
    update(2 * id, l, mid, i, val);
    update(2 * id + 1, mid + 1, r, i, val);
    st[id] = min(st[2 * id], st[2 * id + 1]);
}


// Query minimum in range [u, v]
int get(int id, int l, int r, int u, int v) {
    if (l > v || r < u) return INF;

    if (l >= u && r <= v) return st[id];

    int mid = l + r >> 1;
    int get1 = get(2 * id, l, mid, u, v);
    int get2 = get(2 * id + 1, mid + 1, r, u, v);

    return min(get1, get2);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n);

    cin >> q;
    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) update(1, 1, n, x, y); // Set arr[x] = y
        else cout << get(1, 1, n, x, y) << '\n'; // Query min in range [x, y]
    }
}