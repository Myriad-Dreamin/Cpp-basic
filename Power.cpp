#include <cstdio>
int quick_pow(int a, int b)
{
	int res = 1;
	while(b)
	{
		if(b & 1)res = res * a;
		a = a * a;
		b >>= 1;
	}
	return res;
}

int quick_pmod(int a, int b, int mod)
{
	int res = 1;
	while(b)
	{
		if(b & 1)res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}
int main(){
	int a, n;
	scanf("%d%d",&a, &n);
	printf ("%d\n", quick_pow(a, n));
	// printf ("%d", quick_pmod(a, n, 3));
}