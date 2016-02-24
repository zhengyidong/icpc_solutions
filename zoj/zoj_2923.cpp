// multiple-sp

#include <iostream>
#include <queue>
#include <map>
#include <cstring>
#include <cstdio>

using namespace std;

const int MAX_EDGE = 2000000;
const int MAX_N = 5000;
const int INF = 1 << 29;
struct edge
{
    int x;
    int y;
    int nxt;
}e[MAX_EDGE];


bool has_insect[MAX_N];
int dist[MAX_N];
int insect[MAX_N];
bool visited[MAX_N];

struct node{
    int idx_v;
    int dis;
    int ins;
    node(int i){
        ins = insect[i];
        dis = dist[i];
        idx_v = i;
    }
    bool operator>(const node& n)const{
        if(dis == n.dis) return ins > n.ins;
        return dis > n.dis;
    }
};

map<int, int> v_index_map;
int index_v = 0;
int ne = 0;

int head[MAX_EDGE];
void add_edge(int x, int y){
    e[ne].x = x; e[ne].y = y;
    e[ne].nxt = head[x]; head[x] = ne++;
    e[ne].x = y; e[ne].y = x;
    e[ne].nxt = head[y]; head[y] = ne++;
}

void dijkstra(int i, int n){
    memset(visited, false, sizeof(visited));
    fill(dist, dist + n, INF);
    fill(insect, insect + n, INF);
    dist[i] = 0;
    visited[i] = true;
    insect[i] = has_insect[i];
    priority_queue<node, vector<node>, greater<node> > q;
    q.push(node(i));
    while(!q.empty()){
        int y = q.top().dis;
        int x = q.top().idx_v;
        q.pop();
        if(y != dist[x]){
            continue;
        }
        for(int cur=head[x]; cur!=-1; cur=e[cur].nxt){
            if(!visited[e[cur].y]){
                dist[e[cur].y] = y + 1;
                insect[e[cur].y] = insect[x] + has_insect[e[cur].y];
                q.push(node(e[cur].y));
                visited[e[cur].y] = true;
            }
        }
    }
}

int index_of(int v){
    map<int, int>::iterator itr = v_index_map.find(v);
    if(itr == v_index_map.end()){
        v_index_map.insert(make_pair(v, index_v));
        return index_v++;
    }
    else{
        return itr->second;
    }
}
int dfs(int t, int num_insects){
    if(t == index_of(1)) return 1;
    int ans = 0;
    if(has_insect[t]) --num_insects;
    for(int cur=head[t]; cur!=-1; cur=e[cur].nxt){
        if(dist[e[cur].y] + 1 == dist[t] && insect[e[cur].y] <= num_insects){
            int tmp = dfs(e[cur].y, num_insects);
            ans += tmp;
        }
    }
    return ans;
}

int main(){
    int m, n, k;
    while(scanf("%d%d%d", &m, &n, &k) != EOF){
        memset(head, -1, sizeof(head));
        ne = 0;
        index_v = 0;
        v_index_map.clear();
        for(int i=0; i<n; ++i){
            int v, insect;
            scanf("%d%d", &v, &insect);
            has_insect[index_of(v)] = insect;
        }
        for(int i=0; i<m; ++i){
            int s, e;
            scanf("%d%d", &s, &e);
            add_edge(index_of(s), index_of(e));
        }

        dijkstra(index_of(1), n);

        int ans = dfs(index_of(n), k);
        if(ans == 0){
            printf("Impossible!\n");
        }
        else{
            printf("%d\n", ans);
        }
    }
    return 0;
}
