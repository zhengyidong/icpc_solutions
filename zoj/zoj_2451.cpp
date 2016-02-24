#include <iostream>
#include <cstdio>

using namespace std;

int main(){
    int N, M;
    int arr[50001];
    int s[500001];
    int e[500001];
    while(scanf("%d%d", &N, &M) != EOF){
        for(int i=1; i<=N; ++i) arr[i] = i;

        for(int i=1; i<=M; ++i){
            scanf("%d%d", &s[i], &e[i]);
            swap(arr[s[i]], arr[e[i]]);
        }
        int max_num = arr[N];

        int ans = 0;
        for(int i=1; i<=N; ++i) arr[i] = i;
        for(int i=1; i<=M; ++i){
            if(arr[s[i]] == max_num || arr[e[i]] == max_num){
                ++ans;
            }
            swap(arr[s[i]], arr[e[i]]);
        }
        printf("%d\n", ans);
    }
    return 0;
}

