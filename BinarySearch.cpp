#include <cstdio>
#include <algorithm>
using namespace std;
int a[2000];
const int INF = 0x7fffffff;
int binarysearch(int arr[],int n,int tos)
{
	if(n <= 0)return -INF;
	int m = n >> 1;

	if(arr[m] == tos)
	{
		return m;
	} else if (arr[m] < tos){
		return m + 1 + binarysearch(arr + m + 1, n - m - 1, tos);
	} else {
		return binarysearch(arr, m, tos);
	}
}
int main(){
	int n;
	scanf("%d", &n);
	for(int i = 1;i <= n; i++){
		scanf("%d", a + i);
	}
	int x;
	scanf("%d", &x);
	sort(a + 1, a + 1 + n);
	printf("%d",binarysearch(a + 1, n, x) + 1);
}