#include <stdio.h>
#include <math.h>

const double EPS = 1e-6;

int main(){
    double L, n, C;
    while(scanf("%lf%lf%lf", &L, &n, &C) != EOF){
        if(L < 0 && n < 0 && C < 0) break;

        double l = 0, r = L / 2;
        while(fabs(l - r) > EPS){
            double mid = (l + r) / 2;
            double R = (L * L / 4 + mid * mid) / (2 * mid);
            double theta = asin(L / 2 / R);
            if(R * theta * 2 < L * (1 + n * C)){
                l = mid;
            }
            else
                r = mid;
        }
        printf("%.3f\n", l);
    }

    return 0;
}
