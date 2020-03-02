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
const int maxn = 2e6 + 7;
const int inf = 1e9 + 7;

int dp[maxn];
bool was[maxn];
int p[maxn];
int last[maxn];

int a[27], b[27], c[27];

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;


    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }

    last[0] = -1;
    was[0] = true;
    dp[0] = k;
    queue<int> q;
    q.push(0);
    while (q.size() != 0) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < n; i++) {
            if ((v & (1 << i)) == 0) {
                int to = (v | (1 << i));
                if (!was[to] && dp[v] >= a[i] && dp[v] <= b[i]) {
                    was[to] = true;
                    dp[to] = dp[v] + c[i];
                    p[to] = v;
                    last[to] = i;
                    q.push(to);
                }
            }
        }
    }

    int cnt = 0;
    int start = 0;

    for (int i = 0; i < (1 << n); i++) {
        if (!was[i]) {
            continue;
        }
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j))) {
                sum++;
            }
        }
        if (sum > cnt) {
            cnt = sum;
            start = i;
        }
    }

//    cout << start << "\n";

    int from = last[start];
    vector<int> ans;
    while (from != -1) {
        ans.push_back(from);
        start = p[start];
//        cout << start << "\n";
        from = last[start];
    }

    reverse(ans.begin(), ans.end());

    cout << cnt << "\n";
    for (int i : ans) {
        cout << i + 1 << " ";
    }

    return 0;
}

