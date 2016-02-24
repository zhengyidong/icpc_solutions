#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
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
    LL _m[101][101];
    int _row;
    int _col;
};

int main(){
    int M;
    char T[101];
    LL num[101];
    while(scanf("%d%s", &M, T) != EOF){
        int len = strlen(T);
        for(int i=0; i<len; ++i){
            if(T[i] == '1') num[i] = 1;
            else num[i] = 0;
        }
        matrix m(len, len);
        for(int i=1; i<=len; ++i){
            for(int j=1; j<=len; ++j){
                if(i == j) m[i][j] = 1;
                if(j == (i - 1 == 0 ? i - 1 + len : i - 1)) m[i][j] = 1;
            }
        }
//        for(int i=1; i<=len; ++i){
//            for(int j=1; j<=len; ++j){
//                printf("%lld ", m[i][j]);
//            }
//            printf("\n");
//        }
        matrix ans = m.power_mod(M, 2);
        for(int i=1; i<=len ;++i){
            printf("%lld", inner_product(ans[i] + 1, ans[i] + len + 1, num, (LL)0) % 2);
        }
        printf("\n");
    }
    return 0;
}
