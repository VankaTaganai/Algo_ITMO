#include <bits/stdc++.h>

#define first ff
#define second ss

typedef long long ll;

using namespace std;

const int maxn = 1e5 + 7;
const ll p = 1e6 + 3;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    int iter = (int)(sqrt(m)) / 2;
    int last = iter + 1;
    int oper = 0;

    for (int i = 0; i < iter; ++i) {
        cout << "1 " << last << " " << i + 1 << "\n";
        oper++;
    }

    for (int i = 0; i < iter; ++i) {
        for (int j = 0; j < last; ++j) {
            if (j + 2 >= last) {
                break;
            }
            cout << "0 " << j + 1 << " " << j + 2 << "\n";
            oper++;
            j++;
        }
        cout << "1 " << last + 1 << " " << last << "\n";
        oper++;
        last++;
    }

    while (oper < m) {
        cout << "0 1 2\n";
        oper++;
    }

    return 0;
}
