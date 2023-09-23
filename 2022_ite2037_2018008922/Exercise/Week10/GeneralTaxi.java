package Week10;

public class GeneralTaxi extends Taxi{
    double farePerKilometer;
    double baseDistance = 3;
    double baseFee = 3;

    private static boolean consistent(double farePerKilometer,double baseDistance, double baseFee){
        return (farePerKilometer>baseFee/baseDistance);
    }

    public GeneralTaxi(int carNum, double rate){
        super(carNum);
        if(!consistent(rate,baseDistance,baseFee)){
            System.out.println("Inconsistent condition");
            System.exit(1);
        }
        else{
            super.carNum = carNum;
            this.farePerKilometer = rate;
        }
    }

    @Override
    public String toString(){
        return super.toString() + ", rate per kilometer is " + this.farePerKilometer;
    }

    @Override
    public double getPaid(double dis){
        double fee=0;
        if(dis<=baseDistance){
            fee = baseFee;
        }
        else{
            fee = baseFee + (dis-baseDistance)*farePerKilometer;
        }
        return fee;
    }
}
