#include <cstdio>
int A[205],B[205];
// A = A_1 * X + A_2
// B = B_1 * X + B_2
// C = A * B = A_1B_1 * X^2 + (A_2B_1 + A_1B_2) * X + A_2B_2
// A_2B_1 + A_1B_2 = (A_1 + A_2)(B_1 + B_2) - A_1B_1 + A_2B_2
int karatsuba(int *A,int *B,int n)
{
	static int X[205],Y[205];
	int b = n >> 1;
	add(A,A + b,X);add(B,B + b,X);
}
int main(){
	int n;

}