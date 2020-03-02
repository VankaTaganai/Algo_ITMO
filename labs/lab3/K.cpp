#include <bits/stdc++.h>

#define first ff
#define second ss

typedef long long ll;

using namespace std;

const int maxn = 1e6 + 7;
const int inf = 1e9 + 7;

struct Node {
    int key, degree, index, num_h;
    Node *parent;
    Node *child;
    Node *sibling;

    Node(int key, int index, int num_h) : key(key), degree(0), index(index), num_h(num_h),
    parent(nullptr), child(nullptr), sibling(nullptr) {}
};

Node* vertex[maxn];
vector<list<Node*>> H(1007);

Node* merge_trees(Node* a, Node* b) {
    if (a->key > b->key) {
        swap(a, b);
    }

    a->degree++;
    b->parent = a;
    b->sibling = a->child;
    a->child = b;
    return a;
}

list<Node*> merge_heaps(list<Node*> a, list<Node*> b) {
    list<Node*> tmp, res;
    auto it1 = a.begin();
    auto it2 = b.begin();

    while (it1 != a.end() && it2 != b.end()) {
        if ((*it1)->degree < (*it2)->degree) {
            tmp.emplace_back(*it1);
            it1++;
        } else {
            tmp.emplace_back(*it2);
            it2++;
        }
    }

    while (it1 != a.end()) {
        tmp.emplace_back(*it1);
        it1++;
    }

    while (it2 != b.end()) {
        tmp.emplace_back(*it2);
        it2++;
    }

    for (auto fr = tmp.begin(); fr != tmp.end();) {
        auto md = fr;
        md++;

        if (md == tmp.end()) {
            res.emplace_back(*fr);
            break;
        }

        auto ls = md;
        ls++;

        if (ls == tmp.end()) {
            if ((*fr)->degree == (*md)->degree) {
                res.emplace_back(merge_trees(*fr, *md));
            } else {
                res.emplace_back(*fr);
                res.emplace_back(*md);
            }
            break;
        }

        if ((*fr)->degree == (*md)->degree) {
            if ((*md)->degree == (*ls)->degree) {
                res.emplace_back(*fr);
                fr++;
                continue;
            } else {
                *fr = merge_trees(*fr, *md);
                tmp.erase(md);
                continue;
            }
        }

        res.emplace_back(*fr);
        fr++;
    }

    return res;
}

void decrease_key(Node* v, int x) {
    v->key = x;

    while (v->parent != nullptr) {
        if (v->parent->key < v->key) {
            break;
        }

        Node* par = v->parent;

        swap(par->key, v->key);
        swap(vertex[par->index], vertex[v->index]);
        swap(par->index, v->index);
        v = par;
    }
}

void extract_min(int a) {
    Node *to_del = (*H[a].begin());
    for (auto it = H[a].begin(); it != H[a].end(); it++) {
        if (to_del->key > (*it)->key ||
        (to_del->key == (*it)->key && to_del->index > (*it)->index)) {
            to_del = *it;
        }
    }

    list<Node*> new_heap;
    for (auto it = H[a].begin(); it != H[a].end(); it++) {
        if ((*it) == to_del) {
            continue;
        } else {
            new_heap.emplace_back(*it);
        }
    }

    to_del = to_del->child;
    list<Node*> without_vertex;

    while (to_del != nullptr) {
        to_del->parent = nullptr;
        Node* tmp = to_del;
        to_del = to_del->sibling;
        tmp->sibling = nullptr;
        without_vertex.emplace_back(tmp);
    }

    reverse(without_vertex.begin(), without_vertex.end());

    H[a] = merge_heaps(new_heap, without_vertex);
    for (auto it = H[a].begin(); it != H[a].end(); it++) {
        (*it)->num_h = a;
    }
}

int del(Node* v) {
    int ind = v->index;
    decrease_key(v, -inf);
    v = vertex[ind];
    int num = v->num_h;
    extract_min(num);
    return num;
}

void insert(int x, int num, int ind) {
    Node *tmp = new Node(x, ind, num);
    vertex[ind] = tmp;

    list<Node*> h;
    h.emplace_back(tmp);

    H[num] = merge_heaps(H[num], h);
    for (auto it = H[num].begin(); it != H[num].end(); it++) {
        (*it)->num_h = num;
    }
}

void init(int ind, int v) {
    int num = del(vertex[ind]);
    insert(v, num, ind);
}

void replace(int from, int to) {
    H[to] = merge_heaps(H[from], H[to]);
    for (auto it = H[to].begin(); it != H[to].end(); it++) {
        (*it)->num_h = to;
    }
    H[from].clear();
}

int get_min(int a) {
    int ans = inf;
    for (auto it = H[a].begin(); it != H[a].end(); it++) {
        ans = min((*it)->key, ans);
    }
    return ans;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    int last = 1;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int v, a;
            cin >> a >> v;
            insert(v, a, last);
            last++;
        } else if (t == 1) {
            int a, b;
            cin >> a >> b;
            replace(a, b);
        } else if (t == 2) {
            int a;
            cin >> a;
            del(vertex[a]);
        } else if (t == 3) {
            int ind, v;
            cin >> ind >> v;
            init(ind, v);
        } else if (t == 4) {
            int a;
            cin >> a;
            cout << get_min(a) << "\n";
        } else {
            int a;
            cin >> a;
            extract_min(a);
        }
    }

    return 0;
}
