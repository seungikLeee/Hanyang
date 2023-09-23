package Week5;

import java.util.Scanner;

public class Practice1 {
    public static void main(String[] args){
        Scanner sc= new Scanner(System.in);
        int input = sc.nextInt();

        for(int i=1; i*input<101; i++){
            System.out.print(input*i + ", ");
        }
    }
}
