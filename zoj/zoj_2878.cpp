#include <stdio.h>

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, pos;
        scanf("%d", &n);
        int max_pos = -1, min_pos = 100;
        for(int i=0; i<n; ++i){
            scanf("%d", &pos);
            if(pos < min_pos) min_pos = pos;
            if(pos > max_pos) max_pos = pos;
        }
        printf("%d\n", 2 * (max_pos - min_pos));
    }
    return 0;
}
