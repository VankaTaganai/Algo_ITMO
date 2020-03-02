#include <bits/stdc++.h>

#define first ff
#define second ss

typedef long long ll;

using namespace std;

const int maxn = 3e5;

ll val[maxn];
ll indAr[maxn];
ll indIn[maxn];
ll last = 1;

void siftUp(ll x) {
    ll ind = indIn[x];
    while (x > 1 && val[x] > val[x / 2]) {
        swap(val[x], val[x / 2]);
        swap(indAr[ind], indAr[indIn[x / 2]]);
        swap(indIn[x], indIn[x / 2]);
        x /= 2;
    }
}

void siftDown(ll x) {
    ll ind = indIn[x];
    while (2 * x < last) {
        ll l = 2 * x;
        ll r = 2 * x + 1;
        ll to = l;
        if (r < last && val[r] > val[l]) {
            to = r;
        }
        if (val[x] >= val[to]) {
            break;
        }
        swap(val[x], val[to]);
        swap(indAr[ind], indAr[indIn[to]]);
        swap(indIn[x], indIn[to]);
        x = to;
    }
}

void insert(ll x) {
    val[last] = x;
    siftUp(last);
    last++;
}

ll get(bool del) {
    ll min = val[1];
    if (del) {
        swap(indAr[indIn[1]], indAr[indIn[last - 1]]);
        swap(indIn[1], indIn[last - 1]);
        val[1] = val[--last];
        siftDown(1);
    }
    return min;
}

struct Q {
    ll l, t, val, ind;

    Q(ll l, ll t, ll val, ll ind) : l(l), t(t), val(val), ind(ind) {}

    bool operator < (Q a) {
        if (l == a.l) {
            return t < a.t;
        }
        return l < a.l;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<Q> q;

    for (int i = 0; i < m; i++) {
        ll l, r, num;
        cin >> l >> r >> num;
        l--, r--;
        q.emplace_back(l, 0, num, i);
        q.emplace_back(r, 1, num, i);
    }

    sort(q.begin(), q.end());

    int ind = 0;

    for (int i = 0; i < n; i++) {
        while (ind < (int)q.size() && q[ind].l <= i && q[ind].t == 0) {
            indAr[q[ind].ind] = last;
            indIn[last] = q[ind].ind;
            insert(q[ind].val);
            ind++;
        }
        if (last != 1) {
            cout << get(false) << " ";
        } else {
            cout << 1 << " ";
        }
        while (ind < (int)q.size() && q[ind].l <= i && q[ind].t == 1) {
            ll p = indAr[(int)q[ind].ind];
            val[p] = 1e18;
            siftUp(p);
            get(true);
            ind++;
        }
    }

    return 0;
}
