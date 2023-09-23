package Week5;

import java.util.Random;
import java.util.Scanner;

public class Practice2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Random rnd = new Random();
        
        String input = sc.next();
        
        int computerchoice = rnd.nextInt(3);
        String result = null;
        if(input.equals("rock")){
            if(computerchoice == 0){
                    result = "Draw";
            }
            else if(computerchoice == 1){
                result = "You win";
            }
            else if(computerchoice == 2){
                result = "You lose";
            }
        }
        else if(input.equals("scissors")){
            if(computerchoice == 0){
                result = "You lose";
            }
            else if(computerchoice == 1){
                result = "Draw";
            }
            else if(computerchoice == 2){
                result = "You win";
            }
        }
        else if(input.equals("paper")){
            if(computerchoice == 0){
                result = "You win";
            }
            else if(computerchoice == 1){
                result = "You lose";
            }
            else if(computerchoice == 2){
                result = "Draw";
            }
        }
        
        
        if(computerchoice==0){
            System.out.println("Computer's choice : rock");
        }
        else if(computerchoice==1){
            System.out.println("Computer's choice : scissors");
        }
        else{
            System.out.println("Computer's choice : paper");
        }
        
        System.out.println(result);
    }

}
