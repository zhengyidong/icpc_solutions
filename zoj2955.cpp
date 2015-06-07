//complete-knapsack + pigeonhole-principle 

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX_M = 100;
const int MAX_SCORE = 100;
int score[MAX_M + 1];
int dp[MAX_SCORE * MAX_SCORE + 1];

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        int M, N;
        scanf("%d%d", &M, &N);
        for(int i=1; i<=M; ++i) scanf("%d", &score[i]);
        sort(score + 1, score + M + 1);

        //  max value produced by score[l] to score[M-1]
        int value_max = score[M] * score[M];

        int value_left = N;
        int ans = 0;
        if(N >= value_max){
            value_left = N % value_max;
            ans += (N - value_left) / score[M];
        }
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        for(int i=1; i<=M; ++i)
            for(int j=score[i]; j<=value_left; ++j){
                if(dp[j-score[i]] == -1) continue;
                if(dp[j] == -1){
                    dp[j] = dp[j - score[i]] + 1;
                }
                else{
                    dp[j] = dp[j] < (dp[j - score[i]] + 1) ? dp[j] : (dp[j - score[i]] + 1);
                }
            }

        if(dp[value_left] == -1){
            printf("-1\n");
        }
        else{
            printf("%d\n", ans + dp[value_left]);
        }

    }
    return 0;
}

