package Week15;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int n;
        Scanner sc = new Scanner(System.in);

        n = sc.nextInt();

        ArrayList<Integer> aList = Eratos.sieve(n);
        System.out.println("Input max number: " + n);

        for(int item: aList) {
            System.out.print(item + " ");
        }
    }
}
