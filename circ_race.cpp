#include <cstdio>
void schedule(int **sche, int n)
{
    int subn = n - 1, subsubn = n - 2;
    for (int i = 0; i < n; i++)sche[0][i] = i;
    for (int i = 1; i < n; i++) {
        sche[i][0] = i;
        sche[i][i] = 0;
        for (int j = 0; j < subsubn; j++) {
            sche[i][((i + j) % subn) + 1] = ((i - j - 2 + subn) % subn) + 1;
        }
    }
}

void schedule2(int **sche, int n)
{
    int nsub1 = n - 1, nsub2 = n - 2, nsub3 = n - 3;
    for (int i = 0; i < n; i++)sche[0][i] = i;
    for (int i = 1; i < n; i++) {
        sche[i][nsub1] = i - 1;
        sche[i][i - 1] = nsub1;
        for (int j = 0; j < nsub2; j++) {
            sche[i][(i + j) % nsub1] = ((i - j + nsub3) % nsub1);
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
    }
    schedule(sche, n);
    schedule2(sche, n);
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
    for (int i = 0; i < n; i++) {
        delete[] sche[i];
    }
    delete[] sche;
}