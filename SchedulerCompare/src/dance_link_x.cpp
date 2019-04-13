#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include <cstring>

class DanceLinkX
{
private:
    int n, m;

    std::vector<int> R, L, U, D, H, S;
    std::vector<int> row, col;

public:
    int res;
    std::vector<int> ans;
    //初始化函数
    void init (int x,int y)
    {
        R.clear();
        L.clear();
        U.clear();
        D.clear();
        H.clear();
        S.clear();
        row.clear();
        col.clear();
        
        n = x;
        m = y;

        // init vector
        S   = std::move(std::vector<int>(m + 1, 0));
        col = std::move(std::vector<int>(m + 1, 0));
        row = std::move(std::vector<int>(m + 1, 0));
        U.reserve(m);
        D.reserve(m);
        L.reserve(m);
        R.reserve(m);
        H.reserve(n);
        for (int i = 0; i <= m; i++) {

            U.push_back(i);
            D.push_back(i);
            L.push_back(i - 1);
            R.push_back(i + 1);
        }
        for (int i = 0; i <= n; i++) {
            H.push_back(-1);
        }
        L[0]=m;
        R[m]=0;
    }

    void link (int r,int c)
    {
        ++S[c];


        // insert U-D
        U.push_back(c);
        D.push_back(D[c]);
        U[D[c]] = row.size();
        D[c] = row.size();
        
        // insert L-R
        if(~H[r])
        {
            L.push_back(H[r]);
            R.push_back(R[H[r]]);
            L[R[H[r]]]=row.size();
            R[H[r]]=row.size();
        }
        else
        {
            H[r]=row.size();
            L.push_back(row.size());
            R.push_back(row.size());
        }

        col.push_back(c);
        row.push_back(r);
    }

    void remove (int c)
    {
        R[L[c]]=R[c];
        L[R[c]]=L[c];
        for(int x = D[c]; x != c; x = D[x]) {
            for(int y = R[x]; y != x; y = R[y]) {
                D[U[y]] = D[y];
                U[D[y]] = U[y];
                S[col[y]]--;
            }
        }
    }

    void resume (int c)
    {
        for (int x = U[c]; x != c; x = U[x]) {
            for(int y = L[x]; y != x; y = L[y]) {
                U[D[y]] = D[U[y]] = y;
                S[col[y]]++;
            }
        }
        L[R[c]] = R[L[c]] = c;
    }

    bool dance (int cnt)
    {
        static int ff = 0;
        if( ++ff % 100000 == 0) {
            std::cout << ff << std::endl;
        } 
        if (R[0] == 0) {
            res = cnt;
            return true;
        }
        int cur;
        cur = R[0];
        for (int i = cur; i != 0; i = R[i]){
            if (S[cur] > S[i]) {
                cur = i;
            }
        }

        remove(cur);

        for (int i = D[cur]; i != cur; i = D[i]) {
            ans.push_back(row[i]);

            for (int j = R[i]; j != i; j = R[j]) {
                remove(col[j]);
            }
            
            if(dance(cnt+1))
            {
                return true;
            }

            for (int j = L[i]; j != i; j = L[j]){
                resume(col[j]);
            }
            ans.pop_back();
        }

        resume(cur);
        return false;
    }
    void cr ()
    {
        for (int i = R[0]; i != 0; i = R[i]) {
            if (S[i] == 0) {
                remove(i);
            }
        }
    }
};
DanceLinkX g;
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
    int n;
    std::cin >> n;
    if (n & 1) {
        n++;
    }
    auto beg = clock();
    int npow2 = n * n, nsub1 = n - 1, node_cnt =  (n >> 1) * nsub1 * nsub1;
    g.init(node_cnt, npow2*3);
    int rc[node_cnt+2],row=0;
    for (int i = 0; i < nsub1; i++) {
        for (int j = 0; j < n; j++) {
            for (int val = j + 1; val < n; val++) {
                int node_cnt = i * npow2 + j * n + val;
                rc[++row] = node_cnt;
                // (j, val), (val, j) col 0 ~ n * (n - 1) + n - 1 = n^2 - 1
                g.link(row, j * n + val + 1);
                g.link(row, j + val * n + 1);
                // row (i, val) (i, j)
                g.link(row, npow2 + i * n + val + 1);
                g.link(row, npow2 + i * n + j + 1);
            }
        }
    }
    g.cr();
    g.dance(0);
    std::cout << clock() - beg << "ms" << std::endl;
    int **sche = new int*[n];
    for (int i = 0; i < n; i++) {
        sche[i] = new int[n];
        memset(sche[i], 0 , n << 2);
    }
    for (int i = 0; i < n; i++) {
        sche[0][i] = i;
    }
    for (int i = 0; i < g.res; i++) {
        int row = rc[g.ans[i]]/npow2 + 1, col = (rc[g.ans[i]]/n)%n , val = rc[g.ans[i]]%n;
        sche[row][col] = val;
        sche[row][val] = col;
    }
    schedule_print(sche, n);
    for (int i = 0; i < n; i++) {
        delete[] sche[i];
    }
    delete[] sche;
    return 0;
}

