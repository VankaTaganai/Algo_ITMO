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

int MOD;

vector<vector<ll>> mul(vector<vector<ll>> a, vector<vector<ll>> b) {
    vector<vector<ll>> res(a.size(), vector<ll>(b[0].size(), 0));

    for (ui i = 0; i < a.size(); i++) {
        for (ui j = 0; j < b[0].size(); j++) {
            for (ui k = 0; k < b.size(); k++) {
                res[i][j] = (res[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }

    return res;
}

string div(string a) {
    string res;
    int sum = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        sum = (sum * 10 + a[i] - '0');
        res.push_back(char(sum / 2 + '0'));
        sum = sum % 2;
    }
    reverse(res.begin(), res.end());
    while (res.back() == '0') {
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    return res;
}

string dec(string a) {
    int ind = a.size() - 1;
    while (a[ind] == '0') {
        a[ind] = '9';
        ind--;
    }
    a[ind] = char(a[ind] - 1);
    reverse(a.begin(), a.end());
    while (a.back() == '0') {
        a.pop_back();
    }
    reverse(a.begin(), a.end());
    return a;
}

vector<vector<ll>> pow(vector<vector<ll>> a, string n) {
    if (n == "1") {
        return  a;
    }
    if ((n.back() - '0') % 2 == 0) {
        vector<vector<ll>> res = pow(a, div(n));
        return mul(res, res);
    } else {
        return mul(a, pow(a, dec(n)));
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("nice3.in", "r", stdin);
    freopen("nice3.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string n;
    int m;
    cin >> n >> m >> MOD;

    vector<vector<ll>> mat((1 << m), vector<ll>(1 << m));

    vector<int> mask;

    for (int i = 0; i < (1 << m); i++) {
        mask.emplace_back(i);
    }

    for (int i = 0; i < (int)mask.size(); i++) {
        for (int j = 0; j < (int)mask.size(); j++) {
            bool flag = true;
            for (int k = 0; k < m - 1; k++) {
                bool clr1 = mask[i] & (1 << k);
                bool clr2 = mask[i] & (1 << (k + 1));
                bool clr3 = mask[j] & (1 << k);
                bool clr4 = mask[j] & (1 << (k + 1));
                if (clr1 == clr2 && clr1 == clr3 && clr1 == clr4) {
                    flag = false;
                }
            }
            mat[i][j] = flag;
        }
    }

    if (n == "1") {
        cout << (1 << m) % MOD;
        return 0;
    }

    n = dec(n);

    mat = pow(mat, n);

    ll ans = 0;
    for (int i = 0; i < (1 << m); i++) {
        for (int j = 0; j < (1 << m); j++) {
            ans = (ans + mat[i][j]) % MOD;
        }
    }

    cout << ans;

    return 0;
}

