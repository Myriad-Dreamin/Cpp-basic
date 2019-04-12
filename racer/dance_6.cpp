#include <bits/stdc++.h>
using namespace std;

int n, npow2, curer=0;
class dlx
{
public:

    //实际行列数，实际节点数
    int n,m,size;

    //分别表示每个节点的右边结点，左边，上边，下边；节点所在列，结点所在行头节点，结点所在行，每一列的1的数量
    vector<int> R,L,U,D,col,H,row,S;

    //表示最后选中的行的数量，ans记录答案
    int res,ans[60*60*60];

    //初始化函数
    void init(int x,int y)
    {
        R.clear();
        L.clear();
        U.clear();
        D.clear();
        H.clear();
        S.clear();
        row.clear();
        col.clear();
        //行列数记录
        n=x;
        m=y;
        int i;
        S.reserve(m);
        U.reserve(m);
        D.reserve(m);
        L.reserve(m);
        R.reserve(m);
        H.reserve(n);
        //数组的初始化
        for(i=0;i<=m;i++)
        {
            //每一列的1的数量初始化为0
            S.push_back(0);
            col.push_back(0);
            row.push_back(0);

            //由于已知只有第一行，故上下邻接点都是自己
            U.push_back(i);
            D.push_back(i);

            //左右邻接点
            L.push_back(i - 1);
            R.push_back(i + 1);
        }
        //使得第一行成为一个环
        L[0]=m;
        R[m]=0;

        //目前最大结点数为行数
        size=m;

        //头节点，由于没有数据输入，故初始化为一个取不到的数
        for(i=0;i<=n;i++)
        {
            H.push_back(-1);

        }
    }

    //用于把每一个新加入的结点添加到已知的表中，r为行标号，c为列标号
    void link(int r,int c)
    {
        // printf("%d %d\n",r, c);
        //首先节点数+1，当前节点编号为size，当前节点所在列为c，且所在列1的数量+1
        ++S[c];++size;
        col.push_back(c);
        row.push_back(r);


        //竖直方向，头插法，即把新加入的结点插入到列头节点之后一个的位置，改变邻接关系完成插入操作
        U.push_back(c);
        D.push_back(D[c]);
        U[D[c]] = size;
        D[c] = size;

        //水平方向，
        //如果是该行第一个，则把该节点作为这一行头节点
        if(H[r]<0)
        {
            //自己连成环
            L.push_back(size);
            R.push_back(size);
            H[r]=size;
        }
        //否则，同样头插法，把当前节点插入到行头节点之后（右边）一位，改变邻接关系，可以带入含义方便理解
        else
        {
            L.push_back(H[r]);
            R.push_back(R[H[r]]);
            L[R[H[r]]]=size;
            R[H[r]]=size;
            //row[size]=r;
        }
    }

    //删除结点c
    //删除节点c，以及c上下节点所在的行,每次调用这个函数，
    //都是从列头节点开始向下删除，这里c也可以理解为第c列
    void remove(int c)
    {
        //把列头节点删掉（改变邻接关系，c左边的直接连到右边，在遍历时由于找不到所以移除）
        R[L[c]]=R[c];
        L[R[c]]=L[c];
        int x,y;
        //c的上下结点怎么找呢？因为行列都是环，所以一直找就好了，找到起点就是完整的一圈
        //由于只有结点才加入表，所以竖直找到的都是结点
        for(x=D[c];x!=c;x=D[x])
        {
            //删除所在行，只要删除行上面的结点，也就认为删除了行
            for(y=R[x];y!=x;y=R[y])
            {
                //移除行结点的列方面的连接，即删除行，因为遍历不到了
                D[U[y]]=D[y];
                U[D[y]]=U[y];
                S[col[y]]--;
            }
        }
    }

