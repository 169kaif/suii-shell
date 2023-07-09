#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    FILE* file_pointer;
    file_pointer = fopen(argv[2], "r");
    
    //error1: improper arguments received
    if (!file_pointer || argc!=3){
        printf("error: improper args received for cat\n");
        return 1;
    } 
    else{

        int n_check =0;//set to 1 if b option is given -> numbers lines of the file
        int e_check =0;//set to 1 if E option is givne -> $ sign at the end of lines

        if(strcmp(argv[1], "-n")==0){
            n_check = 1;
        }
        else if(strcmp(argv[1], "-E")==0){
            e_check = 1;
        }
        else if((strcmp(argv[1], "-En")==0)||(strcmp(argv[1], "-nE")==0)){//handled above so that order of options does not matter
            e_check = 1;
            n_check = 1;
        }
        else if(strcmp(argv[1], "empty")==0){
            //do nothing
        }
        else{//error2: invalid options given
            printf("invalid options have been entered for cat, running cat without options :(\n");
        }

        int line_num = 1;
        char tp;
        
        if (n_check == 1){
            printf("%d) ", line_num);
            line_num++;
        }

        char temp_tp;

        while((tp=fgetc(file_pointer))!=EOF){
            if ((temp_tp == '\n') && (n_check == 1)){
                printf("%d) ", line_num);
                line_num++;
            }
            if ((tp == '\n') && (e_check == 1)){
                printf("$");
            }
            printf("%c", tp);
            temp_tp = tp;
        }

        printf("\n");
        fclose(file_pointer);
    }

    return 0;
}