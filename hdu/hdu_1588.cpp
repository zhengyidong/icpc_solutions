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
    LL _m[11][11];
    int _row;
    int _col;
};

int main(){
    LL k, b, n, M;
    while(scanf("%lld%lld%lld%lld", &k, &b, &n, &M) != EOF){
        if(n == 0) printf("0\n");
        else{
            matrix a(2, 2);
            a[1][1] = 1, a[1][2] = 1;
            a[2][1] = 1, a[2][2] = 0;
            matrix a_b = a.power_mod(b, M);
            matrix B = a.power_mod(k, M);
            matrix fac(4, 4);
            fac[1][1] = 1, fac[1][2] = 0, fac[1][3] = 1, fac[1][4] = 0;
            fac[2][1] = 0, fac[2][2] = 1, fac[2][3] = 0, fac[2][4] = 1;
            fac[3][1] = 0, fac[3][2] = 0, fac[3][3] = B[1][1], fac[3][4] = B[1][2];
            fac[4][1] = 0, fac[4][2] = 0, fac[4][3] = B[2][1], fac[4][4] = B[2][2];

            matrix S0_B0(4, 2);
            S0_B0[1][1] = 0, S0_B0[1][2] = 0;
            S0_B0[2][1] = 0, S0_B0[2][2] = 0;
            S0_B0[3][1] = 1, S0_B0[3][2] = 0;
            S0_B0[4][1] = 0, S0_B0[4][2] = 1;
            matrix Sn_Bn = fac.power_mod(n, M) * S0_B0;
            matrix Sn(2, 2);
            Sn[1][1] = Sn_Bn[1][1], Sn[1][2] = Sn_Bn[1][2];
            Sn[2][1] = Sn_Bn[2][1], Sn[2][2] = Sn_Bn[2][2];
            matrix ans = a_b * Sn;
            printf("%lld\n", ans[2][1] % M);

        }
    }
    return 0;
}
