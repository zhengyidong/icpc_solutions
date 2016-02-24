// ZOJ 3686
// dfs + segment tree

#include <iostream>
#include <list>

#include <stdio.h>
#include <string.h>

inline bool intersect(int left1, int right1, int left2, int right2){
    return !(right1 < left2 || right2 < left1);
}

inline bool contains(int left1, int right1, int left2, int right2){
    return (left1 <= left2 && right1 >= right2);
}

const int MAX_N = 100000;
int num_sub[MAX_N + 1];
std::list<int> tree[MAX_N + 1];
int M, N;
int idx_dfs;
int order_dfs[MAX_N + 1];

struct seg_tree{
    int s;
    int e;
    int val;
    int mark;
}t[4 * (MAX_N + 1)];

inline int len_interval(const seg_tree& t){
    return t.e - t.s + 1;
}

void dfs(int node){
    num_sub[node] = 1;
    order_dfs[node] = idx_dfs++;
    for(auto it=tree[node].begin(), e=tree[node].end(); it!=e; ++it){
        dfs(*it);
        num_sub[node] += num_sub[*it];
    }
}

void construct(){
    int parent;
    for(int i=2; i<=N; ++i){
        scanf("%d", &parent);
        tree[parent].push_back(i);
    }

    dfs(1);

    t[0].s = 0; t[0].e = N-1;
    t[0].val = 0; t[0].mark = 0;
}

void push_down(int idx){
    if(len_interval(t[idx]) != 1){
        t[2*idx+1].mark += t[idx].mark;
        t[2*idx+2].mark += t[idx].mark;
        if(t[idx].mark % 2 != 0){
            t[2*idx+1].val = len_interval(t[2*idx+1]) -  t[2*idx+1].val;
            t[2*idx+2].val = len_interval(t[2*idx+2]) -  t[2*idx+2].val;
        }
        t[idx].mark = 0;
    }
}

void build(int idx){
    if(t[idx].e == t[idx].s) return;

    int mid = (t[idx].e + t[idx].s) / 2;
    t[2*idx+1].s = t[idx].s; t[2*idx+1].e = mid;
    t[2*idx+1].mark = 0; t[2*idx+1].val = 0;
    t[2*idx+2].s = mid + 1; t[2*idx+2].e = t[idx].e;
    t[2*idx+2].mark = 0; t[2*idx+2].val = 0;
    build(2*idx + 1);
    build(2*idx + 2);
}

int search(int idx, int left, int right){
    push_down(idx);

    if(!intersect(t[idx].s, t[idx].e, left, right)){
        return 0;
    }

    if(contains(left, right, t[idx].s, t[idx].e)){
        return t[idx].val;
    }

    return search(2 * idx + 1, left, right) +
           search(2 * idx + 2, left, right);
}

int modify(int idx, int left, int right){
    push_down(idx);

    if(!intersect(t[idx].s, t[idx].e, left, right)){
        return 0;
    }

    if(contains(left, right, t[idx].s, t[idx].e)){
        t[idx].val = len_interval(t[idx]) - t[idx].val;
        t[idx].mark += 1;
        return t[idx].val;
    }

    modify(2 * idx + 1, left, right);
    modify(2 * idx + 2, left, right);

    return t[idx].val = t[2*idx+1].val + t[2*idx+2].val;
}

int main(){
    while(scanf("%d%d", &N, &M) != EOF){
        for(int i=1; i<=N; ++i) tree[i].clear();
        idx_dfs = 0;
        construct();
        build(0);

        char cmd[3];
        int node;

        for(int i=0; i<M; ++i){
            scanf("%s%d", cmd, &node);
            if(cmd[0] == 'o'){
                modify(0, order_dfs[node], order_dfs[node] + num_sub[node] - 1);
            }
            else{
                printf("%d\n", search(0,
                                      order_dfs[node],
                                      order_dfs[node] + num_sub[node] - 1));
            }
        }

        printf("\n");
    }
    return 0;
}
