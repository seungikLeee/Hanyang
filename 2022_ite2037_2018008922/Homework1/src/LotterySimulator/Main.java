package LotterySimulator;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        while(1==1) {
            System.out.print("<< ");
            Scanner keyboard = new Scanner(System.in);
            int input = keyboard.nextInt();
            if (input == 0) {
                System.out.print(">> End of program");
                break;
            }
            LotteryGenerator m_lotteryGenerator = new LotteryGenerator();
            m_lotteryGenerator.generateWinnerNum();
            System.out.print(">> Round Winning number : ");
            for (int i = 0; i < 7; i++) {
                if (i == 6) {
                    System.out.print("+ ");
                }
                System.out.print(m_lotteryGenerator.m_WinningNumbers[i] + " ");
            }
            System.out.println("");

            for(int i=0; i<input; i++) {
                m_lotteryGenerator.generateLotteryNum();
                System.out.print(">> Lottery number : ");
                for (int j = 0; j < 6; j++) {
                    System.out.print(m_lotteryGenerator.m_LotteryNumbers[j] + " ");
                }
                LotteryChecker m_lotteryChecker = new LotteryChecker();
                m_lotteryChecker.lotteryChecker(m_lotteryGenerator.m_WinningNumbers,m_lotteryGenerator.m_LotteryNumbers);

                if(m_lotteryChecker.rank=="Lose") {
                    System.out.print(m_lotteryChecker.rank);
                }
                else if(m_lotteryChecker.rank=="1"){
                    System.out.print("Winner " + "(" + m_lotteryChecker.rank + "st place)");
                }
                else if(m_lotteryChecker.rank=="2"){
                    System.out.print("Winner " + "(" + m_lotteryChecker.rank + "nd place)");
                }
                else{
                    System.out.print("Winner " + "(" + m_lotteryChecker.rank + "th place)");
                }

                System.out.println("");
            }
        }
    }
}

