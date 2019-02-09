#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

class Life {
public:
	Life(int m, int n) : nrow(m), ncol(n), size(m * n), nstep(0), cur(size), next(size) {
		for (int i = 0; i < size; ++i) {
			cur[i] = rand() % 2;
		}
	}

	void step() {
		if (nstep % 2) {	// 1 день и т.п.
			for (int i = 0; i < nrow; ++i) {
				for (int j = 0; j < ncol; ++j) {
					if (at(next, i, j))
						cur[(i * ncol + j) % size] = is_alive(next, i, j);
					else
						cur[(i * ncol + j) % size] = is_born(next, i, j);
				}
			}	
		}
		else {				// 0 день и т.п.
			for (int i = 0; i < nrow; ++i) {
				for (int j = 0; j < ncol; ++j) {
					if (at(cur, i, j))
						next[(i * ncol + j) % size] = is_alive(cur, i, j);
					else
						next[(i * ncol + j) % size] = is_born(cur, i, j);
				}
			}	
		}
		++nstep;
	}

	void show() const {
		vector<bool> const & c = (nstep % 2 ? next : cur);
		for (int i = 0; i < nrow; ++i) {
			for (int j = 0; j < ncol; ++j) {
				cout << (at(c, i, j) ? (char)(-127) : '-');
			}
			cout << endl;
		}
	}

private:
	int nrow;
	int ncol;
	int size;
	int nstep;
	vector<bool> cur;
	vector<bool> next;
	bool at(vector<bool> const & a, int i, int j) const {
		return a[(i * ncol + j) % size];
	}
	bool is_alive(vector<bool> const & a, int i, int j) const {
		vector<bool> temp(8);
		temp[0] = at(a, i - 1, j - 1);
		temp[1] = at(a, i - 1, j);
		temp[2] = at(a, i - 1, j + 1);
		temp[3] = at(a, i, j - 1);
		temp[4] = at(a, i, j + 1);
		temp[5] = at(a, i + 1, j - 1);
		temp[6] = at(a, i + 1, j);
		temp[7] = at(a, i + 1, j + 1);
		int sum = 0;
		for (auto it = temp.begin(); it != temp.end(); ++it) {
			sum += *it;
		}
		return sum > 1 && sum < 4;
	}
	bool is_born(vector<bool> const & a, int i, int j) const {
		vector<bool> temp(8);
		temp[0] = at(a, i - 1, j - 1);
		temp[1] = at(a, i - 1, j);
		temp[2] = at(a, i - 1, j + 1);
		temp[3] = at(a, i, j - 1);
		temp[4] = at(a, i, j + 1);
		temp[5] = at(a, i + 1, j - 1);
		temp[6] = at(a, i + 1, j);
		temp[7] = at(a, i + 1, j + 1);
		int sum = 0;
		for (auto it = temp.begin(); it != temp.end(); ++it) {
			sum += *it;
		}
		return sum == 3;
	}

};

int main(int argc, char const *argv[]) {
	srand(time(0));

	Life Vladik(30, 60);
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