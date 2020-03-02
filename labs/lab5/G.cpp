#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;

const ll MOD = 1e9;

struct Node {
    ll x;
    int y;
    ll sum;
    Node *left;
    Node *right;

    Node() {}

    Node(ll value) {
        x = value;
        sum = value;
        y = rand();
        left = nullptr;
        right = nullptr;
    }
};

Node* updateSum(Node *v) {
    ll result = v->x;
    if (v->left != nullptr) {
        result += v->left->sum;
    }
    if (v->right != nullptr) {
        result += v->right->sum;
    }

    v->sum = result;

    return v;
}

pair<Node*, Node*> split(Node *v, ll x) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }

    if (v->x < x) {
        pair<Node*, Node*> result = split(v->right, x);
        v->right = result.ff;
        updateSum(v);
        return {v, result.ss};
    } else {
        pair<Node*, Node*> result = split(v->left, x);
        v->left = result.ss;
        updateSum(v);
        return {result.ff, v};
    }
}

Node* merge(Node *v, Node *u) {
    if (v == nullptr) {
        return u;
    }
    if (u == nullptr) {
        return v;
    }

    if (v->y < u->y) {
        v->right = merge(v->right, u);
        updateSum(v);
        return v;
    } else {
        u->left = merge(v, u->left);
        updateSum(u);
        return u;
    }
}

bool find(Node *v, ll x) {
    if (v == nullptr) {
        return false;
    }

    if (v->x == x) {
        return true;
    } else if (v->x > x) {
        return find(v->left, x);
    } else {
        return find(v->right, x);
    }
}

Node* add(Node *v, ll x) {
    if (find(v, x)) {
        return v;
    }
    Node* u = new Node(x);
    if (v == nullptr) {
        return u;
    }

    pair<Node*, Node*> tmp = split(v, x);
    return merge(merge(tmp.ff, u), tmp.ss);
}

ll getSum(Node *v, ll l, ll r) {
    pair<Node*, Node*> tmp1 = split(v, l);
    pair<Node*, Node*> tmp2 = split(tmp1.ss, r + 1);

    ll result;
    if (tmp2.ff == nullptr) {
        result = 0;
    } else {
        result = tmp2.ff->sum;
    }

    merge(tmp1.ff, merge(tmp2.ff, tmp2.ss));
    return result;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#else
    // freopen("levenshtein.in", "r", stdin);
    // freopen("levenshtein.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Node* tree = nullptr;

    int m;
    bool prev = false;
    ll val = 0;
    cin >> m;


    while (m--) {
        char ch;
        cin >> ch;
        if (ch == '?') {
            ll l, r;
            cin >> l >> r;
            val = getSum(tree, l, r);
            cout << val << "\n";
            prev = true;
        } else {
            ll x;
            cin >> x;
            if (prev) {
                x = (x + val) % MOD;
            }
            tree = add(tree, x);
            prev = false;
        }
    }

    return 0;
}
