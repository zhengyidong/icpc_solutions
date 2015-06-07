#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <set>

const int MAX_FILE_NUM = 10000;
int index_r_m;
int g[300][300];
int in[300];

using namespace std;

int index_of(map<string, int>& m, string r_m[], const string& str){
    map<string, int>::iterator itr = m.find(str);
    if(itr == m.end()){
        r_m[index_r_m] = str;
        m.insert(make_pair(str, index_r_m));
        return index_r_m++;
    }
    else{
        return itr->second;
    }
}

int main(){
    int N;
    char str[25];
    scanf("%d", &N);
    while(true){
        memset(g, 0, sizeof(g));
        memset(in, 0, sizeof(in));
        index_r_m = 0;
        map<string, int> m;
        string r_m[MAX_FILE_NUM];

        for(int i=0; i<N; ++i){
            scanf("%s", str);
            int s = index_of(m, r_m, str);

            int M;
            scanf("%d", &M);
            for(int j=0; j<M; ++j){
                scanf("%s", str);
                int e = index_of(m, r_m, str);
                g[s][e] = 1;
                ++in[e];
            }
        }
        set<string> set_zero_in;
        for(int i=0; i<index_r_m; ++i){
            if(in[i] == 0){
                set_zero_in.insert(r_m[i]);
            }
        }
        for(set<string>::iterator itr=set_zero_in.begin(); itr!=set_zero_in.end(); ++itr){
            printf("%s\n", itr->c_str());
        }
        if(scanf("%d", &N) != EOF){
            printf("\n");
        }
        else{
            break;
        }
    }
    return 0;
}

