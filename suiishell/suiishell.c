#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

//function to call system using thread
void* altSys(void* final_string){

    char* fstr = final_string;
    printf("I'm actually in here!\n");
    system(fstr);

}

//function to check if command is a valid external command
int extCheck(char* cmd){
    if (strcmp(cmd, "ls")==0){
        return 1;
    }
    if (strcmp(cmd, "cat")==0){
        return 1;
    }
    if (strcmp(cmd, "date")==0){
        return 1;
    }
    if (strcmp(cmd, "rm")==0){
        return 1;
    }
    if (strcmp(cmd, "mkdir")==0){
        return 1;
    }
    return 0;
}

void callECHO(char* opt, char* pargs){
    int p_check = 0;//set to 1 if printing is required
    int pargs_check =0;//set to 1 if pargs null need not be checked
    if (opt != NULL){
        if (strcmp(opt, "--help")==0){
            pargs_check = 1;
            printf("--help : displays the help menu \n");
            printf("-n : does not output trailing newline \n");
        }
        else if (strcmp(opt, "-n")==0){
            p_check = 1;
        }
        else{//error1: checking if invalid options have been passed
            printf("invalid options passed :(\n");
        }
    }
    else{
        p_check = 1;
    }

    //edgecase: nothing is passed for pargs so it may throw error during printf
    if ((pargs == NULL)&&(pargs_check!=1)){//error2: no arguments passed for echo error 
        printf("\n");
    }
    else{
        if (p_check == 1){
            printf("%s\n", pargs);
        }
    }
}

void callPWD(char* opt, char* pargs){

    int dcheck = 0;//executes else at the bottom if 0
    
    if(opt != NULL){
        if (strcmp(opt, "-L")==0){//-L....pwd behaves as if L was specified
            dcheck = 1;
            callPWD(NULL, pargs);
        }
        else if(strcmp(opt, "-P")==0){//-P assumed by default if no option is mentioned
            dcheck = 1;
            callPWD(NULL, pargs);
        }
        else if((strcmp(opt, "-LP")==0)||(strcmp(opt, "-PL")==0)){
            dcheck = 1;
            callPWD(NULL, pargs);
        }
        else{//error1: invalid options passed for pwd
            printf("invalid options passed for pwd :(\n");
        }
        
    }
    if (pargs != NULL){//error2: unexpected arguments passed
        printf("expected no arguments for pwd :(\n");
    }
    else{
        if (dcheck==0){
            char pwd[1024];
            getcwd(pwd, 1024);
            printf("%s\n", pwd);
    }
    }
}

int callCD(char* opt, char* pargs){
    
    if(opt != NULL){
        printf("invalid options passed");
    }

    if (pargs == NULL){//error1: when no argument is passed
        printf("expected an argument for cd :(\n");
    }
    else{
        if (chdir(pargs) != 0){
            printf("chdir failed:(\n");//error2 chdir failed
        }
    }
    return 1;
}

void displayPrompt(){
    printf("-suii->  ");
}

int main(int argc, char* argv[]){
    
    char absfp[1024];
    getcwd(absfp,1024);
    char tfp[1024];
    strcpy(tfp, absfp);

    while(1){
        displayPrompt();
        int tflag = 0;//set to 1 if threading is required
        int vc = 0;//set to 1 if command entered by user is valid
        
        //taking input
        char str[1024];
        scanf("%[^\n]%*c", str);
        char* rest = str;

        char* coptions = NULL; //string pointer to options
        char* args = NULL;  //string pointer to arguments(temporary)
        char* fargs = NULL; //final string pointer to arguments

        //splitting string once
        char* initstring = strtok_r(str, " ", &rest);
        
        //checking if options have been given
        if (str[strlen(initstring)+1] == '-'){
            coptions = strtok_r(NULL, " ", &rest);
        }

        args = strtok_r(NULL, "\n", &rest);
        char* rest_temp = args;

        //checking if threading is required
        if (args != NULL){
            if ((args[strlen(args)-1] == 't')&&(args[strlen(args)-2] == '&')){
                printf("Threading required!\n");
                tflag = 1;
                if (strcmp(args, "&t") == 0){
                    fargs = NULL;
                }
                else{
                    fargs = strtok_r(args, "&", &rest_temp);
                }   
            }
            else{
                fargs = args;
            }
        }

        //creating array of pointers to pass as argument to external commands
        char* args_ext[4];

        args_ext[0] = argv[0];
        if (coptions == NULL){
            args_ext[1] = "empty";
        }
        else{    
            args_ext[1] = coptions;
        }
        
        args_ext[2] = fargs;
        args_ext[3] = NULL;


        //HANDLING INTERNAL COMMANDS

        //ECHO
        if (strcmp(initstring, "echo") == 0){
            vc = 1;
            callECHO(coptions, fargs);
        }
        //PWD
        if (strcmp(initstring, "pwd") == 0){
            vc = 1;
            callPWD(coptions, fargs);
        }
        //CD
        if (strcmp(initstring, "cd") == 0){
            vc = 1;
            callCD(coptions, fargs);
        }
        

        //HANDLING EXTERNAL COMMANDS

        //without threading
        if ((extCheck(initstring) == 1) && (tflag==0)){
            vc = 1;

            //creating absolute file path for executable
            strcpy(absfp, tfp);
            strcat(absfp,"/");
            strcat(absfp, initstring);

            int f_id = fork();
            if (f_id != 0){ //parent process waiting for the child process to finish execution
                wait(NULL);
            }
            else{//executing file from child process
                execv(absfp, args_ext);
            }
        }

        //with threading
        if ((extCheck(initstring) == 1) && (tflag==1)){
            vc = 1;

            //creating absolute file path for executable
            strcpy(absfp, tfp);
            strcat(absfp,"/");
            strcat(absfp, initstring);
            for (int i=1; i<3; i++){
                strcat(absfp, " ");

                if (args_ext[i] != NULL){
                    strcat(absfp, args_ext[i]);
                }
                else{
                    strcat(absfp, " ");
                }
            }

            pthread_t newthread;

            pthread_create(&newthread, NULL, altSys, absfp);
            pthread_join(newthread, NULL);
            printf("thread's done\n");
        }


        //exit condition to escape while loop
        if (strcmp(initstring, "exit") == 0){
            break;
        }

        if (vc == 0){
            printf("invalid command entered :(\n");
        }

    }

    return 0;
}