#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool found = false;
bool visited[20][20];
int M, N;
char maze[20][20];
int num_keys[5];
int num_keys_found[5];
int pos_x[5];
int pos_y[5];

bool ok(int x, int y){
    if(x < 0 || x >= M || y < 0 || y >= N) return false;
    if(visited[x][y]) return false;
    if((maze[x][y] >= 'A' && maze[x][y] <= 'E') || maze[x][y] == 'X') return false;

    return true;
}

void dfs(int x, int y){
    visited[x][y] = true;

    if(maze[x][y] >= 'a' && maze[x][y] <= 'e'){
        int tmp = ++num_keys_found[maze[x][y]-'a'];
        int tmp_ch = maze[x][y]-'a';
        maze[x][y] = '.';
        if(num_keys[tmp_ch] == tmp){
            maze[pos_x[tmp_ch]][pos_y[tmp_ch]] = '.';
            memset(visited, false, sizeof(visited));
            dfs(x, y);
        }
    }
    if(maze[x][y] == 'G'){found = true; return;}
    if(ok(x+1, y)) dfs(x+1, y);
    if(ok(x-1, y)) dfs(x-1, y);
    if(ok(x, y+1)) dfs(x, y+1);
    if(ok(x, y-1)) dfs(x, y-1);
}

int main(){
    while(scanf("%d%d", &M, &N) != EOF){
        memset(visited, false, sizeof(visited));
        found = false;
        int s_x, s_y;
        memset(num_keys, 0, sizeof(num_keys));
        memset(num_keys_found, 0, sizeof(num_keys_found));
        if(M == 0 && N == 0) break;

        for(int i=0; i<M; ++i){
            scanf("%s", maze[i]);
            for(int j=0; j<N; ++j){
                if(maze[i][j] >= 'a' && maze[i][j] <= 'e'){
                    ++num_keys[maze[i][j] - 'a'];
                }
                else if(maze[i][j] == 'S'){
                    s_x = i; s_y = j;
                    maze[i][j] = '.';
                }
                else if(maze[i][j] >= 'A' && maze[i][j] <= 'E'){
                    pos_x[maze[i][j] - 'A'] = i;
                    pos_y[maze[i][j] - 'A'] = j;
                }
            }
        }

        dfs(s_x, s_y);

        if(found) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
