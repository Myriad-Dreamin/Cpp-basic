#include <iostream>
#include <bitset>
#include <vector>
#include <utility>
#include <cstring>
#include <queue>
#include <stdexcept>

typedef std::pair<int, int> racer;
typedef std::vector<racer> scenarios;
typedef scenarios *scenarios_pt;

template<int N>
class ScheduleGenerator
{
protected:
    int cur_sel = 0, Nsub2 = N - 2, totcnt = 0;
    std::bitset<N + 2> compared[N + 2];
    scenarios sche[N + 2];

    std::priority_queue<int, std::vector<int>, std::greater<int> > unselected;
    std::bitset<N + 2> not_vis;


    inline bool check (scenarios &scs)
    {
        for (auto pairs: scs) {
            if(compared[pairs.first][pairs.second]) {
                return false;
            }
        }
        return true;
    }

    inline void sign (scenarios &scs)
    {
        for (auto pairs: scs) {
            compared[pairs.first][pairs.second] = true;
        }
    }

    void generate ()
    {
        static scenarios srs;
        if(cur_sel == Nsub2) return ;
        if (!unselected.size()) {
            totcnt++;
            if(check(srs)){
                sign(srs);
                sche[cur_sel++] = srs;
            }
            return ;
        }
        int cur = -1, i;
        while (unselected.size()) {
            i = unselected.top(); unselected.pop();
            if (not_vis[i]) {
                cur = i;
                break;
            }
        }
        if (cur == -1) {
            totcnt++;
            if(check(srs)){
                sign(srs);
                sche[cur_sel++] = srs;
            }
            return ;
        }
        not_vis.reset(cur);
        for (i = cur + 1; i < N; i++) {
            if (not_vis[i]) {
                not_vis.reset(i);
                srs.push_back(std::move(std::make_pair(cur, i)));
                generate();
                if(cur_sel == Nsub2) return ;
                not_vis.set(i);
                srs.pop_back();
                unselected.push(i);
            }
        }
        not_vis.set(cur);
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

        scenarios scs;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                if(!compared[i][j]) {
                    compared[i][j] = true;
                    scs.push_back(std::move(std::make_pair(i, j)));
                }
            }
        }
        sche[N - 2] = std::move(scs);

        std::cout << "searched " << totcnt << std::endl;
    }

    scenarios_pt run()
    {
        return sche;
    }
};

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
    const int n = 6v   
    ;
    ScheduleGenerator<n> scheduler;
    auto sche_res = scheduler.run();
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