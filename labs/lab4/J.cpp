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
const int maxn = 1e4 + 7;

string a, b;

int dp[2][maxn];
int revdp[2][maxn];

void get_dp(int fl, int fr, int sl, int sr) {
    for (int i = sl; i <= sr; i++) {
        dp[0][i] = dp[1][i] = 0;
    }
    for (int i = fl; i <= fr; i++) {
        for (int j = sl; j <= sr; j++) {
            if (a[i] == b[j]) {
                if (j == sl) {
                    dp[1][j] = 1;
                } else {
                    dp[1][j] = dp[0][j - 1] + 1;
                }
            } else {
                if (j == sl) {
                    dp[1][j] = dp[0][j];
                } else {
                    dp[1][j] = max(dp[0][j], dp[1][j - 1]);
                }
            }
        }
        for (int j = sl; j <= sr; j++) {
            dp[0][j] = dp[1][j];
            dp[1][j] = 0;
        }
    }
}

void revget_dp(int fl, int fr, int sl, int sr) {
    for (int i = sl; i <= sr; i++) {
        revdp[0][i] = revdp[1][i] = 0;
    }
    for (int i = fr; i >= fl; i--) {
        for (int j = sr; j >= sl; j--) {
            if (a[i] == b[j]) {
                if (j == sr) {
                    revdp[1][j] = 1;
                } else {
                    revdp[1][j] = revdp[0][j + 1] + 1;
                }
            } else {
                if (j == sr) {
                    revdp[1][j] = revdp[0][j];
                } else {
                    revdp[1][j] = max(revdp[0][j], revdp[1][j + 1]);
                }
            }
        }
        for (int j = sl; j <= sr; j++) {
            revdp[0][j] = revdp[1][j];
            revdp[1][j] = 0;
        }
    }
}

void find_ans(int fl, int fr, int sl, int sr) {
    if (fr < fl || sr < sl) {
        return;
    } else if (fl == fr) {
        bool flag = false;
        for (int i = sl; i <= sr; i++) {
            if (a[fl] == b[i]) {
                flag = true;
            }
        }
        if (flag) {
            cout << a[fl];
        }
        return;
    }

    int m = (fl + fr) / 2;
    get_dp(fl, m, sl, sr);
    revget_dp(m + 1, fr, sl, sr);

    int from = sl - 1;
    int sum = revdp[0][sl];
    for (int i = sl; i < sr; i++) {
        if (dp[0][i] + revdp[0][i + 1] > sum) {
            sum = dp[0][i] + revdp[0][i + 1];
            from = i;
        }
    }
    if (dp[0][sr] > sum) {
        sum = dp[0][sr];
        from = sr;
    }
    find_ans(fl, m, sl, from);
    find_ans(m + 1, fr, from + 1, sr);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
//    freopen("matching.in", "r", stdin);
//    freopen("matching.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;

    find_ans(0, a.size() - 1, 0, b.size() - 1);
    cout << "\n";
    return 0;
}
