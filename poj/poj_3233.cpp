#include <iostream>
#include <cstring>
#include <cstdio>

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
int main(){
    int n, m, k;
    while(scanf("%d%d%d", &n, &k, &m) != EOF){
        matrix A(n, n);
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j){
                scanf("%lld", &A[i][j]);
            }
        matrix factor(2*n, 2*n);
        matrix S0_B0(2*n, n);
        for(int i=n+1; i<=2*n; ++i)
            for(int j=1; j<=n; ++j){
                S0_B0[i][j] = A[i-n][j];
            }
        for(int i=1; i<=n; ++i)
            for(int j=1; j<=n; ++j){
                if(i == j) factor[i][j] = 1;
            }
        for(int i=1; i<=n; ++i)
            for(int j=n+1; j<=2*n; ++j){
                if(i == j-n) factor[i][j] = 1;
            }
        for(int i=n+1; i<=2*n; ++i)
            for(int j=n+1; j<=2*n; ++j){
                factor[i][j] = A[i-n][j-n];
            }
        matrix ans = (factor.power_mod(k, m) * S0_B0) % m;
        for(int i=1; i<=n; ++i){
            for(int j=1; j<=n; ++j){
                if(j == 1) printf("%lld", ans[i][j]);
                else printf(" %lld", ans[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}

