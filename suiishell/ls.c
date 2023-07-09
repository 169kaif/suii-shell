#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char* argv[]){

    int d_check = 0;//set to 1 if d(directory only) is passed as an option
    int c_check=0;//set to 1 if c(fits 2 files/folders in first line, followed by 3 in the remaining ---> replicating column) is passed as an option  

    int i=1;
    int vo=0;//set to 1 if options are valid

    if (strcmp(argv[1], "-c")==0){
        vo = 1;
        c_check = 1;
    }
    if (strcmp(argv[1], "-d")==0){
        d_check = 1;
        vo = 1;
    }
    if (strcmp(argv[1], "-cd")==0){
        c_check = 1;
        d_check = 1;
        vo = 1;
    }
    if (strcmp(argv[1], "-dc")==0){
        c_check = 1;
        d_check = 1;
        vo = 1;
    }
    if (strcmp(argv[1], "empty")==0){
        vo = 1;
    }

    //handling error1: syntax error
    if (vo == 0){
        printf("syntax error: options passed are invalid :(");
        return 1;
    }

    DIR* p_dir = opendir(".");

    //handling error2: empty directory
    if (p_dir == NULL){
        printf("No files in directory!");
        return 1;
    }

    struct dirent* bff;
    bff = readdir(p_dir);

    while (bff != NULL){
        if ((d_check ==0)&&(c_check==0)){
            printf("%s\n", bff->d_name);
            bff = readdir(p_dir);
        }
        if ((d_check ==1)&&(c_check==0)){
            if (bff->d_type == DT_DIR){
                printf("%s\n", bff->d_name);
            }
            bff = readdir(p_dir);
        }
        if ((d_check ==0)&&(c_check==1)){
            i++;
            printf("%s\t\t", bff->d_name);
            if ((i%3)==0){
                printf("\n");
            }
            bff = readdir(p_dir);
        }
        if ((d_check ==1)&&(c_check==1)){
            if (bff->d_type == DT_DIR){
                i++;
                printf("%s\t\t", bff->d_name);
            }
            if ((i%3)==0){
                printf("\n");
            }
            bff = readdir(p_dir);
        }
    }
    
    closedir(p_dir);
    printf("\n");
    return 0;
}