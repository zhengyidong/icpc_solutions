#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_N = 10005;

struct edge{
    int x;
    int y;
    int c;
    int nxt;
}e[2 * MAX_N + 1];

int head[2 * MAX_N + 1];
int ne;
int N;
int dp[MAX_N + 1][3];
// 0 for max from chidren, 1 for 2nd-max from children, 2 for max from father
bool visited[MAX_N + 1];

void add_edge(int x, int y, int c){
    e[ne].x = x; e[ne].y = y; e[ne].c = c;
    e[ne].nxt = head[x]; head[x] = ne++;

    e[ne].x = y; e[ne].y = x; e[ne].c = c;
    e[ne].nxt = head[y]; head[y] = ne++;
}

void dfs_children(int v){
    visited[v] = true;
    for(int cur=head[v]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        int c = e[cur].c;
        if(!visited[y]){
            dfs_children(y);
            if(dp[y][0] + c > dp[v][0]){
                dp[v][1] = dp[v][0];
                dp[v][0] = dp[y][0] + c;
            }
            else if(dp[y][0] + c > dp[v][1]){
                dp[v][1] = dp[y][0] + c;
            }
        }
    }
}

void dfs_father(int v){
    visited[v] = true;
    for(int cur=head[v]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        int c = e[cur].c;
        if(!visited[y]){
            dp[y][2] = max(dp[v][2], dp[v][0] == c + dp[y][0] ? dp[v][1] : dp[v][0])+ c;
            dfs_father(y);
        }
    }
}

int main(){
    while(scanf("%d", &N) != EOF){
        int e, c;
        ne = 0;
        memset(dp, 0, sizeof(dp));
        memset(head, -1 ,sizeof(head));
        memset(visited, false, sizeof(visited));
        for(int i=2; i<=N; ++i){
            scanf("%d%d", &e, &c);
            add_edge(i, e, c);
        }

        dfs_children(1);

        dp[1][2] = 0;

        memset(visited, false, sizeof(visited));
        dfs_father(1);

        for(int i=1; i<=N; ++i){
            printf("%d\n", max(dp[i][0], dp[i][2]));
        }

    }
    return 0;
}

