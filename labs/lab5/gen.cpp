#include <bits/stdc++.h>

using namespace std;

#define first ff
#define second ss

string s[3] = {"insert", "delete", "exists"};

int main() {
#ifdef LOCAL
//    freopen("in.txt", "r", stdin);
    freopen("in.txt", "w", stdout);
#else
    // freopen("levenshtein.in", "r", stdin);
    // freopen("levenshtein.out", "w", stdout);
#endif

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(0));

    int tests = 200;

    while (tests--) {
        int x = rand() % 10;
        cout << s[rand() % 2] << " " << x << "\n";
        cout << s[2] << " " << rand() % 10 << "\n";
    }

    return 0;
}
