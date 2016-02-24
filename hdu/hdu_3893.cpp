#include <iostream>
#include <cstring>
#include <cstdio>

typedef long long LL;
const LL MOD = 112233;

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
    LL _m[41][41];
    int _row;
    int _col;
};

int main(){
    int N;

//    freopen("out.txt", "w", stdout);
    while(scanf("%d", &N) != EOF){
        if((N & 1) == 0){
            printf("0\n");
            continue;
        }
        matrix F(14, 14);
        for(int i=1; i<=6; ++i)
            for(int j=1; j<=6; ++j)
                if(i != j) F[i][j] = 1;
        F[1][14] = -1;
        F[6][10] = -1;
        F[7][1] = 1;
        F[11][6] = 1;

        for(int i=8; i<=10; ++i) F[i][i-1] = 1;
        for(int i=12; i<=14; ++i) F[i][i-1] = 1;

        F = F.power_mod(N / 2, MOD);
        LL ans = 0;
        for(int i=1; i<=6; ++i){
            for(int j=1; j<=6; ++j){
                ans += F[i][j];
                ans %= MOD;
            }
        }
        printf("%lld\n", ans);
    }

    return 0;
}
