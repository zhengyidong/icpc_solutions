import java.util.Scanner;
import java.math.BigInteger;



class Main{
    public static int n;
    public static int m;
    public static int N;
    public static int[][] limit = new int[8][2];
    public static BigInteger C(int n, int m){
        BigInteger ans = new BigInteger("1");
        for(int i=0; i<m; ++i){
            ans = ans.multiply(new BigInteger(new Integer(n - i).toString()));
            ans = ans.divide(new BigInteger(new Integer(i + 1).toString()));
        }
        return ans;
    }
    public static void solve(){

    int all_combine = 1 << n;
    BigInteger ans = new BigInteger("0");
    BigInteger a;

    for(int i=1; i<all_combine; ++i){
        int tmp_m = m;
        int num = i;
        int one_count = 0;
        for(int j=0;j<n;++j){

            if((num & 1) != 0){
                ++one_count;
                tmp_m -= (limit[j][1] + 1);
            }
            num >>= 1;
        }
        if(tmp_m < 0) continue;
        a = C(n + tmp_m - 1, n - 1);
//        a.C(n + tmp_m - 1, n - 1);
        if(one_count % 2 != 0){
            ans = ans.add(a);
        }
        else{
            ans = ans.subtract(a);
        }
    }
    a = C(n + m - 1, n - 1);
    System.out.println(a.subtract((ans)));
    }
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        N = in.nextInt();
        while((N--) != 0){
            n = in.nextInt();
            m = in.nextInt();
            for(int i=0; i<n; ++i){
                limit[i][0] = in.nextInt();
                limit[i][1] = in.nextInt();
                m -= limit[i][0];
                limit[i][1] -= limit[i][0];
            }
            if(m < 0){
                System.out.println(0);
            }
            else{
                solve();
            }
        }
    }
}
