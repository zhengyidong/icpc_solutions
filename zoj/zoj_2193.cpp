#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int main(){
    char cmd[10];
    int g[4][4];
    int g_pos[4][4];
    while(scanf("%s", cmd) != EOF){
        if(strcmp(cmd, "START")){
            break;
        }
        for(int i=0; i<4; ++i)
            for(int j=0; j<4; ++j)
                scanf("%d", &g[i][j]);
        int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        bool found = false;
        for(int i=0; i<362880; ++i){
            for(int j=0; j<9; ++j){
                int start_pos_x = (arr[j] - 1) / 3;
                int start_pos_y = (arr[j] - 1) % 3;
                g_pos[start_pos_x][start_pos_y] = arr[j];
                g_pos[start_pos_x+1][start_pos_y] = arr[j];
                g_pos[start_pos_x][start_pos_y+1] = arr[j];
                g_pos[start_pos_x+1][start_pos_y+1] = arr[j];
            }
            bool equal = true;
            for(int j=0; j<4; ++j)
                for(int k=0; k<4; ++k){
                    if(g[j][k] != g_pos[j][k]){
                        equal = false;
                        break;
                    }
                }

            if(equal){
                found = true;
                break;
            }

            next_permutation(arr, arr + 9);
        }

        if(found){
            printf("THESE WINDOWS ARE CLEAN\n");
        }
        else{
            printf("THESE WINDOWS ARE BROKEN\n");
        }


        scanf("%s", cmd);
    }
    return 0;
}
