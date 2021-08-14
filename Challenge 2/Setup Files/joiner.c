#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define NUM_FILES 300
char *getTextFromFile(FILE *file, int *len);
void joinFiles(FILE *mFile, int *arr);

int main(int argc, char *argv[])
{
    int arr[300] = { INSERT SEQUENCE HERE }
    int *len = malloc(sizeof(int));
    FILE *mFile = fopen("Secret", "w");   
    joinFiles(mFile, arr);
}

void joinFiles(FILE *mFile, int *arr)
{
    for(int i = 0; i<NUM_FILES; i++){
        char fileName[5];
        sprintf(fileName, "%d", arr[i]);
        FILE *file = fopen(fileName, "r");
        int *len = malloc(sizeof(int));
        char *str = getTextFromFile(file,len);
        for(int j = 0; j < *len -1; j++)
        {
            if(!isspace(str[j]))
                fputc(str[j], mFile);
        }
    }   
}

char *getTextFromFile(FILE *file, int *len)
{
    *len = 1;
    char *str, *pStr;
    char c;
    str = (char *)malloc(sizeof(char));
    while (fscanf(file, "%c", &c) != EOF)
    {
        pStr = str;
        pStr += (*len) - 1;
        (*len)++;
        *pStr = c;
        str = realloc(str, sizeof(char) * (*len));
    }
    return str;
}
