#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>

char* getFileContent(FILE *f, long *len);
void byteManipulation(char *buffer, long len, char *filepath, char* fileName);
void helper(int * arr, long i);
int *getDecData(long len, char* fileName);
int is_regular_file(const char *path);
#define MAX_LEN 200

const char *userDataPath = "importantFiles/";
const char *decDataPath = "importantFiles/decryptionData/";

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main()
{   
    DIR *d, *d_Dec;
    d = opendir(userDataPath);
    d_Dec = opendir(decDataPath);
    struct dirent *dir;
    
    while((dir = readdir(d)) != NULL) 
    {    
        char *filepath = malloc(sizeof(char)* MAX_LEN);
        filepath[0] = '\0';
        strcat(filepath, userDataPath);
        strcat(filepath, dir->d_name);
        if(!is_regular_file(filepath))
            continue;
        FILE *f = fopen(filepath,"rb");
        if(!strcmp(dir->d_name, "..") || !strcmp(dir->d_name, "."))
            continue;
        if(!f)
            return -1;
        long len;
        char* buffer = getFileContent(f, &len);
        byteManipulation(buffer, len, filepath, dir->d_name);
    }
}

void byteManipulation(char *buffer, long len, char *filepath, char* fileName)
{ 
    remove(filepath);
    strcat(filepath, ".dec");
    FILE *f = fopen(filepath,"wb");
    if(f == NULL)
        return;
    int *arr = getDecData(len, fileName);
    int *pArr = arr;
    for(long i = 0; i < len; i++)
    {
        helper(pArr,i);
        buffer[i] ^= arr[i];
        fwrite(buffer + i, sizeof(char), 1, f);
    }
}

int *getDecData(long len, char* fileName)
{
    char *filepath = malloc(sizeof(char)* MAX_LEN);
    filepath[0] = '\0';
    strcat(filepath, decDataPath);
    strcat(filepath, fileName);
    strcat(filepath, ".dat");
    FILE *f = fopen(filepath,"rb");
    if(f == NULL)
        exit(0);
    int *arr = malloc(sizeof(int) * len);
    for(long i = 0; i < len; i++)
    {
        fread(arr + i, sizeof(int), 1, f);
    }
    free(filepath);
    return arr;
}

void helper(int * arr, long i)
{
    int r = arr[i];
    if(r % 2 == 0)
        arr[i] /= 2;
    else
        arr[i] --;
    
}

char* getFileContent(FILE *f, long *len)
{
    char *buffer;
    fseek(f, 0, SEEK_END);         
    *len = ftell(f);            
    rewind(f);  
    buffer = (char *)malloc(*len * sizeof(char)); 
    fread(buffer, *len, 1, f); 
    fclose(f);
    return buffer;
}