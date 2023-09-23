package Week8;

import java.util.Scanner;

public class Practice1 {
    public static int[][] drawSnail(int n){
        int[][] tmp = new int[n][n];
        int input = n;
        int num = 1;
        int col=0,brow = -1,trow=1;

        for(int i = input; i>=0; i--){
            for(int j=0; j<input; j++){
                brow = brow + trow;
                tmp[col][brow] = num;
                num++;
            }
            input--;

            for(int k=0; k<input; k++){
                col = col + trow;
                tmp[col][brow] = num;
                num++;
            }
            trow = trow*(-1);
        }
        return tmp;
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int input = sc.nextInt();
        int[][] arr = drawSnail(input);

        for(int i=0; i<arr.length; i++){
            for(int j=0; j<arr[0].length; j++){
                System.out.print(arr[i][j] + "\t");
            }
            System.out.println("");
        }
    }
}
