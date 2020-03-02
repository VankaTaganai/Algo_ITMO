#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;

const ll MOD = 1e9;

struct Node {
    int x;
    int y;
    int sz;
    Node *left;
    Node *right;

    Node() {}

    Node(int value) {
        x = value;
        sz = 1;
        y = rand();
        left = nullptr;
        right = nullptr;
    }
};

int getSize(Node *v) {
    if (v == nullptr) {
        return 0;
    }
    return v->sz;
}

Node* updateSize(Node *v) {
    if (v == nullptr) {
        return v;
    }

    v->sz = 1 + getSize(v->left) + getSize(v->right);
    return v;
}

pair<Node*, Node*> split(Node *v, ll x) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }

    if (v->x < x) {
        pair<Node*, Node*> result = split(v->right, x);
        v->right = result.ff;
        updateSize(v);
        return {v, result.ss};
    } else {
        pair<Node*, Node*> result = split(v->left, x);
        v->left = result.ss;
        updateSize(v);
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
        updateSize(v);
        return v;
    } else {
        u->left = merge(v, u->left);
        updateSize(u);
        return u;
    }
}

Node* add(Node *v, int x) {
    Node* u = new Node(x);
    if (v == nullptr) {
        return u;
    }

    pair<Node*, Node*> tmp = split(v, x);
    return merge(merge(tmp.ff, u), tmp.ss);
}

int kth(Node *v, int k) {
    if (getSize(v->left) == k - 1) {
        return v->x;
    } else if (getSize(v->left) < k - 1) {
        return kth(v->right, k - getSize(v->left) - 1);
    } else {
        return  kth(v->left, k);
    }
}

Node* remove(Node *v, int x) {
    pair<Node*, Node*> tmp1 = split(v, x);
    pair<Node*, Node*> tmp2 = split(tmp1.ss, x + 1);
    return merge(tmp1.ff, tmp2.ss);
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

    int m;
    cin >> m;

    Node* tree = nullptr;

    while (m--) {
        int c, k;
        cin >> c >> k;
        if (c == 1) {
            tree = add(tree, k);
        } else if (c == 0) {
            cout << kth(tree, getSize(tree) - k + 1) << "\n";
        } else {
            tree = remove(tree, k);
        }
    }

    return 0;
}
