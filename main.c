#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "config_parsing.h"

int main(int argc, char** argv){
    
    int* used = malloc(sizeof(int) * 1);
    int x;
    int used_size = 0;
    int used_cap = 1;
    bool unique = false;
    if(used == NULL){
        printf("failed to allocate memory");
        exit(1);
    }
    int chara_num;
    char** chara_output = malloc(1 * sizeof(char*));
    if(chara_output == NULL){
        printf("faild to allocate memory");
        exit(1);
    }
    int chara_output_size = 0;
    int chara_output_cap = 1;
    srand(time(NULL));


    if(argc == 2){
        chara_num = atoi(argv[1]);
    }
    else{
        chara_num = 1;
    }
    int chara_size;
    char** chara_list = read_fileLBL("character_list.txt", &chara_size);

    for(int i = 0; i < chara_num; i++){
         if(chara_output_size == chara_output_cap){
            chara_output = realloc(chara_output, (sizeof(char*) * chara_output_cap) * 2);
            if(chara_output == NULL){
                printf("faild to reallocate memory");
                exit(1);
            }
            chara_output_cap *= 2;
        }
        unique = false;
        while(!unique){
            x = rand() % chara_size;
            unique = true;
            for(int j = 0; j < used_size; j++){
                if(x == used[j]){
                    unique = false;
                    break;
                }
            }
        }

    
        if(used_size == used_cap){
            used = realloc(used, used_cap * sizeof(int) * 2);
            if(used == NULL){
                printf("failed to reallocate pointer");
                exit(1);
            }
        
        used_cap *= 2;
        }
        used[used_size] = x;
        used_size += 1;

        
        chara_output[i] = chara_list[x];
        chara_output_size += 1;
    }

    for(int i = 0; i < chara_output_size; i++){
        printf("%s\n", chara_output[i]);
    }

    for(int i = 0; i < chara_size; i++){
        free(chara_list[i]);
    }
    free(chara_list);
    free(chara_output);

    return 0;
}
