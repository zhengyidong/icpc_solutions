#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

//  ad-hoc.
//  1 <= m <= 50
//  3 <= n <= 10
//  0 <=p, q <= m
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    int cnt_case = 1;
    if(n == 0 && m == 0) return 0;
    while(true){
        int array_p3_n_q3[2501];
        bool valid[250001] = {false};
        int cnt_p3_n_q3 = 0;
        set<int> set_p3_n_q3;
        for(int p=0; p<=m; ++p)
            for(int q=0; q<=m; ++q){
                set_p3_n_q3.insert(p*p*p + q*q*q);
                valid[p*p*p+q*q*q] = true;
            }
        set<int>::iterator itr = set_p3_n_q3.begin();
        for(; itr!=set_p3_n_q3.end(); ++itr){
            array_p3_n_q3[cnt_p3_n_q3++] = *itr;
        }
        vector< pair<int, int> > vec_a_n_b;
        for(int i=0; i<cnt_p3_n_q3; ++i){
            int a = array_p3_n_q3[i];
            for(int j=i+1; j<cnt_p3_n_q3; ++j){
                int b = array_p3_n_q3[j] - array_p3_n_q3[i];
                bool is_valid = true;
                int item = a + 2 * b;
                for(int k=0; k<n-2; ++k){
                    if(item <= 250000 && valid[item]){
                        item += b;
                    }
                    else{
                        is_valid = false;
                        break;
                    }
                }
                if(is_valid){
                    vec_a_n_b.push_back(make_pair(b, a));
                }
            }
        }
        printf("Case %d:\n", cnt_case++);
        int size = vec_a_n_b.size();
        if(size == 0){
            printf("NONE\n");
        }
        else{
            sort(vec_a_n_b.begin(), vec_a_n_b.end());
            for(int i=0; i<size; ++i){
                printf("%d %d\n", vec_a_n_b[i].second, vec_a_n_b[i].first);
            }
        }
        if(scanf("%d%d", &n, &m) != EOF && (n != 0 || m != 0)){
            printf("\n");
        }
        else{
            break;
        }

    }
    return 0;
}
