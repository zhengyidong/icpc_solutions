#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 6000;

struct edge{
    int x;
    int y;
    int nxt;
}e[MAX_N + 1];

int head[MAX_N + 1];
int dp[MAX_N + 1][2];
int conv[MAX_N + 1];
int ne;

void add_edge(int x, int y){
    e[ne].x = x; e[ne].y = y;
    e[ne].nxt = head[x]; head[x] = ne++;
}

int dfs(int v){
    dp[v][0] = 0;
    dp[v][1] = conv[v];
    for(int cur=head[v]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        dfs(y);
        dp[v][0] += max(dp[y][0], dp[y][1]);
        dp[v][1] += dp[y][0];
    }
    return max(dp[v][0], dp[v][1]);
}

int main(){
    int N;
    int root = 0;
    int tmp_root[MAX_N + 1];
    while(scanf("%d", &N) != EOF){
        ne = 0;
        memset(dp, 0, sizeof(dp));
        memset(tmp_root, 0, sizeof(tmp_root));
        memset(head, -1, sizeof(head));
        for(int i=1; i<=N; ++i) scanf("%d", &conv[i]);
        int s, e;
        while(scanf("%d%d", &s, &e) != EOF && (s != 0 || e != 0)){
            tmp_root[s] = 1;
            add_edge(e, s);
        }
        for(int i=1; i<=N; ++i){
            if(tmp_root[i] == 0){
                root = i;
                break;
            }
        }
        printf("%d\n", dfs(root));
    }
    return 0;
}

