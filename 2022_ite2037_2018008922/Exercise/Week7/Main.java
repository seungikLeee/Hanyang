package Week7;

import java.util.Date;
import Week7.util.*;

public class Main {
    public static void main(String[] args){
        Date JDate1 = new Date(1999, 4, 13);
        Date JDate2 = new Date(2002, 4, 14);
        Date myDate1 = new Date(1998, 9, 11);

        Person p1 = new Person("John", JDate1, JDate2);
        Person p2 = new Person( "Ik", myDate1, null);
        System.out.println(p1.toString() + " age is " + AgeCalculator.calAge(p1));
        System.out.println(p2.toString() + " age is " + AgeCalculator.calAge(p2));
        if(AgeCalculator.isOlder(p1,p2) == 1){
            System.out.println(p1.getName() + " is older than " + p2.getName());
        }
        else if(AgeCalculator.isOlder(p1,p2) == 0){
            System.out.println(p1.getName() + " and " + p2.getName() + "are same age");
        }
        else{
            System.out.println(p2.getName() + " is older than " + p1.getName());
        }
    }
}
