#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const int mod = 45;
const int maxn = 1e3 + 7;

int dp[maxn][maxn * 10];

int w[maxn], c[maxn];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "r", stdin);
#else
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    int ans = -1;
    int x = -1, y = -1;


    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - w[i] >= 0) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - w[i]] + c[i]);
            }
            if (ans < dp[i][j]) {
                ans = dp[i][j];
                x = i;
                y = j;
            }
        }
    }

    vector<int> out;
    while (x > 0 && y > 0) {
        if (dp[x][y] == dp[x - 1][y]) {
            x--;
        } else {
            out.push_back(x);
            y -= w[x--];
        }
    }

    cout << out.size() << "\n";
    for (int i = out.size() - 1; i >= 0; i--) {
        cout << out[i] << " ";
    }
    return 0;
}
