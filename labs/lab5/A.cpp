#include <bits/stdc++.h>

using namespace std;

#define first ff
#define second ss

struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

Node* insert(Node *v, int x) {
    if (v == nullptr) {
        return new Node(x);
    }

    if (v->key == x) {
        return v;
    } else if (v->key > x) {
        v->left = insert(v->left, x);
    } else {
        v->right = insert(v->right, x);
    }

    return v;
}

Node* next(Node *v, int x) {
    if (v == nullptr) {
        return v;
    }

    if (v->key > x) {
        Node* result = next(v->left, x);
        if (result == nullptr) {
            return v;
        } else {
            return result;
        }
    } else {
        return next(v->right, x);
    }
}

Node* prev(Node *v, int x) {
    if (v == nullptr) {
        return v;
    }

    if (v->key < x) {
        Node* result = prev(v->right, x);
        if (result == nullptr) {
            return v;
        } else {
            return result;
        }
    } else {
        return prev(v->left, x);
    }
}

Node* remove(Node *v, int x) {
    if (v == nullptr) {
        return v;
    }

    if (v->key > x) {
        v->left = remove(v->left, x);
    } else if (v->key < x) {
        v->right = remove(v->right, x);
    } else {
        if (v->left == nullptr && v->right == nullptr) {
            return nullptr;
        } else if (v->left == nullptr) {
            return v->right;
        } else if (v->right == nullptr) {
            return v->left;
        } else {
            v->key = next(v, v->key)->key;
            v->right = remove(v->right, v->key);
        }
    }

    return v;
}

string exist(Node* v, int x) {
    if (v == nullptr) {
        return "false";
    }

    if (v->key == x) {
        return "true";
    } else if (v->key > x) {
        return exist(v->left, x);
    } else {
        return exist(v->right, x);
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

    Node *tree = nullptr;

    string operation;
    int value;

    while (cin >> operation) {
        cin >> value;
        if (operation == "insert") {
            tree = insert(tree, value);
        } else if (operation == "delete") {
            tree = remove(tree, value);
        } else if (operation == "exists") {
            cout << exist(tree, value) << "\n";
        } else if (operation == "next") {
            Node* result = next(tree, value);
            if (result == nullptr) {
                cout << "none";
            } else {
                cout << result->key;
            }
            cout << "\n";
        } else {
            Node* result = prev(tree, value);
            if (result == nullptr) {
                cout << "none";
            } else {
                cout << result->key;
            }
            cout << "\n";
        }
    }
    return 0;
}
