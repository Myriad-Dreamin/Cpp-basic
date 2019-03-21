#include <cstdio>
#include <algorithm>
using namespace std;
const int bufsz = 20;
struct ts{
	int key,id;
	bool operator==(const ts &b){return b.id==id;}
}B[bufsz];
int partition(ts *A,int len){
	ts m=A[0];
	int x=0,l=0,r;
	for(int j=0;j<len;j++){
		if(A[j].key<m.key)x++;
		else if (A[j].key==m.key){
			x++;
			swap(A[j],m);
		}
	}
	r=x;
	for(int j=0;j<len;j++){
		if(A[j]==m)continue;
		if(A[j].key<=m.key)B[l++]=A[j];
		else B[r++]=A[j];
	}
	B[l]=m;
	for(int j=0;j<len;j++)A[j]=B[j];
	return x;
}
int main(){
	ts A[20] = {{3,0}, {3,1}, {4,2}, {1,3}, {5,4}, {3,5}, {5,6}, {4,7}, {1,8}, {5,9}, {1,10}, {1,11}, {1,12}};
	printf("%d\n",partition(A, 12));
	for(int i=0;i<10;i++){
		printf("{%d,%d} ",A[i].key, A[i].id);
	}
	puts("");
}