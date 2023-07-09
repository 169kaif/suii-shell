#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int rmNormal(char* ftrem){

    int fo;

    fo = open(ftrem, O_RDONLY);
    
    if (fo != -1){
        close(fo);
        unlink(ftrem);
    }
    //error2: no such file exists
    else{
        printf("no such file exists:( \n");
        return 1;
    }

    return 0;
}

int rmI(char* ftrem){

    char uinpt[3];
    printf("Would you like to delete the file: %s  ?", ftrem);
    scanf("%[^\n]s",uinpt);
    printf("\n");

    if (strcmp(uinpt, "yes")==0){
        rmNormal(ftrem);
    }
    else if(strcmp(uinpt, "no")==0){
        return 0;
    }
    else{
        printf("expected yes or no :(\n");
        return 1;
    }


}

int rmF(char* ftrem){

    int fo;

    fo = open(ftrem, O_RDONLY);
    
    if (fo != -1){
        close(fo);
        unlink(ftrem);
    }
    else{
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]){

    //IF THREADING IS USED AND FILE NAME CONTAINS ), ERROR OCCURS

    //error1: no file specified for rm to remove
    if (argc != 3){
        printf("no arguments passed to rm :(\n");
        return 1;
    }

    if(strcmp(argv[1],"-i")==0){
        //prompt before removal of file
        return(rmI(argv[2]));
    }
    else if (strcmp(argv[1],"-f")==0){
        //force removal of a file, never prompt
        return(rmF(argv[2]));
    }
    else if(strcmp(argv[1], "empty")==0){
        //normal removal of a file
        return(rmNormal(argv[2]));
    }
    else{
        printf("invalid options passed:( \n");
        return 1;
    }

    return 0;
}