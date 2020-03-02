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
    int val;
    int ph;
    Node *left;
    Node *right;

    Node() {}

    Node(int ind, int value) {
        x = ind;
        val = value;
        ph = 0;
        y = rand();
        left = nullptr;
        right = nullptr;
    }
};

Node* push(Node* v) {
    if (v == nullptr || v->ph == 0) {
        return v;
    }

    v->x += v->ph;
    if (v->left != nullptr) {
        v->left->ph += v->ph;
    }
    if (v->right != nullptr) {
        v->right->ph += v->ph;
    }
    v->ph = 0;
    return v;
}

pair<Node*, Node*> split(Node *v, ll x) {
    push(v);
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
    push(v);
    push(u);
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

int ans[MAXN];

void getAns(Node *v) {
    push(v);
    if (v == nullptr) {
        return;
    }
    getAns(v->left);
    getAns(v->right);
    ans[v->x] = v->val;
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

    set<pair<int, int>> st;


    int n, m;
    cin >> n >> m;

    st.insert({-1, -1});
    st.insert({MOD, MOD});

    for (int i = 1; i <= n; i++) {
        int ind;
        cin >> ind;
        auto it = (--st.upper_bound({ind, MOD + 1}));
        if ((*it).ss < ind) {
            pair<Node*, Node*> tmp = split(tree, ind);
            tree = merge(merge(tmp.ff, new Node(ind, i)), tmp.ss);
            if ((*it).ss + 1 == ind) {
                st.insert({(*it).ff, ind});
                st.erase(it);
            } else {
                st.insert({ind, ind});
            }
            it = st.upper_bound({ind, MOD + 1});
            auto prev = --it;
            ++it;
            if (it != st.end() && (*it).ff - 1 == ind) {
                st.insert({(*(prev)).ff, (*it).ss});
                st.erase(prev);
                st.erase(it);
            }
        } else {
            pair<Node*, Node*> tmp1 = split(tree, ind);
            pair<Node*, Node*> tmp2 = split(tmp1.ss, (*it).ss + 1);
            tmp2.ff->ph++;
            tree = merge(merge(merge(tmp1.ff, new Node(ind, i)), tmp2.ff), tmp2.ss);
            auto next = ++it;
            --it;
            if (next != st.end() && (*it).ss + 2 == (*next).ff) {
                st.insert({(*it).ff, (*(next)).ss});
                st.erase(next);
                st.erase(it);
            } else {
                st.insert({(*it).ff, (*it).ss + 1});
                st.erase(it);
            }
        }
    }

    getAns(tree);

    int to = -1;

    for (int i = 3e5; i >= 0; i--) {
        if (ans[i] != 0) {
            to = i;
            break;
        }
    }

    cout << to << "\n";

    for (int i = 1; i <= to; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
