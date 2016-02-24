#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>

typedef long long LL;

using namespace std;


class matrix{
public:
    enum option{ZERO, IDENTITY};
    matrix(int row, int col, option opt=ZERO):_row(row), _col(col){
        memset(_m, 0, sizeof(_m));
        if(opt == IDENTITY)
            for(int i=1, len=std::min(_row,_col);i<=len; ++i) _m[i][i] = 1;
    }
    matrix(const matrix& mb){
        _row = mb.row();
        _col = mb.col();
        memcpy(_m, mb._m, sizeof(_m));
    }
    LL* operator[](int i){
        return _m[i];
    }
    LL tr() const{
        int ans = 0;
        for(int i=1, len=std::min(_row,_col); i<=len; ++i) ans += _m[i][i];
        return ans;
    }
    matrix operator*(const matrix& mb) const{
        int col_mb = mb.col();
        matrix ret(_row, col_mb);
        for(int i=1; i<=_row; ++i)
            for(int j=1; j<=col_mb; ++j)
                for(int k=1; k<=_col; ++k)
                    ret._m[i][j] += _m[i][k] * mb._m[k][j];
        return ret;
    }
    matrix operator%(LL mod) const{
        matrix ret = *this;
        for(int i=1; i<=_row; ++i)
            for(int j=1; j<=_col; ++j){
                while(ret[i][j] < 0) ret[i][j] += mod;
                ret[i][j] %= mod;
            }
        return ret;
    }
    matrix power_mod(LL b, LL n){
        matrix ans(_row, _col, IDENTITY);
        matrix a = *this;
        a = a % n;
        while(b > 0){
            if(b & 1) ans = (ans * a) % n;
            b >>= 1;
            a = (a * a) % n;
        }
        return ans;
    }
    int col() const{ return _col; }
    int row() const{ return _row; }
private:
    LL _m[61][61];
    int _row;
    int _col;
};

map<int, int> index_map;
int _index = 1;

int index_of(int v){
    map<int, int>::iterator itr = index_map.find(v);
    if(itr != index_map.end()){
        return itr->second;
    }
    else{
        index_map.insert(make_pair(v, _index));
        return _index++;
    }
}
int main(){
    int n;
    while(scanf("%d", &n) != EOF){
        matrix cities(30, 30);
        index_map.clear(); _index = 1;
        int s, e;
        for(int i=0; i<n; ++i){
            scanf("%d%d", &s, &e);
            ++cities[index_of(s)][index_of(e)];
        }
        matrix fac(60, 60);
        for(int i=1; i<=60; ++i){
            for(int j=1; j<=60; ++j){
                if(i <=30 && j <= 30){
                    if(i == j) fac[i][j] = 1;
                }
                else if(i <=30 && j > 30){
                    fac[i][j] = cities[i][j-30];
                }
                else if(i > 30 && j > 30){
                    fac[i][j] = cities[i-30][j-30];
                }
            }
        }

//        for(int i=31; i<=60; ++i){
//            for(int j=31; j<=60; ++j){
//                printf("%lld ", fac[i][j]);
//            }
//            printf("\n");
//        }
//        for(int i=1; i<=30; ++i){
//            for(int j=1; j<=30; ++j){
//                printf("%lld ", cities[i][j]);
//            }
//            printf("\n");
//        }
        int k;
        scanf("%d", &k);
        for(int i=0; i<k; ++i){
            int v1, v2, t1, t2;
            scanf("%d%d%d%d", &v1, &v2, &t1, &t2);
            if(t1 > t2){
                printf("0\n");
            }
            else{
                if(t1 == 0) t1 = 1;
                int ss = index_of(v1);
                int ee = index_of(v2);
                matrix s0_a0(60, 30);
                for(int i=31; i<=60; ++i)
                    for(int j=1; j<=30; ++j){
                        if(i - 30 == j)
                        s0_a0[i][j] = 1;
                    }
//                for(int i=1; i<=60; ++i){
//                    for(int j=1; j<=30; ++j){
//                        printf("%lld ", s0_a0[i][j]);
//                    }
//                    printf("\n");
//                }
                LL ans = ((fac.power_mod(t2, 2008) * s0_a0)[ss][ee] -
                       (fac.power_mod(t1-1, 2008) * s0_a0)[ss][ee] + 2008) % 2008;
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
