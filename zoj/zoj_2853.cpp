#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <numeric>

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
    matrix operator*(const matrix& mb) const{
        int col_mb = mb.col();
        matrix ret(_row, col_mb);
        for(int i=1; i<=_row; ++i)
            for(int j=1; j<=col_mb; ++j)
                for(int k=1; k<=_col; ++k)
                    ret._m[i][j] += _m[i][k] * mb._m[k][j];
        return ret;
    }
    matrix power(int b){
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
    int col() const{ return _col; }
    int row() const{ return _row; }
private:
    double _m[201][201];
    int _row;
    int _col;
};

int main(){
    int N, M;
    while(scanf("%d%d", &N, &M) != EOF && (N || M)){
        int initial_population[201];
        for(int i=1; i<=N; ++i){
            scanf("%d", &initial_population[i]);
        }
        int T;
        scanf("%d", &T);
        matrix m(N, N, matrix::IDENTITY);
        while(T--){
            int i, j;
            double p;
            scanf("%d%d%lf", &i, &j, &p);
            m[i+1][i+1] -= p;
            m[j+1][i+1] = p;
        }
        matrix ans = m.power(M);
        double num_ans = inner_product(ans[N] + 1, ans[N] + 1 + N, initial_population + 1, double(0));
        printf("%.0f\n", num_ans);
    }
    return 0;
}
