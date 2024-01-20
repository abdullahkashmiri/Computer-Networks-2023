// l217512 Abdullah Dar CN lab 1 Q1 part b

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
{
    char *inputfilename = "input.txt";
    char *outputfilename = "output.txt";
    FILE *infile = fopen(inputfilename,"r");
    FILE *outfile = fopen(outputfilename,"w");
   
    if(outfile == NULL || infile == NULL)
   {
   printf("Files not found \n");
   return 1;
   }
    printf("Numbers moved to file : %s\n", outputfilename);
    char ch;
    while((ch = fgetc(infile))!=EOF)
    {
        if(ch >= '0' && ch <='9')
        fputc(ch, outfile);
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}
