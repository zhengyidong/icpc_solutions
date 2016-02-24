#include <iostream>
#include <cstring>
#include <cstdio>

typedef long long LL;
using namespace std;

LL a2, N, m;
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
        for(int k=1; k<=_col; ++k){
            for(int i=1; i<=_row; ++i){
                if(!_m[i][k]) continue;
                for(int j=1; j<=col_mb; ++j){
                    if(!mb._m[k][j]) continue;
                    ret._m[i][j] += _m[i][k] * mb._m[k][j];
                }
            }
        }
        return ret;
    }
    matrix operator%(LL mod) const{
        matrix ret = *this;
        for(int i=1; i<=_row; ++i)
            for(int j=1; j<=_col; ++j){
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
    LL _m[4][4];
    int _row;
    int _col;
};

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld%lld", &a2, &N, &m);
        matrix factor(4, 4);
        LL C = 2 * a2;
        factor[1][1] = 1, factor[1][2] = 1;
        factor[2][2] = (C % m * C % m); factor[2][3] = 1; factor[2][4] = (-2 * C) % m;
        factor[3][2] = 1;
        factor[4][2] = C % m, factor[4][4] = -1;

        matrix ans = factor.power_mod(N - 1, m);
        LL tmp = (ans[1][1] + a2 * a2 % m * ans[1][2] % m + ans[1][3] + a2 * ans[1][4] % m) % m;
        printf("%lld\n", (tmp + m) % m);
    }
    return 0;
}
