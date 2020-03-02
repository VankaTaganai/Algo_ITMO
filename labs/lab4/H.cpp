#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

#define ff first
#define ss second

const double eps = 1e-6;
const int mod = 45;
const int maxn = 18;
const ll infl = 1e18 + 7;

ll dp_cnt[maxn][(1 << maxn)];

vector<int> v;
int n, k;
ll m;

vector<int> ans;

bool flag = false;

void get_ans(int mask, int last) {
    if (mask == (1 << n) - 1) {
        if (m == 1) {
            for (int i : ans) {
                cout << i << " ";
            }
            flag = true;
        }
        m--;
        return;
    }


    for (int i = 0; i < n; i++) {
        if ((mask & (1 << i)) == 0 && (__gcd(last, v[i]) >= k || last == 0)) {
            int new_mask = mask | (1 << i);
            int rev_mask = 0;
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) == 0) {
                    rev_mask |= (1 << j);
                }
            }
            ll cnt = dp_cnt[i][rev_mask];

            if (cnt < m) {
                m -= cnt;
            } else {
                ans.push_back(v[i]);
                get_ans(new_mask, v[i]);
                return;
            }
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v.emplace_back(x);
    }

    sort(v.begin(), v.end());

    for (int i = 0; i < n; i++) {
        dp_cnt[i][(1 << i)] = 1;
    }

    for (int i = 1; i < n; i++) {
        vector<int> tmp;
        for (int j = 0; j < i; j++) {
            tmp.emplace_back(1);
        }
        for (int j = 0; j < n - i; j++) {
            tmp.emplace_back(0);
        }

        reverse(tmp.begin(), tmp.end());

        do {
            int start = 0;
            for (int j : tmp) {
                start = start * 2 + j;
            }

            for (int from = 0; from < n; from++) {
                if (start & (1 << from)) {
                    for (int to = 0; to < n; to++) {
                        if ((start & (1 << to)) == 0) {
                            if (__gcd(v[from], v[to]) >= k) {
                                dp_cnt[to][start | (1 << to)] += dp_cnt[from][start];
                            }
                        }
                    }
                }
            }
        } while (next_permutation(tmp.begin(), tmp.end()));
    }
    get_ans(0, 0);

    if (!flag) {
        cout << -1;
    }

    return 0;
}
