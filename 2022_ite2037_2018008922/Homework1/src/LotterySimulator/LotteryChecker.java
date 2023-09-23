package LotterySimulator;

public class LotteryChecker {
    public String rank;
    public void lotteryChecker(int m_winningnumbers[], int m_lotterynumbers[]) {
        int count=0;
        int bonus=0;
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                if(m_winningnumbers[i]==m_lotterynumbers[j]){
                    count++;
                }
            }
        }
        if(count==5){
            for(int k=0; k<6; k++){
                if(m_winningnumbers[6]==m_lotterynumbers[k]){
                    bonus=1;
                }
            }
        }

        if(count == 6){
            rank = "1";
        }
        else if(count == 5 && bonus ==1){
            rank = "2";
        }
        else if(count==5 && bonus ==0){
            rank = "3";
        }
        else if(count==4){
            rank = "4";
        }
        else if(count==3){
            rank = "5";
        }
        else{
            rank="Lose";
        }
    }
}
