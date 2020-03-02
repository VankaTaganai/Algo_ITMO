#include <bits/stdc++.h>

using namespace std;

#define first ff
#define second ss

const int MINF = -1e9 - 1;

struct Node {
    Node* parent;
    Node* child[4];
    int key[3];
    int cnt;
    int mx;

    Node() {
        mx = key[0] = MINF;
        child[0] = child[1] = child[2] = parent = nullptr;
        cnt = 0;
    }

    Node(int value) {
        mx = key[0] = value;
        child[0] = child[1] = child[2] = parent = nullptr;
        cnt = 0;
    }
};

Node* tree = nullptr;

Node* find(Node* v, int x) {
    if (v->cnt == 0) {
        return v;
    } else if (v->cnt == 2) {
        if (v->key[0] >= x) {
            return find(v->child[0], x);
        } else {
            return find(v->child[1], x);
        }
    } else {
        if (v->key[0] >= x) {
            return find(v->child[0], x);
        } else if (v->key[1] >= x) {
            return find(v->child[1], x);
        } else {
            return find(v->child[2], x);
        }
    }
}

bool cmp(Node* a, Node* b) {
    return a->mx < b->mx;
}

void my_sort(Node* v) {
    for (int i = 0; i < v->cnt; i++) {
        for (int j = i + 1; j < v->cnt; j++) {
            if (v->child[j]->mx < v->child[i]->mx) {
                swap(v->child[i], v->child[j]);
            }
        }
    }
}

void sorting(Node* v) {
    my_sort(v);
    for (int i = 0; i < v->cnt - 1; i++) {
        v->key[i] = v->child[i]->mx;
    }
    v->mx = v->child[v->cnt - 1]->mx;
}

void balance(Node* v) {
    if (v->cnt <= 3) {
        return;
    }

    Node* x = new Node();
    v->cnt = x->cnt = 2;
    x->key[0] = v->key[2];
    x->child[0] = v->child[2];
    x->child[1] = v->child[3];
    x->child[0]->parent = x->child[1]->parent = x;
    x->parent = v->parent;
    v->child[2] = v->child[3] = nullptr;
    sorting(x);
    sorting(v);

    if (v->parent) {
        v->parent->child[v->parent->cnt++] = x;
        sorting(v->parent);
        balance(v->parent);
    } else {
        Node* res = new Node();
        res->cnt = 2;
        res->child[0] = v;
        res->child[1] = x;
        v->parent = res;
        x->parent = res;
        res->parent = nullptr;
        sorting(res);
        tree = res;
    }
}

void insert(int x) {
    if (!tree) {
        tree = new Node(x);
        return;
    }
    Node* a = find(tree, x);
    Node* b = new Node(x);
    if (a->parent) {
        a->parent->child[a->parent->cnt++] = b;
        b->parent = a->parent;
        sorting(a->parent);
        balance(a->parent);
    } else {
        Node* res = new Node();
        res->child[0] = a;
        res->child[1] = b;
        a->parent = res;
        b->parent = res;
        res->cnt = 2;
        sorting(res);
        balance(res);
        tree = res;
    }
    b = b->parent;
    while (b) {
        sorting(b);
        b = b->parent;
    }
}

void remove(Node* v) {
    if (!v->parent) {
        tree = nullptr;
    } else if (v->parent->cnt == 3) {
        bool flag = false;
        for (int i = 0; i < v->parent->cnt - 1; i++) {
            if (v->parent->child[i] == v) {
                flag = true;
            }
            if (flag) {
                v->parent->child[i] = v->parent->child[i + 1];
            }
        }
        v->parent->cnt--;
        v = v->parent;
        while (v) {
            sorting(v);
            v = v->parent;
        }
    } else {
        Node* p = v->parent;
        Node* b;
        if (p->child[0] == v) {
            b = p->child[1];
        } else {
            b = p->child[0];
        }
        Node* gp = p->parent;
        if (!gp) {
            b->parent = nullptr;
            tree = b;
        } else {
            Node* np = nullptr;
            if (gp->child[0] == p || (gp->cnt == 3 && gp->child[2] == p)) {
                np = gp->child[1];
            } else {
                np = gp->child[0];
            }
            if (gp->cnt == 3 && np->cnt == 2) {
                b->parent = np;
                np->child[np->cnt++] = b;
                gp->cnt--;
                if (gp->child[0] == p) {
                    gp->child[0] = gp->child[1];
                    gp->child[1] = gp->child[2];
                } else if (gp->child[1] == p) {
                    gp->child[1] = gp->child[2];
                }
                b = b->parent;
                while (b) {
                    sorting(b);
                    b = b->parent;
                }
            } else if (np->cnt == 3) {
                p->cnt--;
                if (p->child[0] == v) {
                    p->child[0] = p->child[1];
                }
                if (np->mx > p->mx) {
                    np->child[0]->parent = p;
                    p->child[p->cnt++] = np->child[0];
                    np->cnt--;
                    np->child[0] = np->child[1];
                    np->child[1] = np->child[2];
                } else {
                    np->child[2]->parent = p;
                    p->child[p->cnt++] = np->child[2];
                    np->cnt--;
                }
                sorting(p);
                sorting(np);
                b = b->parent;
                while (b) {
                    sorting(b);
                    b = b->parent;
                }
            } else {
                np->child[np->cnt++] = b;
                b->parent = np;
                sorting(np);
                b = b->parent;
                while (b) {
                    sorting(b);
                    b = b->parent;
                }
                remove(p);
            }
        }
    }
}

int next(int x) {
    if (!tree) {
        return MINF;
    }
    Node* v = find(tree, x);
    if (v->key[0] > x) {
        return v->key[0];
    } else {
        while (v) {
            int k = v->mx;
            v = v->parent;
            if (!v) {
                return MINF;
            }
            for (int i = 0; i < v->cnt; i++) {
                if (v->child[i]->mx > k) {
                    v = v->child[i];
                    while (v->cnt != 0) {
                        v = v->child[0];
                    }
                    return v->key[0];
                }
            }
        }
    }
    return MINF;
}

int prev(int x) {
    if (!tree) {
        return MINF;
    }
    Node* v = find(tree, x);
    if (v->key[0] < x) {
        return v->key[0];
    } else {
        while (v) {
            int k = v->mx;
            v = v->parent;
            if (!v) {
                return MINF;
            }
            for (int i = v->cnt - 1; i >= 0; i--) {
                if (v->child[i]->mx < k) {
                    v = v->child[i];
                    while (v->cnt != 0) {
                        v = v->child[v->cnt - 1];
                    }
                    return v->key[0];
                }
            }
        }
    }
    return MINF;
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



    string operation;

    while (cin >> operation) {
        int x;
        cin >> x;
        if (operation == "insert") {
            if (tree && find(tree, x)->key[0] == x) {
                continue;
            }
            insert(x);
        } else if (operation == "delete") {
            if (tree == nullptr || find(tree, x)->key[0] != x) {
                continue;
            }
            remove(find(tree, x));
        } else if (operation == "exists") {
            if (tree == nullptr || find(tree, x)->key[0] != x) {
                cout << "false\n";
            } else {
                cout << "true\n";
            }
        } else if (operation == "next") {
            int res = next(x);
            if (res == MINF || res <= x) {
                cout << "none\n";
            } else {
                cout << res << "\n";
            }
        } else {
            int res = prev(x);
            if (res == MINF || res >= x) {
                cout << "none\n";
            } else {
                cout << res << "\n";
            }
        }
    }
    return 0;
}
