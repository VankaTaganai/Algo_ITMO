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
const int maxn = 3e5 + 7;

int dp[maxn];
int id[maxn];
int p[maxn];
int a[maxn];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    dp[0] = -inf;
    for (int i = 1; i <= n; i++) {
        dp[i] = inf;
    }

    int len = 0;
    int ans = -1;

    id[0] = -1;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i] = x;
        int ind = lower_bound(dp, dp + n + 1, x) - dp;
        p[i] = id[ind - 1];
        dp[ind] = x;
        id[ind] = i;
        if (ind > len) {
            len = ind;
            ans = i;
        }
    }

    vector<int> out;
    while (ans != -1) {
        out.push_back(a[ans]);
        ans = p[ans];
    }

    cout << out.size() << "\n";
    reverse(out.begin(), out.end());
    for (auto i : out) {
        cout << i << " ";
    }


    return 0;
}
