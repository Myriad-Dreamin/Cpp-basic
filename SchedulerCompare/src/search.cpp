
#include <iostream>
#include <cstring>
#include <iomanip>

#include <queue>
#include <bitset>
#include <vector>
#include <utility>
#include <stdexcept>


/* 定义一场比赛为两个编号的pair */
typedef std::pair<int, int> round;

/* 定义一种可能的情况为round的数组 */
typedef std::vector<round> scenarios;
typedef scenarios *scenarios_pt;

template<int N>
class ScheduleGenerator
{
public:

    enum search_result: bool {success=true, failed=false};

protected:
    bool prepared;
    /* 所有可能的情况 */
    std::vector<scenarios> gen_nodes;
    
    /* 分为N阶段的情况指针数组 */
    std::vector<scenarios_pt> gen[N + 2];
    
    /* compared[x][y]表示x与y是否已较量过 */
    std::bitset<N + 2> compared[N + 2];
    /* 答案数组 */
    scenarios_pt sche[N + 2];

    /* 用于生成, 当前还有哪些人没选 */
    std::priority_queue<int, std::vector<int>, std::greater<int> > unselected;
    /* 用于生成, 当前还有哪些人没选 */
    std::bitset<N + 2> not_vis;

    /* 生成 */
    void generate ()
    {
        /* 用于生成, 可回溯的情况数组 */
        static scenarios srs;
        
        if (!unselected.size()) {
            gen_nodes.push_back(srs);
            return ;
        }
        
        /* 从unseleted中取出一个未选择的编号 */
        int cur = -1, i;
        while (unselected.size()) {
            i = unselected.top(); unselected.pop();
            if (not_vis[i]) {
                cur = i;
                break;
            }
        }
        if (cur == -1) {
            gen_nodes.push_back(srs);
            return ;
        }
        
        /* 回溯 */
        // unselected在之前已经pop过
        not_vis.reset(cur);
        for (i = cur + 1; i < N; i++) {
            if (not_vis[i]) {

                srs.push_back(std::move(std::make_pair(cur, i)));
                not_vis.reset(i);
                
                generate();
                
                // 此时i一定不在unseleted中
                unselected.push(i);
                not_vis.set(i);
                srs.pop_back();
                
            }
        }
        not_vis.set(cur);
        // 此时cur一定不在unseleted中
        unselected.push(cur);
    }

    /* 检测 */
    inline bool check (scenarios_pt scs_pt)
    {
        auto &scs = *scs_pt;
        for (auto pairs: scs) {
            if(compared[pairs.first][pairs.second]) {
                return false;
            }
        }
        return true;
    }

    /* 标记 */
    inline void sign (scenarios_pt scs_pt)
    {
        auto &scs = *scs_pt;
        for (auto pairs: scs) {
            compared[pairs.first][pairs.second] = true;
        }
    }

    /* 取消标记 */
    inline void unsign (scenarios_pt scs_pt)
    {
        auto &scs = *scs_pt;
        for (auto pairs: scs) {
            compared[pairs.first][pairs.second] = false;
        }
    }

    /* 深度优先搜索 */
    search_result dfs (int rnd_cnt)
    {
    	static int Nsub1 = N - 1;

        if (rnd_cnt == Nsub1) {
            return search_result::success;
        }

        int nx_cnt = rnd_cnt + 1;
        for (int i = 0; i < gen[rnd_cnt].size(); i++) {
            sche[rnd_cnt] = gen[rnd_cnt][i];
            
            sign(gen[rnd_cnt][i]);
            for (int j = i + 1; j < gen[rnd_cnt].size(); j++) {
                if (check(gen[rnd_cnt][j])) {
                    gen[nx_cnt].push_back(gen[rnd_cnt][j]);
                }
            }

            if (dfs(nx_cnt) == search_result::success) {
                return search_result::success;
            }

            gen[nx_cnt].clear();
            unsign(gen[rnd_cnt][i]);
        }
        
        return search_result::failed;
    }

public:
    ScheduleGenerator ()
    {
        prepared = false;

        // generate inc_heap
        std::vector<int> inc_arr;
        inc_arr.reserve(N);
        for (int i = 0; i < N; i++) {
            inc_arr.push_back(i);
        }
        unselected = std::move(
            decltype(unselected)(inc_arr.begin(), inc_arr.end())
        );
        inc_arr.clear();

        // all node is not visited
        not_vis.set();

        generate();

        gen[0].reserve(gen_nodes.size());
        for (int i = 0; i < gen_nodes.size(); i++) {
            gen[0].push_back(&gen_nodes[i]);
        }
    }

    scenarios_pt *run ()
    {
        if (prepared) {
            return sche;
        }
        dfs(0);
        prepared = true;
        return sche;
    }
};

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

int main ()
{
    std::ios::sync_with_stdio(false);
    
    const int n = 18;

    ScheduleGenerator<n> scheduler;
    auto sche_res = scheduler.run();
    
    int **sche = new int*[n];
    for (int i = 0; i < n; i++) {
        sche[i] = new int[n];
        sche[0][i] = i;
    }

    for (int i = 1; i < n; i++) {
        auto &scs = *sche_res[i - 1];
        for (auto pairs: scs) {
            sche[i][pairs.first] = pairs.second;
            sche[i][pairs.second] = pairs.first;
        }
    }

    schedule_print(sche, n);

    for (int i = 0; i < n; i++) {
        delete[] sche[i];
    }
    delete[] sche;
    
    return 0;
}