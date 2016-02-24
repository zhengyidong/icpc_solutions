#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

int main(){
    char g[2188][2188];
    int n;
    while(scanf("%d", &n) != EOF && n != -1){
        memset(g, 0, sizeof(g));
        g[0][0] = 1;
        int num_rows = pow(3, n - 1);
        if(n != 1){
            int cur_row = 1;
            for(int i=1; i<n; ++i){
                for(int j=0; j<cur_row; ++j)
                    for(int k=0; k<cur_row; ++k){
                        g[j][k + 2 * cur_row] = g[j][k];
                        g[j + 2 * cur_row][k] = g[j][k];
                        g[j + 2 * cur_row][k + 2 * cur_row] = g[j][k];
                        g[j + cur_row][k + cur_row] = g[j][k];
                    }
                cur_row *= 3;
            }
        }
        for(int i=num_rows-1; i>=0; --i){
            for(int j=num_rows-1; j>=0; --j){
                if(g[i][j] == 1){
                    g[i][j+1] = 2;
                    break;
                }
            }
        }

        for(int i=0; i<num_rows; ++i){
            for(int j=0; j<num_rows; ++j){
                if(g[i][j] == 1){
                    printf("X");
                }
                else if(g[i][j] == 2){
                    break;
                }
                else{
                    printf(" ");
                }
            }
            printf("\n");
        }
        printf("-\n");
    }
    return 0;
}