    //恢复节点c,以及c上下节点所在的行(同上，也可以理解为从第c列的头节点开始恢复
    void resume(int c)
    {
        int i,j;
        //从头节点开始
        for(i=U[c];i!=c;i=U[i])
        {
            //对于同一行的每一个，恢复上下邻接关系
            for(j=L[i];j!=i;j=L[j])
            {
                U[D[j]]=j;
                D[U[j]]=j;
                S[col[j]]++;
            }
        }
        //对于列头节点，删除的时候只改变了c左右的连接情况，c的没改变，所以把c的信息作为起点，恢复邻接
        //c左边的右边和右边的左边都是自己
        L[R[c]]=R[L[c]]=c;
    }

    //实现主程
    bool dance(int cnt)//cnt表示递归深度
    {
        curer++;
        if(curer % 100000 == 0) {
            printf("%d\n",curer);
        }
        //当原点的右边结点是自己时，所有的已经全部删除完毕，符合条件，结束，找到结果
        if(R[0]==0)
        {
            res=cnt;
            return true;
        }
        int cur;
        cur=R[0];
        //找到一个结点数最小的
        for(int i=cur;i!=0;i=R[i])
        {
            if(S[cur]>S[i])
            {
                cur=i;
            }
        }
        remove(cur);//找到节点数最少的列，当前元素不是原图上0，1的节点，而是列头节点，删除
        int i,j;

        //对于每一行
        for(i=D[cur];i!=cur;i=D[i])
        {
            //假设当前行就是选中的答案，即使不是也无所谓，找到正确答案的时候会覆盖掉原来的值
            ans[cnt]=row[i];

            //删除列上面的结点及其所在的行，保证那些行不会被选中而造成同一列有多个1
            for(j=R[i];j!=i;j=R[j])
            {

                remove(col[j]);
            }
            //对删除完毕的矩阵递归操作，成功，则返回true
            if(dance(cnt+1))
            {
                return true;
            }

            //矩阵恢复
            for(j=L[i];j!=i;j=L[j])
            {
                resume(col[j]);
            }
        }
        resume(cur);
        return false;
    }
    void cr()
    {
        for (int i = R[0];i!=0;i=R[i]) {
            if(S[i] == 0) {
                remove(i);
            }
        }
    }
};
dlx g;
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
    cin >> n;
    npow2 = n * n;
    int nsub1 = n - 1;
    int rr;
    for (int i = 0; i < nsub1; i++) {
        for (int j = 0; j < n; j++) {
            for (int val = j + 1; val < n; val++) {
                    rr++;
            }}}
    g.init(rr, npow2*3);
    printf("%d %d\n",rr, npow2*3);
    int rc[rr+2],row=0;
    for (int i = 0; i < nsub1; i++) {
        for (int j = 0; j < n; j++) {
            for (int val = j + 1; val < n; val++) {
                int rrr = i * npow2 + j * n + val;
                rc[++row] = rrr;
                // (i, j, val), (i, val, j) col 0 ~ n * (n - 1) + n - 1 = n^2 - 1
                g.link(row, j * n + val + 1);
                g.link(row, j + val * n + 1);
                // row (i, val) (i, j)
                g.link(row, npow2 + i * n + val + 1);
                g.link(row, npow2 + i * n + j + 1);
                // col (j, val), (val, j)
                g.link(row, npow2 * 2 + j * n + val + 1);
                g.link(row, npow2 * 2 + val * n + j + 1);
            }
        }
    }
    g.cr();
    g.dance(0);
    int **sche = new int*[n];
    for (int i = 0; i < n; i++) {
        sche[i] = new int[n];
        memset(sche[i], 0 , n << 2);
    }
    for (int i = 0; i < n; i++) {
        sche[0][i] = i;
    }
    for (int i = 0; i < g.res; i++) {
        sche[rc[g.ans[i]]/npow2 + 1][(rc[g.ans[i]]/n)%n] = rc[g.ans[i]]%n;
        sche[rc[g.ans[i]]/npow2 + 1][rc[g.ans[i]]%n] = (rc[g.ans[i]]/n)%n;
    }
    schedule_print(sche, n);
    for (int i = 0; i < n; i++) {
        delete[] sche[i];
    }
    delete[] sche;
    return 0;
}

