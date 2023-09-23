package Week12;

import java.io.FileNotFoundException;
import java.io.FileInputStream;
import java.util.Scanner;

public class Practice {

    public static void main(String[] args) {
        BinarySearch binarySearch = new BinarySearch();
        Scanner inputStream = null;
        try {
            inputStream = new Scanner(new FileInputStream("C:\\Users\\Seungik Lee\\Desktop\\객체지향시스템설계\\input.txt"));

        }
        catch (FileNotFoundException e) {
            System.out.println("input.txt was not found");
        }
        int[] target = new int[100];
        for(int i=0; i<100; i++){
            target[i] = inputStream.nextInt();
            inputStream.nextLine();
        }

        int[] s_array = new int[100000];
        for(int i=0; i<100000; i++){
            s_array[i] = inputStream.nextInt();
            inputStream.nextLine();
        }

        for(int i=0; i<100; i++){
            int result = binarySearch.binarySearch(s_array, 0, 99999, target[i]);
            if(result == -1){
                System.out.println("target is not in the array!");
            }
            else{
                System.out.println(result);
            }
        }
    }
}
