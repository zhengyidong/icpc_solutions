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
    double* operator[](int i){
        return _m[i];
    }
    double tr() const{
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
//    matrix operator%(LL mod) const{
//        matrix ret = *this;
//        for(int i=1; i<=_row; ++i)
//            for(int j=1; j<=_col; ++j){
//                while(ret[i][j] < 0) ret[i][j] += mod;
//                ret[i][j] %= mod;
//            }
//        return ret;
//    }
    matrix power(LL b){
        matrix ans(_row, _col, IDENTITY);
        matrix a = *this;
        a = a;
        while(b > 0){
            if(b & 1) ans = (ans * a);
            b >>= 1;
            a = (a * a);
        }
        return ans;
    }
//    matrix power_mod(LL b, LL n){
//        matrix ans(_row, _col, IDENTITY);
//        matrix a = *this;
//        a = a % n;
//        while(b > 0){
//            if(b & 1) ans = (ans * a) % n;
//            b >>= 1;
//            a = (a * a) % n;
//        }
//        return ans;
//    }
    int col() const{ return _col; }
    int row() const{ return _row; }
private:
    double _m[31][31];
    int _row;
    int _col;
};

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        double init_water[21];
        int N;
        scanf("%d", &N);
        matrix a(N, N);
        for(int i=1; i<=N; ++i) scanf("%lf", &init_water[i]);
        for(int i=1; i<=N; ++i){
            int K;
            scanf("%d", &K);
            int num;
            for(int j=0; j<K; ++j){
                scanf("%d", &num);
                a[num][i] += 1.0 / K;
            }
            if(K == 0) a[i][i] += 1;
        }
        int M;
        scanf("%d", &M);
        matrix ans = a.power(M);
        for(int i=1; i<=N; ++i){
            double res = 0;
            for(int j=1; j<=N; ++j){
                res += ans[i][j] * init_water[j];
            }
            printf("%.2f", res);
            if(i != N) printf(" ");
        }
        printf("\n");

    }
    return 0;
}

