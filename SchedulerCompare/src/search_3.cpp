
#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>

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
protected:
    /* 当前选到了第cur_sel个情况 */
    int cur_sel = 0, Nsub1 = N - 1;

    /* compared[x][y]表示x与y是否已较量过 */
    std::bitset<N + 2> compared[N + 2];
    /* 答案数组 */
    scenarios sche[N + 2];

    /* 用于生成, 当前还有哪些人没选 */
    std::priority_queue<int, std::vector<int>, std::greater<int> > unselected;
    /* 用于生成, 当前还有哪些人没选 */
    std::bitset<N + 2> not_vis;

    /* 检测 */
    inline bool check (scenarios &scs)
    {
        for (auto pairs: scs) {
            if(compared[pairs.first][pairs.second]) {
                return false;
            }
        }
        return true;
    }

    /* 标记 */
    inline void sign (scenarios &scs)
    {
        for (auto pairs: scs) {
            compared[pairs.first][pairs.second] = true;
        }
    }

    /* 生成 */
    void generate ()
    {
        /* 用于生成, 可回溯的情况数组 */
        static scenarios srs;

        if(cur_sel == Nsub1) return ;
        if (!unselected.size()) {
            if(check(srs)){
                sign(srs);
                sche[cur_sel++] = srs;
            }
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
            if(check(srs)){
                sign(srs);
                sche[cur_sel++] = srs;
            }
            return ;
        }
        
        /* 回溯 */
        // unselected在之前已经pop过
        not_vis.reset(cur);
        for (i = cur + 1; i < N; i++) {
            if (not_vis[i]) {

                not_vis.reset(i);
                srs.push_back(std::move(std::make_pair(cur, i)));
                
                generate();
                if(cur_sel == Nsub1) return ;
                
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

public:
    ScheduleGenerator ()
    {
        // generate inc_heap
        std::vector<int> inc_arr;
        inc_arr.reserve(N);
        for (int i = 0; i < N; i++){
            inc_arr.push_back(i);
        }
        unselected = std::move(
            decltype(unselected)(inc_arr.begin(), inc_arr.end())
        );
        inc_arr.clear();

        // all node is not visited
        not_vis.set();

        generate();
    }

    scenarios_pt run ()
    {
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
    
    const int n = 20;

    auto beg = clock();
    ScheduleGenerator<n> scheduler;
    auto sche_res = scheduler.run();
    std::cout << clock() - beg << "ms" << std::endl;
    
    int **sche = new int*[n];
    for (int i = 0; i < n; i++) {
        sche[i] = new int[n];
        sche[0][i] = i;
    }

    for (int i = 1; i < n; i++) {
        auto &scs = sche_res[i - 1];
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