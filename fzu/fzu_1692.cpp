#include <iostream>
#include <cstring>
#include <cstdio>

typedef long long LL;

using namespace std;

class circulant_matrix{
public:
    enum option{ZERO, IDENTITY};
    int order()const { return _order; }
    circulant_matrix(int order, option opt=ZERO):_order(order){
        memset(_m, 0, sizeof(_m));
        if(opt == IDENTITY) _m[1] = 1;
    }
    circulant_matrix(const circulant_matrix& mb){
        _order = mb._order;
        memcpy(_m, mb._m, sizeof(_m));
    }
    LL& operator[](int index){
        return _m[index];
    }
    circulant_matrix operator*(const circulant_matrix& mb) const{
        circulant_matrix ret(_order);
        for(int i=1; i<=_order; ++i)
            for(int j=1; j<=_order; ++j)
                ret._m[i] += _m[j] * mb._m[(i-j+_order)%_order + 1];
        return ret;
    }
    circulant_matrix operator%(int mod) const{
        circulant_matrix ret = *this;
        for(int i=1; i<=_order; ++i){
            while(ret[i] < 0) ret[i] += mod;
            ret[i] %= mod;
        }
        return ret;
    }
    circulant_matrix power_mod(LL b, LL n){
        circulant_matrix ans(_order, IDENTITY);
        circulant_matrix a = *this;
        a = a % n;
        while(b > 0){
            if(b & 1) ans = (ans * a) % n;
            b >>= 1;
            a = (a * a) % n;
        }
        return ans;
    }

private:
    LL _m[1001];
    int _order;
};

int main(){
    int T;
    LL init[1001];
    LL n, m, L, R, M;
    scanf("%d", &T);
    while(T--){
        scanf("%lld%lld%lld%lld%lld", &n, &m, &L, &R, &M);
        for(int i=0; i<n; ++i) scanf("%lld", &init[i]);

        circulant_matrix F(n);
        F[2] = L; F[n] = R; F[1] = 1;
        F = F.power_mod(m, M);
        for(int i=0; i<n; ++i){
            LL ans = 0;
            for(int j=0; j<n; ++j){
                ans += F[(j - i + n) % n + 1] * init[j];
                ans %= M;
            }
            if(i != 0) printf(" ");
            printf("%lld", ans);
        }
        printf("\n");
    }
    return 0;
}
