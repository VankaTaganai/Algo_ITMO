#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const int mod = 1e9;
const int maxn = 2e3 + 7;
const int inf = 1e9 + 7;

int dp[maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
//    freopen("meetings.in", "r", stdin);
//    freopen("meetings.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < n - i + 1; j++) {
            int l = j;
            int r = j + i - 1;
            dp[l][r] = (dp[l][r - 1] + dp[l + 1][r]) % mod;
            if (v[l] == v[r]) {
                dp[l][r] = (dp[l][r] + 1) % mod;
            } else {
                dp[l][r] = (dp[l][r] - dp[l + 1][r - 1] + mod) % mod;
            }
        }
    }

    cout << dp[0][n - 1];

    return 0;
}

