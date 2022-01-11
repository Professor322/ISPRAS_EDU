#include <iostream>

using namespace std;

int main(void) {
	int counter = 0;
	int n = 8;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << counter++ << '\t';
		}
		cout << '\n';
	}
	return 0;
}
