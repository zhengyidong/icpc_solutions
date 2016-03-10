import java.util.Scanner;
import java.math.BigInteger;

public class Main{
    public static final int MAX = 10005;
    public static boolean[] visited = new boolean[MAX];
    public static int[] prime = new int[MAX];
    public static int cnt = 0;
    public static final BigInteger MINUS_ONE = new BigInteger("-1");
    public static final BigInteger TWO = new BigInteger("2");
    public static final BigInteger THREE = new BigInteger("3");
    public static final BigInteger THIRTY = new BigInteger("30");
    public static final BigInteger MOD = new BigInteger("1000000007");
    public static void prime_table(int n){
        for(int i=2; i<=n; ++i){
            if(!visited[i]){
                prime[cnt++] = i;
                for (int j=i*i; j<=n; j+=i)
                    visited[j] = true;
            }
        }
    }
    public static BigInteger sumOfPower4(long n){
        BigInteger num = new BigInteger(Long.toString(n));
        BigInteger tmp_ans = BigInteger.ONE;
        tmp_ans = tmp_ans.multiply(num);
        tmp_ans = tmp_ans.multiply(num.add(BigInteger.ONE));
        tmp_ans = tmp_ans.multiply(num.multiply(TWO).add(BigInteger.ONE));
        tmp_ans = tmp_ans.multiply(num.multiply(num).multiply(THREE).add(num.multiply(THREE)).add(MINUS_ONE));
        tmp_ans = tmp_ans.divide(THIRTY);
        return tmp_ans;
    }
    public static void main(String[] args){
        Scanner in = new Scanner(System.in);
        prime_table(10001);
        long[] p_factors = new long[100];
        long[] max_mul = new long[100];
        BigInteger[] terms = new BigInteger[100];
        int T = in.nextInt();

        while((T--) != 0){
            int num_p_f = 0;
            long n = in.nextLong();
            long tmp_n = n;
            for(int i=0; i<cnt; ++i){
                if(tmp_n % prime[i] == 0){
                    p_factors[num_p_f++] = prime[i];
                    while(tmp_n % prime[i] == 0){
                        tmp_n /= prime[i];
                    }
                }
            }
            if(tmp_n != 1){
                p_factors[num_p_f++] = tmp_n;
            }
            BigInteger all_sum = sumOfPower4(n);
            BigInteger ans = BigInteger.ZERO;
            int all_combines = 1 << num_p_f;
            BigInteger tmp_ans = null;
            for(int i=1; i<all_combines; ++i){
                long pro = 1;
                int num = i;
                int one_count = 0;
                for(int j=0; j<num_p_f; ++j){
                    if((num & 1) != 0){
                        ++one_count;
                        pro *= p_factors[j];
                        BigInteger p_f = new BigInteger(Long.toString(pro));
                        p_f = p_f.pow(4);
                        tmp_ans = sumOfPower4(n / pro);
                        tmp_ans = tmp_ans.multiply(p_f);
                    }
                    num >>= 1;
                }
                if(one_count % 2 != 0) ans = ans.add(tmp_ans);
                else ans = ans.subtract(tmp_ans);
            }
            ans = all_sum.subtract(ans);
            ans = ans.mod(MOD);
            System.out.println(ans);
        }
    }
}
