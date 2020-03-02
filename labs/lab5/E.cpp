#include <bits/stdc++.h>

using namespace std;

#define ff first
#define ss second

typedef long long ll;

const ll MOD = 1e9;
const int MAXN = 3e5 + 7;

struct Node {
    int x;
    int y;
    int ind;
    Node *left;
    Node *right;

    Node() {}

    Node(int value, int prior, int ind) {
        x = value;
        y = prior;
        this->ind = ind;
        left = nullptr;
        right = nullptr;
    }
};

pair<Node*, Node*> split(Node *v, int x) {
    if (v == nullptr) {
        return {nullptr, nullptr};
    }

    if (v->x < x) {
        pair<Node*, Node*> result = split(v->right, x);
        v->right = result.ff;
        return {v, result.ss};
    } else {
        pair<Node*, Node*> result = split(v->left, x);
        v->left = result.ss;
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
        return v;
    } else {
        u->left = merge(v, u->left);
        return u;
    }
}

Node* add(Node *v, int x, int y, int ind) {
    Node* u = new Node(x, y, ind);
    if (v == nullptr) {
        return u;
    }

    pair<Node*, Node*> tmp = split(v, x);
    return merge(merge(tmp.ff, u), tmp.ss);
}

int p[MAXN];
int l[MAXN];
int r[MAXN];

void getAns(Node *v, Node* from = nullptr) {
    p[v->ind] = from == nullptr ? 0 : from->ind;

    l[v->ind] = v->left == nullptr ? 0 : v->left->ind;

    r[v->ind] = v->right == nullptr ? 0 : v->right->ind;

    if (v->left != nullptr) {
        getAns(v->left, v);
    }

    if (v->right != nullptr) {
        getAns(v->right, v);
    }
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

    vector<pair<pair<int, int>, int>> v;
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        v.push_back({{a, b}, i});
    }

    sort(v.begin(), v.end());

    queue<Node*> q;
    for (int i = 0; i < m; i++) {
        q.push(new Node(v[i].ff.ff, v[i].ff.ss, v[i].ss));
    }

    while (q.size() > 1) {
        Node *left = q.front();
        q.pop();
        Node *right = q.front();
        q.pop();
        if (left->x > right->x) {
            q.push(left);
            left = right;
            right = q.front();
            q.pop();
        }
        q.push(merge(left, right));
    }

    cout << "YES\n";
    getAns(q.front());
    for (int i = 1; i <= m; i++) {
        cout << p[i] << " " << l[i] << " " << r[i] << "\n";
    }

    return 0;
}
