#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("zero.in", "r", stdin);
	freopen("zero.out", "w", stdout);
	int n;
	cin >> n;
	vector<long long> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}
	reverse(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		cout << v[i] << " ";
	}
}

