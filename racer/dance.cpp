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
public:

    enum search_result: bool {success=true, failed=false};

protected:
    bool prepared;
    std::vector<scenarios> gen_nodes;
    std::vector<scenarios_pt> gen[N + 2];
    std::bitset<N + 2> compared[N + 2];
    scenarios_pt sche[N + 2];

    std::priority_queue<int, std::vector<int>, std::greater<int> > unselected;
    std::bitset<N + 2> not_vis;

    void generate()
    {
        static scenarios srs;
        if (!unselected.size()) {
            gen_nodes.push_back(srs);
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
            gen_nodes.push_back(srs);
            return ;
        }
        not_vis.reset(cur);
        for (i = cur + 1; i < N; i++) {
            if (not_vis[i]) {
                not_vis.reset(i);
                srs.push_back(std::move(std::make_pair(cur, i)));
                generate();
                not_vis.set(i);
                srs.pop_back();
                unselected.push(i);
            }
        }
        not_vis.set(cur);
        unselected.push(cur);
    }

    inline bool check (scenarios_pt scs_pt)
    {
        auto &scs = *scs_pt;
        for (auto pairs: scs) {
            if(compared[pairs.first][pairs.second])return false;
        }
        return true;
    }

    inline void sign (scenarios_pt scs_pt)
    {
        auto &scs = *scs_pt;
        for (auto pairs: scs) {
            compared[pairs.first][pairs.second] = true;
        }
    }

    inline void unsign (scenarios_pt scs_pt)
    {
        auto &scs = *scs_pt;
        for (auto pairs: scs) {
            compared[pairs.first][pairs.second] = false;
        }
    }

    search_result dfs(int rnd_cnt)
    {
        if (rnd_cnt == N) {
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
            if (dfs(nx_cnt)) {
                return search_result::success;
            }
            unsign(gen[rnd_cnt][i]);
            gen[nx_cnt].clear();
        }
        return search_result::failed;
    }
public:
    

    ScheduleGenerator()
    {
        prepared = false;
        
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
        gen[0].reserve(gen_nodes.size());
        for (int i = 0; i < gen_nodes.size(); i++) {
            gen[0].push_back(&gen_nodes[i]);
        }
        // for (auto scs: gen_nodes) {
        //     for(auto pairs: scs) {
        //         std::cout << "(" << pairs.first << ", " << pairs.second << ") ";
        //     }
        //     std::cout << std::endl;
        // }
    }

    scenarios_pt *run()
    {
        if (prepared) {
            return sche;
        }
        dfs(0);
        prepared = true;
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
    const int n = 4;
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