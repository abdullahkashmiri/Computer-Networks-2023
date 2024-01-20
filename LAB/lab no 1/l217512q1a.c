// l217512 Abdullah Dar CN lab 1 Q1 part a
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
    char *filename = "input.txt";
    FILE *infile = fopen(filename,"r");
    if(infile == NULL)
    {
    printf("File not found");
    return 1;
    }
    char ch;
    while((ch = fgetc(infile))!=EOF)
    {
        printf("%c",ch);
    }
    fclose(infile);
    return 0;
}