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
const int maxn = 1e3 + 7;

bool dp[maxn][maxn];
int p[maxn][maxn];
int from[maxn][maxn];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    queue<pair<int, int>> q;
    q.emplace(0, 0);
    dp[0][0] = true;

    while (q.size() != 0) {
        auto tmp = q.front();
        q.pop();
        int a = tmp.ff;
        int b = tmp.ss;
        if (a == n && b == 0) {
            break;
        }
        for (int i = 0; i < 10; i++) {
            int sum = a + i;
            int rem = (b * 10 + i) % n;
            if (sum > n) {
                break;
            }
            if (!dp[sum][rem]) {
                dp[sum][rem] = true;
                p[sum][rem] = i;
                from[sum][rem] = b;
                q.emplace(sum, rem);
            }
        }
    }


    int x = n, y = 0;

    vector<int> ans;

    while (x != 0) {
        ans.push_back(p[x][y]);
        int del = p[x][y];
        y = from[x][y];
        x -= del;
    }

    reverse(ans.begin(), ans.end());

    for (auto i : ans) {
        cout << i;
    }

    return 0;
}

