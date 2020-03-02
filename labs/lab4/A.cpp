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
const int maxn = 400 + 7;

int dp[maxn][maxn];
int p[maxn][maxn];

void get_ans(int l, int r) {
    if (l == r) {
        cout << "A";
        return;
    }
    cout << "(";
    get_ans(l, p[l][r]);
    get_ans(p[l][r] + 1, r);
    cout << ")";
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<pair<int, int>> v(n);

    for (int i = 0; i < n; i++) {
        cin >> v[i].ff >> v[i].ss;
    }

    for (int i = 2; i <= n; i++) {
        for (int from = 0; from < n; from++) {
            int to = from + i - 1;
            if (to >= n) {
                break;
            }
            dp[from][to] = dp[from][from] + dp[from + 1][to]
                    + v[from].ff * v[from].ss * v[to].ss;
            p[from][to] = from;
            for (int k = from + 1; k < to; k++) {
                int res = dp[from][k] + dp[k + 1][to]
                        + v[from].ff * v[k].ss * v[to].ss;
                if (dp[from][to] > res) {
                    dp[from][to] = res;
                    p[from][to] = k;
                }
            }
        }
    }

    // cout << dp[0][n - 1] << "\n";
    get_ans(0, n - 1);


    return 0;
}
