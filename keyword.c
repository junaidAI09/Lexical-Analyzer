#include <stdio.h>
#include <string.h>

char *keywords[] = {
    "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto",
    "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};
       void check_keyword(char *word, int line_number) {
            int found=0;    
            for(int j=0;j<32;j++)//checking if the word is a keyword or not
            {
                if(strcmp(word, keywords[j])==0)
                {
                    printf("Line %-5d %-20s : KEYWORD\n",line_number, word);
                    found=1;
                    break;
                }
            }
            if(found==0){//if the word is not a keyword then it is an identifier
                printf("Line %-5d %-20s : IDENTIFIER\n",line_number, word);
            }
        }