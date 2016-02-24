//  dfs

#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <cmath>
#include <map>

using namespace std;

const int MAX_N = 300001;

int intime[MAX_N], outtime[MAX_N];

int ne = 0;
int cnte, cntin, cntout;

struct edge{
    int x;
    int y;
    int nxt;
} g[2 * MAX_N];

int head[2 * MAX_N];
void add_edge(int x, int y){
    g[ne].x = x; g[ne].y = y;
    g[ne].nxt = head[x]; head[x] = ne++;
}
void dfs(int u, int depth){
    intime[u] = ++cntin;
    for(int cur = head[u]; cur!=-1; cur=g[cur].nxt){
        if(!intime[g[cur].y]){
            dfs(g[cur].y, depth + 1);
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

int index_current;
map<string, int> name_index_map;

int index_of(const char *str){
    string stdstr(str);
    map<string, int>::iterator itr = name_index_map.find(stdstr);
    if(itr == name_index_map.end()){
        name_index_map.insert(make_pair(stdstr, index_current));
        return index_current++;
    }
    else{
        return itr->second;
    }
}

int main(){
    int N;
    char base[256];

    char class_a[256];
    char class_b[256];
    int index_case = 1;
    scanf("%s%d", base, &N);
    while(true){
        printf("Project %d\n", index_case++);
        cntin = 0; cntout = 0; ne = 0; index_current = 0;
        name_index_map.clear();
        name_index_map.insert(make_pair(string(base), index_current++));
        memset(head, -1, sizeof(head));
        memset(intime, 0, sizeof(intime));
        for(int i=0; i<N; ++i){
            scanf("%s%s", class_a, class_b);
            int s = index_of(class_b);
            int e = index_of(class_a);
            add_edge(s, e);
        }
        dfs(0, 0);
        int M;
        scanf("%d", &M);
        for(int i=0; i<M; ++i){
            scanf("%s%s", class_a, class_b);
            bool is_ance = is_ancestor(index_of(class_b), index_of(class_a));

            if(is_ance || (strcmp(class_a, class_b) == 0)) printf("Yes\n");
            else printf("No\n");
        }
        if(scanf("%s%d", base, &N) != EOF) printf("\n");
        else break;
    }
    return 0;
}
