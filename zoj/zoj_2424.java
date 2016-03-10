import java.util.Scanner;
import java.math.BigInteger;

public class Main{
    public static void main(String[] args){
        int n;
        BigInteger dp[] = new BigInteger[101];
        dp[0] = new BigInteger("1");
        dp[1] = new BigInteger("1");
        for(int i=2; i<=100; ++i){
            dp[i] = new BigInteger("0");
            for(int j=1; j<=i; ++j){
                dp[i] = dp[i].add(dp[i-j].multiply(dp[j-1]));
            }
        }
        Scanner in  = new Scanner(System.in);

        while(in.hasNextInt()){
            n = in.nextInt();
            if(n == -1) break;
            System.out.println(dp[n]);
        }
    }
}
