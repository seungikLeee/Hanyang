package Week15;

import java.util.ArrayList;

public class Eratos {
    public static ArrayList sieve(int n){
        ArrayList<Integer> aList = new ArrayList<Integer>();

        for(int i=1; i<=n; i++){
            boolean prime = true;
            for(int j=2; j<=Math.sqrt(i); j++){
                if(i%j==0){
                    prime = false;
                    break;
                }
            }
            if(i>1 && prime==true){
                aList.add(i);
            }
        }

        return aList;
    }
}
