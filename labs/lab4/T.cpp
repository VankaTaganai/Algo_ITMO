#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const ll mod = 999999937;
const int maxn = 3e5 + 7;
const int inf = 1e9 + 7;

ll sz[maxn];
ll pathD[maxn];

int n;
vector<pair<int, int>> g[maxn];

void dfs(int v, int p = -1) {
    for (auto to : g[v]) {
        if (to.ff != p) {
            dfs(to.ff, v);
            sz[v] += sz[to.ff];
            pathD[v] += pathD[to.ff] + sz[to.ff];
        }
    }
    sz[v]++;
}

ll ans[maxn];

void get_ans(int v, ll up = 0, int p = -1) {
    for (auto to : g[v]) {
        if (to.ff != p) {
            ll del = up + pathD[v] - pathD[to.ff] - sz[to.ff];
            ans[to.ss] = sz[to.ff] * del + pathD[to.ff] * (n - sz[to.ff]) + sz[to.ff] * (n - sz[to.ff]);
            get_ans(to.ff, up + pathD[v] + (n - sz[to.ff]) - pathD[to.ff] - sz[to.ff], v);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("treedp.in", "r", stdin);
    freopen("treedp.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }

    dfs(1);
    get_ans(1);

    for (int i = 0; i < n - 1; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}

