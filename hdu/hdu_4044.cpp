#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int m, n;
const int MAX_N = 1005;
const int MAX_KI = 52;
const int MAX_M = 202;
const int INF = (1 << 30);

struct tower{
    int price;
    int power;
    bool operator<(const tower& t) const{
        if(price == t.price) return power < t.power;
        return price < t.price;
    }
}to[MAX_N][MAX_KI];
int ki[MAX_N];
int dp[MAX_N][MAX_M];

int ne;
int head[MAX_N];
struct edge{
    int x;
    int y;
    int nxt;
}e[2 * MAX_N];

void add_edge(int x, int y){
    e[ne].x = x; e[ne].y = y;
    e[ne].nxt = head[x]; head[x] = ne++;
}

void dfs(int u, int parent){
    int cnt = 0;
    for(int cur=head[u]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        if(y == parent) continue;
        dfs(y, u);

        for(int i=m; i>=0; --i){
            int tmp_ui = dp[u][i];
            if(cnt == 0)
                dp[u][i] = dp[y][i];
            else
                dp[u][i] = 0;
            int tmp = INF;
            for(int j=0; j<=i; ++j){
                if(cnt != 0){
                    tmp = dp[u][i-j];
                    if(j == 0) tmp = tmp_ui;
                }
                else tmp = INF;
                if(dp[u][i] >= tmp) continue;
                for(int k=0; k<ki[y]; ++k){
                    if(j < to[y][k].price) break;
                    dp[u][i] = max(dp[u][i], min(tmp, dp[y][j-to[y][k].price] + to[y][k].power));
                }
            }
        }
        ++cnt;
    }
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        memset(head, -1, sizeof(head));
        memset(dp, 0, sizeof(dp));
        ne = 0;

        scanf("%d", &n);
        int s, e;
        for(int i=1; i<=n-1; ++i){
            scanf("%d%d", &s, &e);
            add_edge(s, e);
            add_edge(e, s);
        }
        scanf("%d", &m);
        for(int i=1; i<=n; ++i){
            scanf("%d", &ki[i]);
            for(int j=0; j<ki[i]; ++j){
                scanf("%d%d", &to[i][j].price, &to[i][j].power);
            }
            to[i][ki[i]].price = to[i][ki[i]].power = 0;
            ++ki[i];
            sort(to[i], to[i] + ki[i]);
        }

        add_edge(0, 1);
        add_edge(1, 0);

        dfs(0, -1);

        printf("%d\n", dp[0][m]);
    }
    return 0;
}
