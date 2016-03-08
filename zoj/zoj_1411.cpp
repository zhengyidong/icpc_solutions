#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

bool visited[40][40];
bool used[40];
int pieces[16];
int s, n;
bool empty(int sx, int sy, int len){
    if(sx + len > s || sy + len > s) return false;
    for(int i=sx; i<sx+len; ++i)
        for(int j=sy; j<sy+len; ++j){
            if(visited[i][j]) return false;
        }
    return true;
}
inline bool fill(int sx, int sy, int len){
    for(int i=sx; i<sx+len; ++i)
        for(int j=sy; j<sy+len; ++j){
            visited[i][j] = true;
        }
    return true;
}
inline bool unfill(int sx, int sy, int len){
    for(int i=sx; i<sx+len; ++i)
        for(int j=sy; j<sy+len; ++j){
            visited[i][j] = false;
        }

    return true;
}
bool dfs(int state){
    if(state >= s * s) return true;
    int sx = state / s;
    int sy = state % s;
    if(visited[sx][sy]) return dfs(state + 1);

    bool no[16];
    memset(no, false, sizeof(no));

    for(int i=0; i<n; ++i){
        if(used[i] || no[pieces[i]]) continue;
        if(empty(sx, sy, pieces[i])){
            fill(sx, sy, pieces[i]);

            used[i] = true;

            if(dfs(state + 1)) return true;
            else no[pieces[i]] = true;

            used[i] = false;

            unfill(sx, sy, pieces[i]);
        }
        else no[pieces[i]] = true;
    }
    return false;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        memset(visited, false, sizeof(visited));
        memset(used, false, sizeof(used));
        int sum = 0;
        scanf("%d%d", &s, &n);
        for(int i=0; i<n; ++i){
            scanf("%d", &pieces[i]);
            sum += pieces[i] * pieces[i];
        }

        sort(pieces, pieces + n, greater<int>());

        if(s * s != sum){
            printf("HUTUTU!\n");
        }
        else{
            if(dfs(0)){
                printf("KHOOOOB!\n");
            }
            else{
                printf("HUTUTU!\n");
            }
        }
    }
    return 0;
}
