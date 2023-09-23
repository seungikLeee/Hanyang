package Week8;

import Week7.*;
import Week7.util.AgeCalculator;

import java.util.Date;
import java.util.Random;

public class Practice2 {

    public static void main(String args[]){
        String[] nameArr = {
                "John", "Jacob", "Jack", "Edward", "Brian", "Sophia", "Olivia", "Zoe", "Riley", "Emma"
        };

        Random rnd = new Random();

        Person[] arr = new Person[10];
        for(int i=0; i< arr.length; i++){
            int tmpy = rnd.nextInt(50)+1950;
            int tmpm = rnd.nextInt(12);
            int tmpd = rnd.nextInt(28);
            Date tmp = new Date(tmpy,tmpm,tmpd);
            arr[i] = new Person(nameArr[rnd.nextInt(10)],tmp,null);
        }
        for(int i=0; i< arr.length; i++){
            System.out.print(AgeCalculator.calAge(arr[i]) + " ");
        }
        System.out.println("");

        arr = sort(arr,arr.length);
        for(int i=0; i< arr.length; i++){
            System.out.print(AgeCalculator.calAge(arr[i]) + " ");
        }
        System.out.println("");
    }

    public static Person[] sort(Person[] arr,int numberUsed){
        Person[] tmp = arr;
        int index, indexOfNextSmallest;
        for(index=0; index<numberUsed-1; index++){
            indexOfNextSmallest = indexOfSmallest(index, tmp, numberUsed);
            tmp = interchange(index, indexOfNextSmallest, tmp);
        }
        return tmp;
    }

    private static int indexOfSmallest(int startIndex, Person[] arr, int numberUsed){
        int indexOfMin = startIndex;
        int min = AgeCalculator.calAge(arr[startIndex]);
        int index;
        for(index = startIndex + 1; index<numberUsed; index++) {
            if (min>AgeCalculator.calAge(arr[index])) {
                min = AgeCalculator.calAge(arr[index]);
                indexOfMin = index;
            }
        }
        return indexOfMin;
    }
    private static Person[] interchange(int i, int j, Person[] arr){
        Person tmp;
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        return arr;
    }


}
