import java.util.*;
import java.math.BigInteger;

public class Main{
    public static void main(String[] args){
        BigInteger[][][] dp = new BigInteger[61][61][61];
        for(int i=0; i<61; ++i)
            for(int j=0; j<61; ++j)
                for(int k=0; k<61; ++k)
                    dp[i][j][k] = BigInteger.ZERO;

        dp[0][0][0] = BigInteger.ONE;
        for(int i=0; i<61; ++i)
            for(int j=i; j<61; ++j)
                for(int k=j; k<61; ++k){
                    if(i +j + k == 0) continue;
                    if(i > 0) dp[i][j][k] = dp[i][j][k].add(dp[i-1][j][k]); 
                    if(j > 0) dp[i][j][k] = dp[i][j][k].add(dp[i][j-1][k]); 
                    if(k > 0) dp[i][j][k] = dp[i][j][k].add(dp[i][j][k-1]); 
                }
        Scanner in = new Scanner(System.in);
        while(in.hasNextInt()){
            int n = in.nextInt();
            System.out.println(dp[n][n][n]);
            System.out.println();
        }
    }
}
