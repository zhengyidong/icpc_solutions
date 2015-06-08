//  multiple-sp

#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

const int MAX_Q = 1000;
int query[MAX_Q];
int _q;
int ans[MAX_Q];
const int MAX_N = 1000;
int dist[MAX_N];
int g[MAX_N][MAX_N];
const int INF = 1 << 29;
void dijkstra(int s, int n){
    for(int i=0; i<n; ++i) dist[i] = INF;
    bool known[MAX_N] = {false};
    dist[s] = 0;

    for(int i=0; i<n; ++i){
        int min_v = -1;
        int min_dist = INF;
        for(int j=0; j<n; ++j){
            if(!known[j] && dist[j] < min_dist){
                min_dist = dist[j];
                min_v = j;
            }
        }
        for(int j=0; j<n; ++j){
            if(!known[j] && g[min_v][j] != INF && dist[min_v] + g[min_v][j] < dist[j]){
                dist[j] = dist[min_v] + g[min_v][j];
            }
        }
        known[min_v] = true;
    }
}

void bfs(int s, int t, int n){
    bool in_q[MAX_N];
    bool on_shortest[MAX_N];
    bool visited[MAX_N][MAX_N];
    memset(ans, 0, sizeof(ans));
    memset(in_q, false, sizeof(in_q));
    memset(visited, false, sizeof(visited));
    memset(on_shortest, false, sizeof(on_shortest));
    std::queue<int> q;
    q.push(t);
    in_q[t] = true;
    on_shortest[s] = true;
    on_shortest[t] = true;

    while(!q.empty()){
        int now = q.front(); q.pop();
        in_q[now] = false;
        for(int i=0; i<n; ++i){
            if(!visited[i][now] && dist[i] != INF && g[i][now] != INF && dist[i] + g[i][now] == dist[now]){
                on_shortest[i] = true;
                visited[i][now] = visited[now][i] = true;
                for(int j=0; j<_q; ++j){
                    if(query[j] >= dist[i] + 1 && query[j] < dist[now]){
                        ++ans[j];
                    }
                }

                if(!in_q[i]){
                    q.push(i);
                    in_q[i] = true;
                }
            }
        }
    }
    for(int i=0; i<n; ++i){
        for(int j=0; j<_q; ++j){
            if(on_shortest[i] && query[j] == dist[i]) ++ans[j];
        }
    }
}

int main(){
    int n, m, S, T;
    bool first = true;
    while(scanf("%d%d%d%d", &n, &m, &S, &T) != EOF){
        if(!first) printf("\n");
        else first = false;

        --S; --T;
        for(int i=0; i<n; ++i)
            for(int j=0; j<n; ++j){
                if(i == j) g[i][j] = 0;
                else g[i][j] = INF;
            }

        for(int i=0; i<m; ++i){
            int s, e, t;
            scanf("%d%d%d", &s, &e, &t);
            --s; --e;
            g[s][e] = g[e][s] = t;
        }

        dijkstra(S, n);

        scanf("%d", &_q);
        for(int i=0; i<_q; ++i) scanf("%d", &query[i]);

        bfs(S, T, n);

        for(int i=0; i<_q; ++i){
            if(query[i] >= dist[T] || query[i] == 0) printf("1\n");
            else printf("%d\n", ans[i]);
        }
    }
    return 0;
}
