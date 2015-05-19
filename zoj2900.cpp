#include <stdio.h>
#include <string.h>
#include <assert.h>

//  dp + binary-indexed-tree

typedef long long LL;
const int MAX_N = 2015;
const int MAX_MARK = 102;
LL array[MAX_MARK+5];
int mark[MAX_N+5];
LL dp[2][MAX_N+5];
int m;

inline int lowbit(int x){
    return x & (x ^ (x - 1));
}
void add(int i, LL value, int n){
    for(;i<=n; i+=lowbit(i)){
        array[i] += value;
        if(array[i] >= m) array[i] -= m;
    }
}
LL sumOf(int i){
    if(i <= 0) return 0;
    LL sum = 0;
    for(;i>0;i-=lowbit(i)){
        sum += array[i];
    }
    return sum;
}
inline void init(int n){
    for(int i=1; i<=n; ++i) array[i] = 0;
}
inline LL valueOf(int l, int r, int n){
    if(l <= 1) l = 1;
    if(r >= n) r = n;
    return (sumOf(r) - sumOf(l-1));
}

int main(){
    int n, k, p;
    while(scanf("%d%d%d%d", &n, &k, &p, &m) != EOF){
        int ans = 0;
        int max_mark = 1;
        for(int i=1; i<=n; ++i){
            scanf("%d", &mark[i]);
            ++mark[i];
            if(mark[i] > max_mark) max_mark = mark[i];
            dp[0][i] = 1;
            if(k <= 1){ ++ans; }
        }
        if(ans >= m) ans %= m;
        for(int idx_old=0, j=2; j<=n; ++j, idx_old^=1){
            init(max_mark + 1);
            for(int i=j-1; i<n; ++i){
                add(mark[i], dp[idx_old][i], max_mark);
                dp[idx_old^1][i+1] = valueOf(mark[i+1]-p, mark[i+1]+p, max_mark);
                if(dp[idx_old^1][i+1] >= m) dp[idx_old^1][i+1] %= m;
                while(dp[idx_old^1][i+1] < 0) dp[idx_old^1][i+1] += m;
                if(j >= k){
                    ans += dp[idx_old^1][i+1];
                    if(ans >= m) ans %= m;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
