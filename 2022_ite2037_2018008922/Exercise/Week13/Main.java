package Week13;

public class Main {
    public static void main(String[] args) {
        ComplexNumberCalculator calc = new ComplexNumberCalculator();
        ComplexNumber c1 = new ComplexNumber(new ComplexNumber.RealNumber(4, 10), new ComplexNumber.RealNumber(3,2));
        ComplexNumber c2 = new ComplexNumber(new ComplexNumber.RealNumber(3, 10), new ComplexNumber.RealNumber(-4, 2));

        calc.printResult(calc.sub(c1, c2));
        calc.printResult(calc.mul(c1, c2));
    }
}
