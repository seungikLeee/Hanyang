package Week13;

public interface Calculator {
    ComplexNumber add(ComplexNumber c1, ComplexNumber c2);
    ComplexNumber sub(ComplexNumber c1, ComplexNumber c2);
    ComplexNumber mul(ComplexNumber c1, ComplexNumber c2);
    ComplexNumber.RealNumber add(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2);
    ComplexNumber.RealNumber sub(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2);
    ComplexNumber.RealNumber mul(ComplexNumber.RealNumber r1, ComplexNumber.RealNumber r2);

    default void printResult(ComplexNumber c){
        System.out.println("Real : "+ c.getReal().toString() + ", Imaginary : " + c.getImaginary().toString());
    }

}
