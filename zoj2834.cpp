#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>

//  ad-hoc dfs.

using namespace std;

struct tree{
    vector<int> children;
    int t;
    int p;
}trs[1005];

int all_time[1005];
int not_all_time[1005];
int not_r_time[1005];

int N;

// all time. fight with every one.
int dfs_all_time(int idx){
    int ans = trs[idx].t;
    for(int i=0, s=trs[idx].children.size(); i<s; ++i){
        int idx_i = trs[idx].children[i];
        ans += dfs_all_time(idx_i);
    }
    return (all_time[idx] = ans);
}

//  max time when cannnot fight with root.
int dfs_not_r(int idx){
    int ans = 0;
    int size_ch = trs[idx].children.size();
    if(size_ch == 0) return (not_r_time[idx] = ans);
    int max_value = 0;
    for(int i=0; i!=size_ch; ++i){
        int idx_i = trs[idx].children[i];
        ans += dfs_not_r(idx_i);
        if(max_value < all_time[idx_i] - not_r_time[idx_i]){
            max_value = all_time[idx_i] - not_r_time[idx_i];
        }
    }
    ans += max_value;
    return (not_r_time[idx] = ans);
}

int dfs(int idx){
    int ans = trs[idx].t;
    int size_ch = trs[idx].children.size();
    if(size_ch == 0) {
        return (not_all_time[idx] = ans);

    }
    else if(size_ch == 1){
        return (not_all_time[idx] = (ans + all_time[trs[idx].children[0]]));
    }
    else{
        for(int i=0; i!=size_ch; ++i){
            int idx_i = trs[idx].children[i];
            ans += not_r_time[idx_i];
        }
    }
    int max_value = 0;

    for(int i=0; i<size_ch; ++i){
        for(int j=0; j<size_ch; ++j){
            int idx_i = trs[idx].children[i];
            int idx_j = trs[idx].children[j];
            if(idx_i == idx_j) continue;
            dfs(idx_i);
            if(max_value < not_all_time[idx_i] - not_r_time[idx_i] + all_time[idx_j] - not_r_time[idx_j]){
                max_value = not_all_time[idx_i] - not_r_time[idx_i] + all_time[idx_j] - not_r_time[idx_j];
            }
        }
    }
    ans += max_value;
    return (not_all_time[idx] = ans);
}

int main(){
    while(scanf("%d", &N) != EOF && N != 0){
        for(int i=0; i<N; ++i) {
            scanf("%d", &trs[i].t);
            trs[i].children.clear();
        }

        memset(not_all_time, -1, sizeof(not_all_time));
        memset(not_r_time, -1, sizeof(not_r_time));
        memset(all_time, -1, sizeof(all_time));


        for(int i=0; i<N; ++i){
            int parent;
            scanf("%d", &parent);
            trs[i].p = parent;
            if(parent == -1){
                continue;
            }
            trs[parent].children.push_back(i);
        }

        int ans = 0;
        for(int i=0; i<N-1; ++i){
            if(trs[i].p == -1)
                ans += dfs_all_time(i);
        }

        dfs_all_time(N - 1);
        dfs_not_r(N - 1);
        printf("%d\n", ans + dfs(N - 1));
    }
    return 0;
}
