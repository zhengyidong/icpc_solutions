#include <stdio.h>
#include <string.h>

int dp[6][26];
int total[6];
int main(){
    memset(dp, 0, sizeof(dp));
    memset(total, 0, sizeof(total));

    for(int i=0; i<26; ++i) dp[1][i] = 1;
    for(int i=2; i<=5; ++i){
        for(int j=0; j<26; ++j){
            for(int k=j+1; k<26; ++k)
            dp[i][j] += dp[i-1][k];
        }
    }

    for(int i=1; i<=5; ++i){
        for(int j=0; j<26; ++j){
            total[i] += dp[i][j];
        }
    }

    char str[6];
    while(scanf("%s", str) != EOF){
        int len = strlen(str);
        bool valid = true;
        for(int i=0; i<len-1; ++i){
            if(str[i] >= str[i+1]) valid = false;
        }
        if(!valid){
            printf("0\n");
            continue;
        }
        int ans = 0;
        for(int i=1; i<len; ++i) ans += total[i];

        int j = 0;
        for(int i=len; i>=1; --i){
            for(;j<str[len-i]-'a'; ++j){
                ans += dp[i][j];
            }
            j = str[len-i]-'a' + 1;

        }
        printf("%d\n", ans + 1);
    }
    return 0;
}

