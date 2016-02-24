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
                for(int k=1; k<=_col; ++k){
                    ret._m[i][j] += _m[i][k] * mb._m[k][j];
                    ret._m[i][j] %= 1234567891;
                }
        return ret;
    }
    matrix operator%(LL mod) const{
        matrix ret = *this;
        for(int i=1; i<=_row; ++i)
            for(int j=1; j<=_col; ++j){
//                while(ret[i][j] < 0) ret[i][j] += 10000000 * mod;
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

LL dp[31][31];
int main(){
    memset(dp, 0, sizeof(dp));
    for(int n=1; n<=30; ++n)
        for(int k=1; k<=30; ++k){
            if(n < k) dp[n][k] = 0;
            else if(k == 1) dp[n][k] = n % 1234567891;
            else dp[n][k] = (k * (dp[n-1][k] + dp[n-1][k-1])) % 1234567891;
        }

    int T;
    LL N, K;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld", &N, &K);
        if(N < K) printf("0\n");
        else{
            matrix a(K+1, K+1);
            a[1][1] = 1;
            a[2][1] = 1;
            a[2][2] = 1;
            for(int i=3; i<=K+1; ++i){
                a[i][i] = i - 1;
                a[i][i-1] = i - 1;
            }
            matrix ans = a.power_mod(N - K, 1234567891);
            LL ret = ans[K+1][1] % 1234567891;
            for(int i=2; i<=K+1; ++i){
                ret += ans[K+1][i] * dp[K][i-1];
                ret %= 1234567891;
            }
            printf("%lld\n", ret);
        }
    }

    return 0;
}
