#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int getUTC(){

    
    time_t now = time(&now);
    
    if (now == -1){
        printf("error: the time function failed :(\n");
        return 1;
    }

    struct tm* ptm = gmtime(&now);

    if (ptm == NULL){
        printf("error: the gmtime function failed :(\n");
        return 1;
    }

    printf("%s\n", asctime(ptm));
    return 0;
}

int getN(){

    
    time_t now = time(NULL);

    if (now == -1){
        printf("the time function failed :( \n");
        return 1;
    }

    char space[100];

    struct tm* present_time = localtime(&now);

    if (present_time == NULL){
        printf("the localtime function failed :( \n");
        return 1;
    }

    strftime(space, 100, "%A %d %B %Y %r %Z\n", present_time);
    puts(space);
 
    return 0;
}

int getD(char* inptime){

    time_t now = time(NULL);

    if (now == -1){
        printf("the time function failed :( \n");
        return 1;
    }

    char space[100];
    char findate[1024];

    struct tm* present_time = localtime(&now);

    if (present_time == NULL){
        printf("the localtime function failed :( \n");
        return 1;
    }

    strftime(space, 100, "%A %d %B %Y ", present_time);
    strcpy(findate, space);

    strcat(findate, inptime);
    strcat(findate, " IST");

    printf("%s\n", findate);
    printf("\n");
 
    return 0;
}

int main(int argc, char* argv[]){

    //invalid option check trig
    int invop = 0;//set to 1 if no invalid options

    int d_nt =0;//set to 1 if no options have been passed

    //if -u is there, prints UTC
    if (strcmp(argv[1],"-u")==0){
        invop = 1;
        return(getUTC());
    }

    //if -d is there, prints time asked by string
    if (strcmp(argv[1],"-d")==0){
        invop = 1;

        //error2: no arguments passed after option -d
        if (argc!=3){
            printf("missing arguments :(\n");
            return 1;
        }
        else{
            return(getD(argv[2]));
        }
    }

    if (strcmp(argv[1],"empty")==0){
        invop = 1;
        d_nt = 1;
    }

    if (d_nt == 1){
        //prints normal date and time here
        return(getN());
    }

    //error1: invalid options passed error
    if (invop == 0){
        printf("invalid options passed :(\n");
        return 1;
    }
    
    return 0;
}