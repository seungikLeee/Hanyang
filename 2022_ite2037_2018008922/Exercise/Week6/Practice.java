package Week6;

import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.Random;

public class Practice {
    public static void main(String args[]){
        Scanner keyboard = new Scanner(System.in);
        String input1 = keyboard.nextLine();

        StringTokenizer stk = new StringTokenizer(input1," ");

        String name1 = stk.nextToken();
        System.out.println("test1 " + name1);
        String date = stk.nextToken();
        System.out.println("test2 "+ date);

        StringTokenizer stk1 = new StringTokenizer(date,".");
        String syear = stk1.nextToken();
        String smonth = stk1.nextToken();
        String sday = stk1.nextToken();

        int year=Integer.parseInt(syear);
        int month1=Integer.parseInt(smonth);
        int day1=Integer.parseInt(sday);
        boolean yeartest = true;

        if(year<1000||year>9999){
            yeartest = false;
        }
        Student stu1 = new Student(name1, year, month1, day1);

        String input2 = keyboard.nextLine();
        Student stu2 = new Student(input2,year);

        if(stu1.checkDate(date)&&yeartest) {
            System.out.println(stu1.getName() + " " + stu1.getYear() + "/" + stu1.getMonth() + "/" + stu1.getDay() + " age :" + stu1.calAge());
            System.out.println(stu2.getName() + " " + stu2.getYear() + "/" + stu2.getMonth() + "/" + stu2.getDay() + " age :" + stu2.calAge());
            if (stu1.isOlder(stu2)) {
                System.out.println(stu1.getName() + " is older than " + stu2.getName());
            } else {
                System.out.println(stu2.getName() + " is older than " + stu1.getName());
            }
        }
        else{
            System.out.println("invalid input");
        }
    }
}
