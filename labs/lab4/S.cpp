//
// Created by vankataganai on 18.11.2019.
//
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const ll mod = 999999937;
const int maxn = 5e3 + 7;

vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b) {
    vector<vector<ll>> res(a.size(), vector<ll>(b[0].size(), 0));

    for (ui i = 0; i < a.size(); i++) {
        for (ui j = 0; j < b[0].size(); j++) {
            for (ui k = 0; k < b.size(); k++) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }

    return res;
}

vector<vector<ll>> pow(vector<vector<ll>> a, ll n) {
    if (n == 1) {
        return  a;
    }
    if (n % 2 == 0) {
        vector<vector<ll>> res = pow(a, n / 2);
        return mul(res, res);
    } else {
        return mul(a, pow(a, n - 1));
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("sequences.in", "r", stdin);
    freopen("sequences.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        if (n == 1) {
            cout << 5 << "\n";
            continue;
        }
        vector<vector<ll>> a = {{1}, {1}, {1}, {1}, {1}};
        vector<vector<ll>> b = {{1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1},
                                {1, 1, 0, 1, 0}, {1, 1, 0, 1, 0}};

        b = pow(b, n - 1);
        a = mul(b, a);

        ll ans = 0;
        for (int i = 0; i < 5; i++) {
            ans = (ans + a[i][0]) % mod;
        }

        cout << ans << "\n";
    }

    return 0;
}

