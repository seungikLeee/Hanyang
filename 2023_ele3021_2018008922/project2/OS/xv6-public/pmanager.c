#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[])
{
    char buf[100];
    
    while (1) {
        printf(1, "Enter a command: ");
        gets(buf,sizeof(buf));
        
        if(buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't' && buf[4] == '\n'){
            printf(1, "Exiting program!\n");
            exit();
            break;
        }
        else if(buf[0] == 'l' && buf[1] == 'i' && buf[2] == 's' && buf[3] == 't' && buf[4] == '\n'){
            if(p_list()==0){
                //printf(1,"List success!\n");
            }
            else{
                printf(1, "List fail!\n");
            }
        }
        else if(buf[0] == 'k' && buf[1] == 'i' && buf[2] == 'l' && buf[3] == 'l'){
            char tmp[20] = "";
            int i = 4;
            while(1){
                if(buf[i]=='\n'){
                    break;
                }
                else if(buf[i]==' '){
                    i++;
                    continue;
                }
                else{
                    tmp[i-5]=buf[i];
                    i++;
                }
            }
            if (i>=6){  
                int pi = atoi(tmp);     //pid extract
                if (kill(pi) == 0){
                    //printf(1, "Kill process %d success\n", pi);    
                }
                else{
                    printf(1, "Kill process %d fail!\n", pi);
                }
            }
            else{
                printf(1,"Missing pid for kill!\n");
            }
        
        }
        else if(buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'e' && buf[3] == 'c' && buf[4] == 'u' && buf[5] == 't' && buf[6] =='e' ){
            char tmp[60] = "";
            char tmp2[20] = "";
            int i = 7;
            while(1){
                if(buf[i]=='\n'){
                    break;
                }
                else if(buf[i]==' '){
                    if(i==7){
                        i++;
                        continue;
                    }
                    else{
                        break;
                    }
                }
                else{
                    tmp[i-8]=buf[i];
                    i++;
                }
            }
            tmp[i]='\0';

            if (i>=9){ 
                int j = i+1;
                while(1){ 
                    if(buf[i]=='\n'){
                        break;
                    }
                    else if(buf[i]==' '){
                        i++;
                        continue;
                    }
                    else{
                        tmp2[i-j]=buf[i];
                        i++;
                    }
                }
                if (i>j){ 
                    int stacksize = atoi(tmp2);     // stacksize extract
                    //printf(1, "path: %s, stacksize: %d\n", tmp, stacksize);
                    char *argv[2];
                    argv[0] = tmp;
                    argv[1] = 0;
                    if(fork()==0){
                        if (exec2(argv[0], argv, stacksize)==0){
                            //printf(1, "Execute success!\n");
                        }
                        else{
                            printf(1, "Execute fail!\n");
                        }
                    }
                    else{
                        wait();
                    }
                }
                else{
                    printf(1, "Missing argument for execute!\n");
                }
            }
            else{
                printf(1,"Missing argument for execute!\n");
            }
        }
        else if(buf[0] == 'm' && buf[1] == 'e' && buf[2] == 'm' && buf[3] == 'l' && buf[4] == 'i' && buf[5] == 'm' ){
            char tmp[20] = "";
            char tmp2[20] = "";
                
            int i = 6;
            while(1){
                if(buf[i]=='\n'){
                    break;
                }
                else if(buf[i]==' '){
                    if(i==6){
                        i++;
                        continue;
                    }
                    else{
                        break;
                    }
                }
                else{
                    tmp[i-7]=buf[i];
                    i++;
                }
            }
            if (i>=8){ 
                int pi = atoi(tmp);     // pid extract
                int j = i+1;
                while(1){ 
                    if(buf[i]=='\n'){
                        break;
                    }
                    else if(buf[i]==' '){
                        i++;
                        continue;
                    }
                    else{
                        tmp2[i-j]=buf[i];
                        i++;
                    }
                }
                if (i>j){ 
                    int limit = atoi(tmp2);     // limit extract
                    
                    if (setmemorylimit(pi, limit)==0){
                        //printf(1, "pid %d, limit %d\n", pi, limit);
                        printf(1, "Memory limit success!\n");
                    }
                    else{
                        printf(1, "Memory limit fail!\n");
                    }
                }
                else{
                    printf(1, "Missing argument for memlim!\n");
                }
            }
            else{
                printf(1,"Missing argument for memlim!\n");
            }
        }
        else{
            printf(1, "Invalid command!\n");
        } 
    }

    return 0;
}
