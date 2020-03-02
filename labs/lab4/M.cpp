#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const int mod = 45;
const int maxn = 20;
const ll infl = 1e18 + 7;

vector<pair<int, ll>> g[maxn];

ll dp[maxn][(1 << maxn)];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("salesman.in", "r", stdin);
    freopen("salesman.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        a--;
        b--;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
    }

    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[j][i] = infl;
        }
    }

    for (int i = 0; i < n; i++) {
        dp[i][(1 << i)] = 0;
    }

    for (int i = 1; i < n; i++) {
        vector<int> tmp;
        for (int j = 0; j < i; j++) {
            tmp.emplace_back(1);
        }
        for (int j = 0; j < n - i; j++) {
            tmp.emplace_back(0);
        }

        reverse(tmp.begin(), tmp.end());

        do {
            int start = 0;
            for (int j : tmp) {
                start = start * 2 + j;
            }

            for (int v = 0; v < n; v++) {
                if (start & (1 << v)) {
                    for (auto to : g[v]) {
                        if ((start & (1 << to.ff)) == 0) {
                            dp[to.ff][start | (1 << to.ff)] = min(dp[to.ff][start | (1 << to.ff)],
                                    dp[v][start] + to.ss);
                        }
                    }
                }
            }
        } while (next_permutation(tmp.begin(), tmp.end()));
    }

    ll ans = infl;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[i][(1 << n) - 1]);
    }

    if (ans == infl) {
        cout << -1;
    } else {
        cout << ans;
    }

    return 0;
}
