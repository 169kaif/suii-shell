#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int callmkN(char* userinp){

    int check;
    check = mkdir(userinp, 0777);

    //mkdir fails for some reason
    if (check == -1){
        printf("directory couldn't be created :(\n");
        return 1;
    }
    else{
        //no message displayed for normal mkdir unless error
        return 0;
    }

}

int callmkV(char* userinp){

    int check;
    check = mkdir(userinp, 0777);

    //mkdir fails for some reason
    if (check == -1){
        printf("directory couldn't be created :(\n");
        return 1;
    }
    else{
        printf("mkdir: %s has been created \n", userinp);
        return 0;
    }

}

int callmkM(char* mode, char* ftcname){

    printf("mkdir -m prompt: if doesn't work retry with order r-> w-> x\n");

    int check;

    if (strcmp(mode, "rwx")==0){
        check = mkdir(ftcname, 0777);
    }
    else if(strcmp(mode, "rw")==0){
        check = mkdir(ftcname, 0666);
    }
    else if(strcmp(mode, "rx")==0){
        check = mkdir(ftcname, 0555);
    }
    else if(strcmp(mode, "wx")==0){
        check = mkdir(ftcname, 0333);
    }
    else if(strcmp(mode, "r")==0){
        check = mkdir(ftcname, 0444);
    }
    else if(strcmp(mode, "w")==0){
        check = mkdir(ftcname, 0222);
    }
    else if(strcmp(mode, "x")==0){
        check = mkdir(ftcname, 0111);
    }
    else{//errorcheck: if invalid permissions are passed
        printf("invalid permissions passed :( \n");
    }

    //mkdir fails for some reason
    if (check == -1){
        printf("directory couldn't be created :(\n");
        return 1;
    }
    else{
        //no message displayed for normal mkdir unless error
        return 0;
    }

}

int main(int argc, char* argv[]){

    int invc = 0;//error2: invalid check set to 1 if invalid syntax
    
    if (argc!=3){
        invc = 1;
        printf("invalid syntax for mkdir :(\n");
    }

    if (invc==0){

        if (strcmp(argv[1], "-v")==0){
            return(callmkV(argv[2]));
        }
        else if((argv[1][0] == '-')&&(argv[1][1] == 'm')){

            //ONLY SET HANDLED
            char *perms = NULL;
            char* duparg1 = argv[1];
            perms = strtok_r(argv[1],"=",&duparg1);

            //error3: file permissions not mentioned
            if (duparg1 == NULL){
                printf("file permissions not mentioned :( \n");
                return 1;
            }
            else{
                return(callmkM(duparg1, argv[2]));
            }
        }
        else if(strcmp(argv[1],"empty")==0){
            return(callmkN(argv[2]));
        }
        else{//error1: invalid options passed check
            printf("invalid options have been passed :(\n");
        }
    }

    return 0;
}