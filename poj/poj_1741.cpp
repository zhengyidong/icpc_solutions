#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAX_N = 10005;
const int INF = 1 << 30;

int N, K;
struct edge{
    int x;
    int y;
    int c;
    int nxt;
};

int final_ans;

edge e[2 * MAX_N + 1];
int head[2 * MAX_N + 1];
int ne;
bool visited[MAX_N + 1];
int num_of_nodes[MAX_N + 1];
int num_max_branch[MAX_N + 1];
int possible_roots[MAX_N + 1];
int depth[MAX_N + 1];
int possible_depth[MAX_N + 1];
int num_possible_nodes;

void add_edge(int x, int y, int c){
    e[ne].x = x; e[ne].y = y; e[ne].c = c;
    e[ne].nxt = head[x]; head[x] = ne++;
}


void get_depth(int v, int parent, int depth){
    possible_depth[num_possible_nodes++] = depth;
    for(int cur=head[v]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        int c = e[cur].c;
        if(!visited[y] && y != parent && c <= K){
            get_depth(y, v, depth + c);
        }
    }
}

void dfs(int v, int parent){
    num_of_nodes[v] = 1;
    num_max_branch[v] = 0;
    for(int cur=head[v]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        if(!visited[y] && y != parent){
            dfs(y, v);
            num_of_nodes[v] += num_of_nodes[y];
            num_max_branch[v] = max(num_max_branch[v], num_of_nodes[y]);
        }
    }
    possible_roots[num_possible_nodes++] = v;
}
int get_center(int v){
    num_possible_nodes = 0;
    dfs(v, 0);
    int num_nodes_of_v = num_of_nodes[v];
    int min_max_branch = INF;
    int min_idx = -1;
    for(int i=0; i<num_possible_nodes; ++i){
        int index_root = possible_roots[i];
        if(min_max_branch > max(num_max_branch[index_root], num_nodes_of_v - num_of_nodes[index_root])){
            min_max_branch = max(num_max_branch[index_root], num_nodes_of_v - num_of_nodes[index_root]);
            min_idx = index_root;
        }
    }
    return min_idx;
}

int num_not_exceed_k_diff(int v){
    int ans = 0;
    num_possible_nodes = 0;
    get_depth(v, 0, 0);
    sort(possible_depth, possible_depth + num_possible_nodes);
    int left = 0, right = num_possible_nodes - 1;
    while(left < right){
        if(possible_depth[left] + possible_depth[right] <= K){ans+=(right - left); ++left;}
        else {--right;}
    }
    return ans;
}
int num_not_exceed_k_same(int v){
    int ans = 0;
    for(int cur=head[v]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        int c = e[cur].c;
        if(!visited[y]){
            num_possible_nodes = 0;
            get_depth(y, v, c);
            sort(possible_depth, possible_depth + num_possible_nodes);
            int left = 0, right = num_possible_nodes - 1;
            while(left < right){
                if(possible_depth[left] + possible_depth[right] <= K){ans+=(right - left); ++left;}
                else {--right;}
            }
        }
    }
    return ans;
}

void solve(int v, int parent){
    int root = get_center(v);
    visited[root] = true;
    final_ans += num_not_exceed_k_diff(root) - num_not_exceed_k_same(root);

    for(int cur=head[root]; cur!=-1; cur=e[cur].nxt){
        int y = e[cur].y;
        if(!visited[y] && y != parent){
            solve(y, root);
        }
    }
}

int main(){
    while(scanf("%d%d", &N, &K) != EOF && (N != 0 || K != 0)){
        ne = 0;
        memset(head, -1, sizeof(head));
        memset(visited, false, sizeof(visited));

        int s, e, c;
        for(int i=0; i<N-1; ++i){
            scanf("%d%d%d", &s, &e, &c);
            add_edge(s, e, c);
            add_edge(e, s, c);
        }

        final_ans = 0;
        solve(1, 0);
        printf("%d\n", final_ans);

    }
    return 0;
}
