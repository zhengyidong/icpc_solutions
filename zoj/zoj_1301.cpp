#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <bitset>

using namespace std;

int r, d, ss;
int g[10][10];
int swit[10][10];
bool visited[10][1024];

struct state{
    state(int step=0, int pos=0):
        step(step),pos(pos), on(1), first(true){}
    int step;
    int pos;
    bitset<10> on;
    bool first;
    int type; // 0: move, 1: turn
    int val;
};

state pre[10][1024];



int bfs(){
    queue<state> q;

    q.push(state(0, 0));
    while(!q.empty()){
        state cur = q.front(); q.pop();
        if(cur.pos == r - 1 && cur.on.to_ulong() == (1 << (r-1))){
            return cur.step;
        }

        for(int i=0; i<r; ++i){
            state old_cur = cur;
            if(cur.pos == i) continue;
            cur.on.flip(i);
            ++cur.step;
            if(swit[cur.pos][i] && !visited[cur.pos][cur.on.to_ulong()]){
                visited[cur.pos][cur.on.to_ulong()] = true;
                if(pre[cur.pos][cur.on.to_ulong()].first){
                    pre[cur.pos][cur.on.to_ulong()] = old_cur;
                    if(cur.on[i])
                        pre[cur.pos][cur.on.to_ulong()].type = 2;
                    else
                        pre[cur.pos][cur.on.to_ulong()].type = 1;
                    pre[cur.pos][cur.on.to_ulong()].val = i;
                    pre[cur.pos][cur.on.to_ulong()].first = false;
                }
                q.push(cur);
            }
            cur.on.flip(i);
            --cur.step;
        }
        for(int i=0; i<r; ++i){
            state old_cur = cur;
            if(cur.pos == i || !g[cur.pos][i] || !cur.on[i]) continue;
            int tmp_pos = cur.pos;
            cur.pos = i;
            ++cur.step;
            if(!visited[i][cur.on.to_ulong()]){
                if(pre[cur.pos][cur.on.to_ulong()].first){
                    pre[cur.pos][cur.on.to_ulong()] = old_cur;
                    pre[cur.pos][cur.on.to_ulong()].first = false;
                    pre[cur.pos][cur.on.to_ulong()].val = i;
                    pre[cur.pos][cur.on.to_ulong()].type = 0;
                }
                visited[i][cur.on.to_ulong()] = true;
                q.push(cur);
            }
            cur.pos = tmp_pos;
            --cur.step;
        }

    }

    return -1;
}

int main(){
    int num_case = 1;
    while(scanf("%d%d%d", &r, &d, &ss) != EOF && (r || d || ss)){
        memset(g, 0, sizeof(g));
        memset(swit, 0, sizeof(swit));
        memset(visited, false, sizeof(visited));
        for(int i=0; i<10; ++i)
            for(int j=0; j<1024; ++j) pre[i][j].first = true;

        int s, e;
        for(int i=0; i<d; ++i){
            scanf("%d%d", &s, &e);
            g[s-1][e-1] = g[e-1][s-1] = 1;
        }
        for(int i=0; i<ss; ++i){
            scanf("%d%d", &s, &e);
            swit[s-1][e-1] = 1;
        }

        int ans = bfs();
        int val[10240];
        int type[10240];
        int cnt = ans - 1;

        printf("Villa #%d\n", num_case++);
        if(ans == -1){
            printf("The problem cannot be solved.\n");
        }
        else{
            printf("The problem can be solved in %d steps:\n", ans);
            state st = pre[r-1][(1 << (r-1))];
            type[cnt] = st.type;
            val[cnt] = st.val;
            --cnt;
            while(st.pos != 0 || st.on.to_ulong() != 1){
                st = pre[st.pos][st.on.to_ulong()];
                type[cnt] = st.type;
                val[cnt] = st.val;
                --cnt;
            }
            for(int i=0; i<ans; ++i){
                if(type[i] >= 1){
                    printf("- Switch %s light in room %d.\n",
                           type[i] == 2 ? "on":"off", val[i] + 1);
                }
                else
                    printf("- Move to room %d.\n", val[i] + 1);
            }
        }
        printf("\n");
    }
    return 0;
}
