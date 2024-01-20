// l217512 Abdullah Dar CN lab 1 Q1 part c

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<stdbool.h>

bool checkNonAlphabets(char * str)
{
    int i = 0;
    while(str[i]!='\0')
    {
        if((str[i]>='a' && str[i]<='z' )||(str[i]>='A' && str[i]<='Z' ))
            return false;
        i++;
    }
    return true;
}
 
 
int main() {
    char *inputfilename = "input.txt";
    char *outputfilename = "output.txt";
    FILE *infile = fopen(inputfilename, "r");
    FILE *outfile = fopen(outputfilename, "w");
    size_t size = 0;

    if (outfile == NULL || infile == NULL) {
        printf("Files not found or couldn't be opened.\n");
        return 1;
    }

    char *line = NULL;
    ssize_t read;
    char delimiter = ' ';
    char * word;
    while ((read = getline(&line, &size, infile)) != -1) {
        word = strtok(line, " \n");
        while(word = strtok(NULL,  " \n")){
           // printf("%s\n", word);
            if (checkNonAlphabets(word) == true) {
                {
                   // printf("True %s\n", word);
                    fputs(word, outfile);
                    fputc(delimiter, outfile);
                }
            }
        }
    }
    printf("Non Alphabets moved to file : %s\n", outputfilename);
    fclose(infile);
    fclose(outfile);
    if (line) {
        free(line);  
    }
    return 0;
}
