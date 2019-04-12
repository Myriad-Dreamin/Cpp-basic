#include <iostream>

#include <algorithm>
#include <vector>

# define bit_arr(_arr, _idx) (((_arr) >> ((_idx) << 2)) & 0xf)
# define set_arr(_arr, _idx, _x) (((_arr) & (~(0xf << ((_idx) << 2)))) | ((_x) << ((_idx) << 2)))
# define swap_bit_arr(_arr, _hi, _lo) (\
	(\
		(_arr) &\
		(~(\
			(0xf << ((_hi) << 2)) |\
			(0xf << ((_lo) << 2))\
		))\
	) |\
	(\
		(\
			((((_arr) >> ((_lo) << 2)) & 0xf) << ((_hi) << 2)) |\
			((((_arr) >> ((_hi) << 2)) & 0xf) << ((_lo) << 2))\
		)\
	)\
)

const int MAX_SIZE = 32;
const unsigned long long PERM_LONG = 0x0123456789abcdefLL;
int sche[MAX_SIZE+2][MAX_SIZE+2];
unsigned int bit_mask_check[1<<(MAX_SIZE>>1)];
std::vector<unsigned int> bit_mask[(MAX_SIZE>>1)+2];

std::string convert_binary (unsigned int x, int bit_count)
{
	if (bit_count == 0) {
		return std::string("");
	}
	std::string b(std::move(convert_binary(x >> 1, bit_count - 1)));
	b.push_back((x & 1) ? '1' : '0');
	return b;
}
std::vector<int> convert_permutation (unsigned long long x, int bit_count)
{
	if (bit_count == 0) {
		return std::vector<int>();
	}
	std::vector<int> p(std::move(convert_permutation(x >> 4, bit_count - 1)));
	p.push_back(x & 0xf);
	return p;
}
unsigned long long next_permutation (unsigned long long &x, int per_len)
{
	int hi = 1,lo = 0;
	for (; hi < per_len; hi++) {
		if(bit_arr(x, hi) < bit_arr(x, hi - 1))break;
	}
	if (hi == per_len) return x=-1;
	for (int idx = 0; idx < hi; idx++) {
		if(bit_arr(x, idx) < bit_arr(x, lo)) {
			lo = idx;
		}
	}
	printf("%d %d\n", hi, lo);
	x = swap_bit_arr(x, hi, lo);
	for (int idx = (hi >> 1) - 1; ~idx; idx--) {
		x = swap_bit_arr(x, idx, hi - 1 - idx);
	}
	return x;
}
void search_init (std::vector<unsigned int> bit_mask[])
{
	int binary_max = 1<<(MAX_SIZE>>1);
	for (int i = 0; i < binary_max; i++) {
		bit_mask_check[i] = bit_mask_check[i >> 1] + (i & 1);
		bit_mask[bit_mask_check[i]].emplace_back(i);
	}

	#ifdef DEBUG
	for(auto s: bit_mask[2]){
		cout << convert_binary(s, MAX_SIZE) << endl;
	}
	#endif

	return ;
}

void LCS(){
	static int dp[40][40],n=30,m=30;
	const char s[]="123", t[]="13";
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(s[i] == t[j]){
				dp[i][j] = dp[i-1][j-1]+1;
			}else {
				dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
			}
		}
	}
}

void search(int m){
	// max is 16
	unsigned long long perm = PERM_LONG >> (64-(m<<1));
	do {
		auto vecp = convert_permutation(perm, m>>1);
		for (auto s: vecp) {
			std::cout << s << " ";
		}
		std::cout << std::endl;
	}while(~next_permutation(perm, m>>1));
	return ;
}
int main()
{
	using std::cout;
	using std::endl;
	search_init(bit_mask);
	search(8);
	return 0;
}