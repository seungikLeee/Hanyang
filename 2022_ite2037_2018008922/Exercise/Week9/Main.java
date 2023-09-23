package Week9;

import java.util.Date;

public class Main {
    public static void main(String[] args){
        Date JDate = new Date(1999, 1, 13);
        Date KDate = new Date(2002, 4, 4);
        Date myDate = new Date(1998, 9, 11);
        Date EDate = new Date(1995, 8, 13);
        Date NDate = new Date(2002, 5, 24);
        Date ADate = new Date(1980, 4, 18);

        Patient p1 = new Patient("John", JDate, null, "internal");
        Patient p2 = new Patient("Ik", myDate, null, "head");

        Doctor d1 = new Doctor("Kevin", KDate, null, "Samsung hospital");
        Doctor d2 = new Doctor("Edward", EDate, null, "HanyangUniversity hospital");

        Physician ph1 = new Physician("Nick", NDate, null, "HanyangUniversity hospital");
        Physician ph2 = new Physician("Alice", ADate, null, "HanyangUniversity hospital");

        System.out.println(p1.toString());
        System.out.println(p2.toString());
        System.out.println(d1.toString());
        System.out.println(d2.toString());
        System.out.println(ph1.toString());
        System.out.println(ph2.toString());

        d1.examination(p1);

        d2.examination(p1);

        ph1.examination(p1);
        ph2.examination(p1);
        ph1.examination(p2);
        ph2.examination(p2);

    }
}
