#include <bits/stdc++.h>

#define first ff
#define second ss

typedef long long ll;

using namespace std;

const int maxn = 1e5 + 7;
const ll p = 1e6 + 3;

ll delt[maxn];
ll was[maxn];
ll parent[maxn];
ll sz[maxn];
ll zerg = 0;

ll find(ll v) {
    if (parent[v] == v) {
        return v;
    }
    return find(parent[v]);
}

void merge(ll a, ll b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        zerg = (13 * zerg + 11) % p;
        if (sz[a] < sz[b]) {
            swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
        delt[b] -= delt[a];
    }
}

void send_massage(ll a) {
    a = find(a);
    delt[a]++;
}

ll get_ans(ll a) {
    ll prev = a;
    ll sum = delt[a];
    while (parent[a] != a) {
        a = parent[a];
        sum += delt[a];
    }
    ll ans = sum - was[prev];
    was[prev] = sum;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    while (m--) {
        int type;
        cin >> type;
        if (type == 1) {
            ll i;
            cin >> i;
            ll v = (i + zerg) % n;
            send_massage(v);
            zerg = (30 * zerg + 239) % p;
        } else if (type == 2) {
            ll i, j;
            cin >> i >> j;
            ll a = (i + zerg) % n;
            ll b = (j + zerg) % n;
            merge(a, b);
        } else {
            ll i;
            cin >> i;
            ll v = (i + zerg) % n;
            ll ans = get_ans(v);
            cout << ans << "\n";
            zerg = (100500 * zerg + ans) % p;
        }
    }

    return 0;
}
