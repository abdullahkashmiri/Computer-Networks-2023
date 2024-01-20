// l217512 Abdullah Dar CN lab 1 Q1 part d

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<stdbool.h>
 
bool containsVowels(char *str) {
     while (*str) {
        if (*str == 'a' || *str == 'e' || *str == 'i' || *str == 'o' || *str == 'u' || *str == 'A' || *str == 'E' || *str == 'I' || *str == 'O' || *str == 'U') {
            return true;
            }
          str++;
       }
        return false;
    }

    void reverseString(char *str) {
        int length = strlen(str);
        int i = 0;
        for (i = 0; i < length / 2; i++) {
            char temp = str[i];
            str[i] = str[length - i - 1];
            str[length - i - 1] = temp;
        }
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
    char *word;
    while ((read = getline(&line, &size, infile)) != -1) {
        word = strtok(line, " \n");
        while (word) {
            if (containsVowels(word)) {
            reverseString(word);
        }
    fputs(word, outfile);
        fputc(' ', outfile);
        word = strtok(NULL, " \n");
        }
        fputc('\n', outfile);
    }

    printf("Words with vowels inverted and written to: %s\n", outputfilename);
    fclose(infile);
    fclose(outfile);
    if (line) {
        free(line);
    }
    return 0;
}