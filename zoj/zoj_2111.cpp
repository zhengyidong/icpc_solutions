#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int g[101][101];
int P[101];
int bug[101];
bool visited[101];
int N, M;
int max_pos;

void dfs(int v, int cur_man, int cur_val){
    if(bug[v] > cur_man * 20 || cur_man == 0) return;

    cur_man -= (bug[v] + 19) / 20;
    cur_val += P[v];
    if(cur_val > max_pos) max_pos = cur_val;
    for(int i=1; i<=N; ++i){
        if(!visited[i] && g[v][i] && bug[i] <= cur_man * 20){
            visited[i] = true;
            dfs(i, cur_man, cur_val);
            visited[i] = false;
        }
    }
}

int main(){
    while(scanf("%d%d", &N, &M) != EOF && (N != -1 || M != -1)){
        max_pos = 0;
        memset(g, 0, sizeof(g));
        memset(visited, false, sizeof(visited));
        for(int i=1; i<=N; ++i) scanf("%d%d", &bug[i], &P[i]);
        for(int i=0; i<N-1; ++i){
            int s, e;
            scanf("%d%d", &s, &e);
            g[s][e] = g[e][s] = 1;
        }
        visited[1] = true;
        dfs(1, M, 0);
        printf("%d\n", max_pos);
    }
    return 0;
}

