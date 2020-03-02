#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const int inf = 1e9 + 7;
const ll mod = 999999937;
const int maxn = 1e5 + 7;

ll dp[maxn][2];

vector<pair<int, ll>> g[maxn];

void dfs(int v, int p = -1) {
    ll sum = 0;
    for (auto to : g[v]) {
        if (to.ff != p) {
            dfs(to.ff, v);
            dp[v][0] += max(dp[to.ff][0], dp[to.ff][1]);
            sum += max(dp[to.ff][0], dp[to.ff][1]);
        }
    }

    for (auto to : g[v]) {
        if (to.ff != p) {
            dp[v][1] = max(dp[v][1], sum - max(dp[to.ff][0], dp[to.ff][1])
            + dp[to.ff][0] + to.ss);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    dfs(1);

    cout << max(dp[1][0], dp[1][1]);

    return 0;
}
