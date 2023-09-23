package Week6;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Random;

public class Student {
    private String name;
    private int year;
    private int month;
    private int day;

    public Student(String name, int year, int month, int day){
        this.name = name;
        this.year = year;
        this.month = month;
        this.day = day;
    }

    public Student(String name, int year){
        this.name = name;
        this.year = year;
        Random rnd = new Random();
        String tmpdate;
        do {
            this.month = rnd.nextInt(12) + 1;
            if (this.month == 2) {
                this.day = rnd.nextInt(28) + 1;
            } else {
                this.day = rnd.nextInt(31) + 1;
            }
            String tmpyear = Integer.toString(this.year);
            String tmpmonth = Integer.toString(this.month);
            String tmpday = Integer.toString(this.day);
            tmpdate = tmpyear + "." + tmpmonth + "." + tmpday;
        }while(!checkDate(tmpdate));
    }

    public String getName() {
        return name;
    }

    public int getYear() {
        return year;
    }

    public int getMonth() {
        return month;
    }

    public int getDay(){
        return day;
    }

    boolean checkDate(String date){
        try{
            SimpleDateFormat dateFormatParser = new SimpleDateFormat("yyyy.MM.dd");
            dateFormatParser.setLenient(false);
            dateFormatParser.parse(date);
            return true;
        }
        catch(Exception e){
            return false;
        }
    }

    int calAge(){
        Calendar current = Calendar.getInstance();
        int currentYear = current.get(Calendar.YEAR);
        int currentMonth = current.get(Calendar.MONTH)+1;
        int currentDay = current.get(Calendar.DAY_OF_MONTH);

        int age = currentYear-this.year;

        if(this.month*100+this.day>currentMonth*100 + currentDay){
            age--;
        }
        return age;
    }

    boolean isOlder(Student stu){
        return ((getMonth()<stu.getMonth())||(month==stu.getMonth()&&day<stu.getDay()));
    }

}


