#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;

const ll MOD = 1e9;
const int MAXN = 3e5 + 7;

struct Node {
    int sz;
    int y;
    int val;
    Node *left;
    Node *right;

    Node() {}

    Node(int value) {
        sz = 1;
        y = rand();
        val = value;
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

pair<Node*, Node*> split(Node *v, int k) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }

    if (getSize(v->left) < k) {
        pair<Node*, Node*> tmp = split(v->right, k - getSize(v->left) - 1);
        v->right = tmp.ff;
        v = updateSize(v);
        return {v, tmp.ss};
    } else {
        pair<Node*, Node*> tmp = split(v->left, k);
        v->left = tmp.ss;
        v = updateSize(v);
        return {tmp.ff, v};
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
        v = updateSize(v);
        return v;
    } else {
        u->left = merge(v, u->left);
        u = updateSize(u);
        return u;
    }
}

Node* toBegin(Node *v, int l, int r) {
    pair<Node*, Node*> tmp1 = split(v, l - 1);
    pair<Node*, Node*> tmp2 = split(tmp1.ss, r - l + 1);
    return merge(merge(tmp2.ff, tmp1.ff), tmp2.ss);
}

void print(Node *v) {
    if (v == nullptr) {
        return;
    }
    print(v->left);
    cout << v->val << " ";
    print(v->right);
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

    int n, m;
    cin >> n >> m;

    Node *tree = nullptr;
    for (int i = 1; i <= n; i++) {
        tree = merge(tree, new Node(i));
    }

    while (m--) {
        int l, r;
        cin >> l >> r;
        tree = toBegin(tree, l, r);
    }

    print(tree);

    return 0;
}
