#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *getTextFromFile(FILE *file);
int *fibo(int n);
char* getSequence(char *txt, int* fiboArr, int n);
void printArr(char* arr, int len);

int main(int argc, char *argv[])
{
    const int n = 20;
    FILE *file;
    int keyLength;
    char *path = "txtfile";
    file = fopen(path, "r");
    if (file == NULL)
    {
        return -1;
    }
    char *txt = getTextFromFile(file);
    int *arr = fibo(n+1);
    char* sqn = getSequence(txt,arr,n+1);   
    printArr(sqn,n+1);
    free(txt);
    free(arr);
    free(sqn);
       
}

char *getTextFromFile(FILE *file)
{
    int len = 1;
    char *str, *pStr;
    char c;
    str = (char *)malloc(sizeof(char));
    while (fscanf(file, "%c", &c) != EOF)
    {
        pStr = str;
        pStr += len - 1;
        len++;
        *pStr = c;
        str = realloc(str, sizeof(char) * len);
    }
    return str;
}

int *fibo(int n)
{
    int *fiboArr = malloc(sizeof(int)*n);
    fiboArr[0] = 0;
    fiboArr[1] = 1;
    for(int i = 2; i<n ; i++)
    {
        fiboArr[i] = fiboArr[i-1] + fiboArr[i-2];
    }
    return fiboArr;
}

char* getSequence(char *txt, int* fiboArr, int n)
{
    char *sqn = malloc(sizeof(int) *n);
    for(int i = 0; i< n; i++)
    {
        sqn[i] = txt[fiboArr[i]];
    }
    return sqn;
}

void printArr(char* arr, int len)
{
    for(int i = 0; i<len; i++)
    {
        printf("%c" , arr[i]);
    }
    printf("\n");
}