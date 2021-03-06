#include <iostream>
#include <iomanip>
#include <cstring>

void schedule(int **sche, int n)
{
	if (n == 2) {
		sche[0][0] = 0; sche[0][1] = 1;
		sche[1][0] = 1; sche[1][1] = 0;
		return ;
	}
	if(n & 1) {
		schedule(sche, n + 1);
	} else {
		int nrs1 = n >> 1, nrs1p1 = nrs1 + 1;
		schedule(sche, nrs1);
		if (nrs1 & 1) {
			for (int i = nrs1; i < n; i++) {
				for (int j = 0; j < nrs1p1; j++) {
					sche[i][j] = sche[i - nrs1][j] + nrs1;
				}
				sche[i][n - i] = i - nrs1;
				sche[i - nrs1][n - i] = i;
			}
			for (int i = 0; i < nrs1; i++) {
				for (int j = nrs1 + 1; j < n; j++) {
					sche[i][j] = (i + j - nrs1) % nrs1 + nrs1;
					sche[i + nrs1][j] = (i - j + n) % nrs1;
				}
			}
		}else {
			for (int i = 0; i < nrs1; i++) {
				for (int j = nrs1; j < n; j++) {
					sche[i][j] = sche[i][j - nrs1] + nrs1;
				}
				memcpy(sche[i + nrs1], sche[i] + nrs1, n << 1);
				memcpy(sche[i + nrs1] + nrs1, sche[i], n << 1);
			}
		}
	}
}

void schedule_print (int **sche, int n)
{
    using std::cout;
    using std::endl;
    cout << "id      |";
    for (int i = 0; i < n; i++) {
        if (i) {
            cout << "day " << std::setw(4) << i << "|";
        }
        for (int j = 0; j < n; j++) {
            cout << std::setw(4) << sche[i][j] << " ";
        }
        cout << endl;
        if (!i) {
            cout << "---------";
            for (int j = 0; j < n; j++) {
                cout << "-----";
            }
            cout << endl;
        }
    }
}
int main()
{
	std::ios::sync_with_stdio(false);
    int n;
	std::cin >> n;
    if (n&1) {
        n++;
    }
    int **sche = new int*[n];
    for (int i = 0; i < n; i++) {
        sche[i] = new int[n];
    }
    auto beg = clock();
    schedule(sche, n);
    // schedule_print(sche, n);
    std::cout << clock() - beg << "ms" << std::endl;
    for (int i = 0; i < n; i++) {
        delete[] sche[i];
    }
    delete[] sche;
}