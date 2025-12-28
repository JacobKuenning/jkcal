#include "readfile.h"

char* readFile(char* filename){
    FILE* file = fopen(filename, "r");
    int size = fileSize(file);

    char* contents = malloc(sizeof(char) * size + 1);
    fread(contents, sizeof(char), size +1, file);
    return contents;
}

int fileSize(FILE* file){
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file,0,0); // move marker back to beginning of file
    return size;
}