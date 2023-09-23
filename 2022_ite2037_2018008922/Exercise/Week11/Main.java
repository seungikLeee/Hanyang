package Week11;

import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            Scanner keyboard = new Scanner(System.in);
            int a = keyboard.nextInt();
            int b = keyboard.nextInt();

            isCoprime(a, b);
        }
        catch (InputMismatchException e) {
            System.out.println("input illegal input type; Type \"LEGAL\" integer number!");
        }
    }

    public static boolean isCoprime(int a, int b) {
        try {
            if (a <= 1 || b <= 1) {
                throw new MyException("one of two integer is less or equal to 1; Change input integers more than 1! ");
            } else if (a == b) {
                throw new MyException("two integer are same number; Change input integers not same!");
            } else if (a >= 10000 && b >= 10000) {
                throw new MyException("both two integer are lager than 10000; Change both input integers less than 10000!");
            }

            int result = 0;
            if (a <= b) {
                for (int i = a; i > 0; i--) {
                    if ((a % i == 0) && (b % i == 0)) {
                        result = i;
                        break;
                    }
                }
            } else {
                for (int i = b; i > 0; i--) {
                    if ((a % i == 0) && (b % i == 0)) {
                        result = i;
                        break;
                    }
                }
            }
            if(result == 1){
                System.out.println("two integers are coprime!");
                return true;
            }
            else{
                System.out.println("two integers are not coprime!");
                return false;
            }

        }
        catch (MyException e) {
            System.out.println(e.getMessage());
        }
        return false;
    }
}
