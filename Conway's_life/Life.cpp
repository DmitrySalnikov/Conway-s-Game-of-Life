#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

class Life {
public:
	Life(int m, int n, bool * arr = nullptr) : nrow(m), ncol(n), size(m * n), 
			cur(arr), next(new bool[size]) {
		if (cur == nullptr) {
			cur = new bool[size];
			for (int i = 0; i < size; ++i) {
				cur[i] = rand() % 4 < 1;
			}
		}
	}

	void step() {
		for (int i = 0; i < nrow; ++i) {
			for (int j = 0; j < ncol; ++j) {
				if (at(i, j))
					next[i * ncol + j] = is_alive(i, j);
				else
					next[i * ncol + j] = is_born(i, j);
			}
		}
		swap(cur, next);
	}

	void show() const {
		for (int i = 0; i < nrow; ++i) {
			for (int j = 0; j < ncol; ++j) {
				cout << (at(i, j) ? (char)(-127) : '-');
			}
			cout << endl;
		}
	}

private:
	int nrow;
	int ncol;
	int size;
	bool * cur;
	bool * next;
	bool at(int i, int j) const {
		return cur[(i * ncol + j) % size];
	}
	bool is_alive(int i, int j) const {
		bool temp[8];
		temp[0] = at((i + nrow - 1) % nrow, (j + ncol - 1) % ncol);
		temp[1] = at((i + nrow - 1) % nrow, j);
		temp[2] = at((i + nrow - 1) % nrow, (j + 1) % ncol);
		temp[3] = at(i, (j + ncol - 1) % ncol);
		temp[4] = at(i, (j + 1) % ncol);
		temp[5] = at((i + 1) % nrow, (j + ncol - 1) % ncol);
		temp[6] = at((i + 1) % nrow, j);
		temp[7] = at((i + 1) % nrow, (j + 1) % ncol);
		int sum = 0;
		for (int i = 0; i < 8; ++i) {
			sum += temp[i];
		}
		return sum > 1 && sum < 4;
	}
	bool is_born(int i, int j) const {
		bool temp[8];
		temp[0] = at((i + nrow - 1) % nrow, (j + ncol - 1) % ncol);
		temp[1] = at((i + nrow - 1) % nrow, j);
		temp[2] = at((i + nrow - 1) % nrow, (j + 1) % ncol);
		temp[3] = at(i, (j + ncol - 1) % ncol);
		temp[4] = at(i, (j + 1) % ncol);
		temp[5] = at((i + 1) % nrow, (j + ncol - 1) % ncol);
		temp[6] = at((i + 1) % nrow, j);
		temp[7] = at((i + 1) % nrow, (j + 1) % ncol);
		int sum = 0;
		for (int i = 0; i < 8; ++i) {
			sum += temp[i];
		}
		return sum == 3;
	}

};

int main(int argc, char const *argv[]) {
	srand(time(0));

	bool * line = new bool[25] {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	Life Vladik(40, 160);
	Vladik.show();
	string ans;
	getline(cin, ans);
	while (ans == "") {
		Vladik.step();
		Vladik.show();
		getline(cin, ans);
	}

	return 0;
}