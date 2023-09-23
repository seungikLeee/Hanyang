package LotterySimulator;

import java.util.Random;

public class LotteryGenerator {
    public int m_WinningNumbers[] = new int[7];
    public int m_LotteryNumbers[] = new int[6];

    Random rnd = new Random();

    public void generateWinnerNum() {
        for (int i = 0; i < 7; i++) {
            m_WinningNumbers[i] = rnd.nextInt(10) + 1;
            for (int j = 0; j < i; j++) {
                if (m_WinningNumbers[i] == m_WinningNumbers[j]) {
                    i--;
                }
            }
        }
    }

    public void generateLotteryNum() {
        for (int i = 0; i < 6; i++) {
            m_LotteryNumbers[i] = rnd.nextInt(10) + 1;
            for (int j = 0; j < i; j++) {
                if (m_LotteryNumbers[i] == m_LotteryNumbers[j]) {
                    i--;
                }
            }
        }
    }
}


