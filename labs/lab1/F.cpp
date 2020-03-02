#include <iostream>
#include <cstdlib>

using namespace std;

struct vector {
	int sz;
	int cap;
	int *a;

	vector() {
		sz = 0;
		cap = 1;
		a = (int *)malloc(sizeof(int));
	}

	int pop() {
		return a[--sz];
	}

	void push(int x) {
		if (sz == cap) {
			int *buf = (int *)malloc(cap * sizeof(int));
			for (int i = 0; i < sz; i++) {
				buf[i] = a[i];
			}
			free(a);
			cap *= 2;
			a = (int *)malloc(cap * sizeof(int));
			for (int i = 0; i < sz; i++) {
				a[i] = buf[i];
			}
			free(buf);
		}
		a[sz++] = x;
	}
};

struct stack {
	vector v;

	stack() {
		v = vector();
	}

	int pop() {
		return v.pop();
	}

	void push(int x) {
		v.push(x);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	stack st;

	char ch;
	while (cin >> ch) {
		if (ch == '+') {
			int a = st.pop(), b = st.pop();
			st.push(a + b);
		} else if (ch == '-') {
			int a = st.pop(), b = st.pop();
			st.push(b - a);
		} else if (ch == '*') {
			int a = st.pop(), b = st.pop();
			st.push(a * b);
		} else {
			st.push(ch - '0');
		}
	}

	cout << st.pop() << "\n";

	return 0;
}
