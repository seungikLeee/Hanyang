package Week10;

public abstract class Taxi {
    int carNum;
    double distance;
    double income;

    public abstract double getPaid(double dis);

    public Taxi(int carNum){
        this.carNum = carNum;
    }

    public void doDrive(double dis){
        this.distance = dis;
        this.income = this.getPaid(dis);
    }

    public boolean earnMore(Taxi t){
        return (this.income>t.income);
    }

    public String toString(){
        return ("carNum is " + this.carNum + ", total distance is " + this.distance + ", total income is " + this.income);
    }
}
