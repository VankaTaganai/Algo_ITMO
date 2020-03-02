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
const int maxn = 150 + 7;
const int inf = 1e9 + 7;

int dp[maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x, a, y, b, l;
    cin >> x >> a >> y >> b >> l;

    int L = min(a, b), R = ((x * a) + (y * b) + 1) / l + 1;
    int m, i, j, k, t, mx, was;

    while (L + 1 != R) {
        m = ((L + R) >> 1);

        was = 0;

        for (i = 0; i <= x; ++i) {
            if (was >= l) {
                break;
            }
            for (j = 0; j <= y; ++j) {
                if (was >= l) {
                    break;
                }
                dp[i][j] = 0;
                mx = 0;
                if (i - 1 >= 0) {
                    mx = dp[i - 1][j];
                }
                if (j - 1 >= 0) {
                    mx = max(mx, dp[i][j - 1]);
                }
                for (k = i; k >= 0; --k) {
                    if (was >= l || dp[i][j] == mx + 1) {
                        break;
                    }
                    for (t = j; t >= 0; --t) {
                        if (was >= l || dp[i][j] == mx + 1) {
                            break;
                        }
                        if (k == i && t == j) {
                            continue;
                        }
                        if ((i - k) * a + (j - t) * b >= m) {
                            dp[i][j] = max(dp[k][t] + 1, dp[i][j]);
                            was = max(was, dp[i][j]);
                        }
                    }
                }
            }
        }
        if (was >= l) {
            L = m;
        } else {
            R = m;
        }
    }

    cout << L;

    return 0;
}

