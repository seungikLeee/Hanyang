package Week4;

import java.util.Scanner;

public class Practice2 {
    public static void main(String[] args){
        Scanner keyboard = new Scanner(System.in);
        int dividend = keyboard.nextInt();
        int divisor = keyboard.nextInt();

        int quotient = dividend/divisor;
        int remainder = dividend%divisor;

        System.out.println("dividend = " + dividend);
        System.out.println("divisor = " + divisor);
        System.out.println("quotient = " + quotient);
        System.out.println("remainder = " + remainder);

    }
}
