#include <iostream>
#include <cstring>
#include <cstdio>
#include <numeric>

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
        _row = mb._row;
        _col = mb._col;
        memcpy(_m, mb._m, sizeof(_m));
    }
    LL* operator[](int i){
        return _m[i];
    }
//    LL tr() const{
//        int ans = 0;
//        for(int i=1, len=std::min(_row,_col); i<=len; ++i) ans += _m[i][i];
//        return ans;
//    }
    matrix operator*(const matrix& mb) const{
        matrix ret(_row, mb._col);
        for(int k=1; k<=_col; ++k)
            for(int i=1; i<=_row; ++i){
                if(!_m[i][k]) continue;
                for(int j=1; j<=mb._col; ++j){
                    if(!mb._m[k][j]) continue;
                    ret._m[i][j] += _m[i][k] * mb._m[k][j];
                }
            }
        return ret;
    }
//    void _self_mul() const{
//        memset(_inner, 0, sizeof(_inner));
//        for(int i=1; i<=_row; ++i)
//            for(int j=1; j<=_col; ++j)
//                for(int k=1; k<=_col; ++k)
//                    _inner[i][j] += _inner[i][k] * _inner[k][j];
//        memcpy(_m, _inner, sizeof(_inner));
//    }
//    matrix operator%(LL mod) const{
//        matrix ret = *this;
//        for(int i=1; i<=_row; ++i)
//            for(int j=1; j<=_col; ++j){
//                while(ret[i][j] < 0) ret[i][j] += 1000000 * mod;
//                ret[i][j] %= mod;
//            }
//        return ret;
//    }
    matrix power_mod(LL b){
        matrix ans(_row, _col, IDENTITY);
        matrix a = *this;
//        a = a;
        while(b > 0){
            if(b & 1) ans = (ans * a);
            b >>= 1;
            a = (a * a);
        }
        return ans;
    }
//    matrix _self_power(LL b){

//    }
//    int col() const{ return _col; }
//    int row() const{ return _row; }
private:
    LL _m[105][105];
    int _row;
    int _col;
};

int main(){
    int n, m, k;
    char cmd[3];
    int index_cat;
    while(scanf("%d%d%d", &n, &m, &k) != EOF && (n || m || k)){
        matrix A(n+1, n+1, matrix::IDENTITY);
//        for(int i=1; i<=n+1; ++i)
//            for(int j=1; j<=n+1; ++j)
//                A[i][j] = 0;
//        A._col = n + 1;
//        A._row = n + 1;
        for(int j=1; j<=k; ++j){
            scanf("%s%d", cmd, &index_cat);
            if(strcmp(cmd, "g") == 0){
                ++A[index_cat+1][1];
            }
            else if(strcmp(cmd, "e") == 0){
                for(int i=1; i<=n+1; ++i) A[index_cat+1][i] = 0;
            }
            else{
                int another;
                scanf("%d", &another);
                for(int i=1; i<=n+1; ++i) swap(A[index_cat+1][i], A[another+1][i]);
            }
        }
        A = A.power_mod(m);
        for(int i=1; i<=n; ++i){
            if(i != 1) printf(" ");
            printf("%lld", A[i+1][1]);
        }
        printf("\n");
    }
    return 0;
}
