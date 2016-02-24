#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <cmath>

using namespace std;

const int MAX_N = 50001;
const int INF = 1 << 29;

int dist[MAX_N];
int R[MAX_N], L[2 * MAX_N], intime[MAX_N], outtime[MAX_N], E[2 * MAX_N];
int dp[2*MAX_N][17];

int ne = 0;
int cnte, cntin, cntout;

struct edge
{
    int x;
    int y;
    int c;
    int nxt;
}g[2 * MAX_N];

int head[2 * MAX_N];
void add_edge(int x, int y, int c){
    // add an arc(x <-> y, c); vertex: 0 ~ n-1;

    g[ne].x = x; g[ne].y = y; g[ne].c = c;
    g[ne].nxt = head[x]; head[x] = ne++;

    g[ne].x = y; g[ne].y = x; g[ne].c = c;
    g[ne].nxt = head[y]; head[y] = ne++;
}
void st(){
    for(int i=0; i<cnte; ++i)
        dp[i][0] = i;
    int m=(int)(log(1.0*cnte) / log(2.0));
    for(int j=1; j<=m; ++j){
        for(int i=0; i<cnte; ++i){
            dp[i][j] = dp[i][j-1];
            int k = 1 << (j-1);
            int a1 = dp[i][j-1];
            if(i + k < cnte){
                int a2 = dp[i+k][j-1];
                if(L[a1] > L[a2])
                    dp[i][j] = a2;
            }
        }
    }
}
int rmq(int l, int r){
    if(r < l) std::swap(r, l);
    int k = (int)(log(1.0*(r-l+1)) / log(2.0));
    int q1 = dp[l][k];
    int q2 = dp[r-(1<<k)+1][k];
    if(L[q1] < L[q2]) return E[q1];
    else return E[q2];
}
void dfs(int u, int depth, int dis){
    dist[u] = dis;
    R[u] = cnte;
    E[cnte] = u;
    L[cnte++] = depth;
    intime[u] = ++cntin;
    for(int cur = head[u]; cur!=-1; cur=g[cur].nxt){
        if(!intime[g[cur].y]){
            dfs(g[cur].y, depth + 1, dis + g[cur].c);
            E[cnte] = u;
            L[cnte++] = depth;
        }
    }
    outtime[u] = ++cntout;
}

inline bool is_ancestor(int f, int s)
{
    if(intime[f] < intime[s] && outtime[f] > outtime[s])
        return true;
    return false;
}

inline int _distance(int a, int b){
    if(a == b) return 0;
    if(is_ancestor(a, b) || is_ancestor(b, a)){
        return abs(dist[b] - dist[a]);
    }
    else{
        int ancestor = rmq(R[a], R[b]);
        return _distance(ancestor, a) + _distance(ancestor, b);
    }
}

int main(){
    int N;
    scanf("%d", &N);
    while(true){
        ne = 0;
        memset(head, -1, sizeof(head));
        memset(intime, 0, sizeof(intime));
        int A, _B, _L;
        for(int i=0; i<N-1; ++i){
            scanf("%d%d%d", &A, &_B, &_L);
            add_edge(A, _B, _L);
        }

        cnte = 0; cntin = 0; cntout = 0;
        dfs(0, 0, 0);
        st();
        int Q;
        scanf("%d", &Q);
        for(int i=0; i<Q; ++i){
            int X, Y, Z;
            scanf("%d%d%d", &X, &Y, &Z);
            int ancestor = 0;
            int len = INF;
            ancestor = rmq(R[Z], R[X]);
            len = min(len, _distance(ancestor, X)
                      + _distance(ancestor, Y)
                      + _distance(ancestor, Z));
            ancestor = rmq(R[Z], R[Y]);
            len = min(len, _distance(ancestor, X)
                      + _distance(ancestor, Y)
                      + _distance(ancestor, Z));
            ancestor = rmq(R[X], R[Y]);
            len = min(len, _distance(ancestor, X)
                      + _distance(ancestor, Y)
                      + _distance(ancestor, Z));
            printf("%d\n", len);
        }
        if(scanf("%d", &N) != EOF){
            printf("\n");
        }
        else{
            break;
        }
    }
    return 0;
}
