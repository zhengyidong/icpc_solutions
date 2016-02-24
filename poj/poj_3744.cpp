#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

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
    matrix power(LL b){
        matrix ans(_row, _col, IDENTITY);
        matrix a = *this;
        while(b > 0){
            if(b & 1) ans = (ans * a);
            b >>= 1;
            a = (a * a);
        }
        return ans;
    }
    int col() const{ return _col; }
    int row() const{ return _row; }
private:
    double _m[11][11];
    int _row;
    int _col;
};

int main(){
    int N;
    double p;
    int mines[11];
    while(scanf("%d%lf", &N, &p) != EOF){
        double init = 1;
        for(int i=0; i<N; ++i) scanf("%d", &mines[i]);
        sort(mines, mines + N);
        bool cont = false;
        for(int i=0; i<N-1; ++i){
            if(mines[i] + 1 == mines[i+1]){
                cont = true;
            }
        }
        if(cont || mines[0] == 1){
            printf("%.7f\n", 0.0);
            continue;
        }

        matrix F(2, 2);
        F[1][1] = p, F[1][2] = 1 - p;
        F[2][1] = 1, F[2][2] = 0;
        int cur = 1;
        for(int i=0; i<N; ++i){
            F = F.power(mines[i] - cur - 1);
            init = (F[1][1] * init) * (1 - p);
            cur = mines[i] + 1;
            F[1][1] = p, F[1][2] = 1 - p;
            F[2][1] = 1; F[2][2] = 0;
        }

        printf("%.7f\n", init);

    }
    return 0;
}
