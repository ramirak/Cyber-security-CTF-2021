#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define NUM_FILES 300
void splitMeToFiles(char* str, int len);
void createArrFileNames(int *arr);
int getRandFileNum(int *arr);
char *getTextFromFile(FILE *file, int *len);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int *len = malloc(sizeof(int));
    FILE *file = fopen("Secret", "r");
    char *str = getTextFromFile(file, len);
    
    splitMeToFiles(str,*len);
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

void splitMeToFiles(char* str, int len)
{
    int numChars = len / NUM_FILES;
    int *arr = malloc(sizeof(int) * NUM_FILES);
    createArrFileNames(arr);

    FILE *fp;
    for(int i = 0; i< len; i++)
    {
        char fileName[5];
        if(i % numChars == 0)
        {
            int fileNum = getRandFileNum(arr);
            if(fileNum == 0)
                return;
            printf("%d," , fileNum);
            sprintf(fileName, "%d", fileNum);
            fp  = fopen(fileName, "w");
        }
        fputc(str[i], fp);
    }
}

void createArrFileNames(int *arr)
{
    for(int i = 0; i < NUM_FILES; i++){
        arr[i] = i+1;
    }
}

int getRandFileNum(int *arr)
{
    int r = rand() % NUM_FILES;  
    if(arr[r] != -1){
        arr[r] = -1;
        return r+1;
    }
    else{
        for(int i = 0; i < NUM_FILES; i++)
        {
            if(arr[i] != -1)
            {
                arr[i] = -1;
                return i+1;
            }
        }
    }
    return 0;
}