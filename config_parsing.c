#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"config_parsing.h"



// config params

// returns dynamic array of strings each string being a line from the file
// initial value of array size is irrelevent. function will change array size to be size of array
char** read_fileLBL(char* file, int* array_size){
    
    FILE* raw_file = fopen(file, "r");
    if(!raw_file){
        printf("failed to open file");
    }

    char** output_array = (char**)malloc(1 * sizeof(char*));

    // defines max number of characters per line
    int buffer_size = 200;
    char buffer[buffer_size];
    int array_capacity = 1;
    *array_size = 0;
    int x = 0;

    while(fgets(buffer, buffer_size, raw_file)){

        //check for empty lines
        if(strlen(buffer) == 1){
            continue;
        } 
        
        // remove the \n character
        int pos = strlen(buffer);
        buffer[pos - 1] = '\0';
    
        // free up memory for new pointer
        if(array_capacity <= *array_size){
            output_array = (char**)realloc(output_array, (array_capacity * sizeof(char*)) * 2);
            array_capacity = array_capacity * 2;

            if(output_array == NULL){
                printf("failed to reallocate memory\n");
                exit(EXIT_FAILURE);
            }
        }
         //free up memory for the new string
        output_array[*array_size] = (char*)malloc((strlen(buffer) + 11) * sizeof(char));
        if(output_array[*array_size] == NULL){
            printf("failed to allocate memory");
            exit(EXIT_FAILURE);
        }
       //  copy new string into array
        strcpy(output_array[*array_size], buffer);
        (*array_size)++;
    }
    output_array = (char**)realloc(output_array, *array_size * sizeof(char*));
    fclose(raw_file);
    return output_array;
}

