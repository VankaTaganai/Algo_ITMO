#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const ll mod = 999999937;
const int maxn = 1e4 + 7;

bool dp[2][maxn];
bool was[maxn];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    // freopen("number.in", "r", stdin);
    // freopen("number.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string a, b;
    cin >> b >> a;

    a = "$" + a;
    b = "$" + b;
    for (ui i = 1; i < b.size(); i++) {
        if (b[i] != '*') {
            break;
        }
        dp[0][i] = true;
    }
    dp[0][0] = true;
    was[0] = true;
    for (ui i = 1; i < a.size(); i++) {
        for (ui j = 1; j < b.size(); j++) {
            if (b[j] == '?') {
                dp[1][j] = dp[0][j - 1];
            } else if (b[j] == '*') {
                dp[1][j] = was[j - 1];
            } else if (a[i] == b[j]) {
                dp[1][j] = dp[0][j - 1];
            }
            was[j] = was[j] | dp[1][j];
        }
        for (ui j = 0; j <= b.size(); j++) {
            was[j] = was[j] | dp[1][j];
            dp[0][j] = dp[1][j];
            dp[1][j] = false;
        }
    }

    if (dp[0][b.size() - 1]) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}

