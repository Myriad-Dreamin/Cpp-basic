#include <cstdio>
#include <cstring>
void schedule(int **sche, int n)
{
	printf("%d\n", n);
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
void schedule_print(int **sche, int n)
{
	printf("id      |");
	for (int i = 0; i < n; i++) {
	    if (i) {
	        printf("day %4d|", i);
	    }
	    for (int j = 0; j < n; j++) {
	        printf("%4d ", sche[i][j]);
	    }
	    puts("");
	    if (!i) {
	        printf("---------");
	        for (int j = 0; j < n; j++) {
	            printf("-----");
	        }
	        puts("");
	    }
	}
}
int main()
{
    int n;
    scanf("%d",&n);
    if (n&1) {
        n++;
    }
    int **sche = new int*[n];
    for (int i = 0; i < n; i++) {
        sche[i] = new int[n];
        memset(sche[i], 0 , n << 2);
    }
    schedule(sche, n);
    schedule_print(sche, n);
    for (int i = 0; i < n; i++) {
        delete[] sche[i];
    }
    delete[] sche;
}