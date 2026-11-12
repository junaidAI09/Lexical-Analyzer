#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include "keyword.h"
#include "special.h"
#include "operator.h"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: ./lexer filename\n");
        return 1;
    }

    printf("Lexical Analyzer!\n");
    printf("file: %s\n", argv[1]);

    FILE *fp;
    fp = fopen(argv[1], "r");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    printf("File opened successfully\n\n");

    char word[100];
    int i = 0;
    int ch;
    int line_number = 1;

    // Store opening bracket line numbers
    int round_lines[1000], round_top = -1;
    int curly_lines[1000], curly_top = -1;
    int square_lines[1000], square_top = -1;

    while((ch = fgetc(fp)) != EOF)
    {
        // IGNORE WHITESPACE
        if(ch == '\n')
        {
            line_number++;
            continue;
        }

        if(ch == ' ' || ch == '\t' || ch == '\r')
        {
            continue;
        }
         
         // PREPROCESSOR DIRECTIVE / HEADER FILE
        if(ch == '#')
        {
            char directive[100];
            int j = 0;

            directive[j++] = ch;
            ch = fgetc(fp);

            while(ch == ' ' || ch == '\t')
            {
                ch = fgetc(fp);
            }

            while(isalpha(ch))
            {
                directive[j++] = ch;
                ch = fgetc(fp);
            }

            directive[j] = '\0';

            if(strcmp(directive, "#include") == 0)
            {
                printf("Line %-5d %-20s : PREPROCESSOR DIRECTIVE\n",
                       line_number, directive);
            }

            // Skip spaces before header
            while(ch == ' ' || ch == '\t')
            {
                ch = fgetc(fp);
            }

            // HEADER FILE
            if(ch == '<' || ch == '"')
            {
                char header[100];
                int k = 0;
                int closing;

                closing = (ch == '<') ? '>' : '"';

                header[k++] = ch;
                ch = fgetc(fp);

                while(ch != closing && ch != EOF && ch != '\n')
                {
                    header[k++] = ch;
                    ch = fgetc(fp);
                }

                if(ch == closing)
                {
                    header[k++] = ch;

                    // Consume closing delimiter
                    ch = fgetc(fp);
                }

                header[k] = '\0';

                printf("Line %-5d %-20s : HEADER FILE\n",
                       line_number, header);
            }

            // Handle next character
            if(ch == '\n')
            {
                line_number++;
            }
            else if(ch != EOF)
            {
                ungetc(ch, fp);
            }

            continue;
        }
        
        // KEYWORD / IDENTIFIER
        if(isalpha(ch) || ch == '_')
        {
            while(isalpha(ch) || isdigit(ch) || ch == '_')
            {
                word[i++] = ch;
                ch = fgetc(fp);
            }

            word[i] = '\0';
            check_keyword(word, line_number);
            i = 0;

            if(ch != EOF)
            {
                ungetc(ch, fp);
            }

            continue;
        }

        // INTEGER / FLOATING CONSTANT
        if(isdigit(ch))
        {
            char number[100];
            int j = 0;
            int is_float = 0;

            while(isdigit(ch) || ch == '.')
            {
                if(ch == '.')
                {
                    is_float = 1;
                }

                number[j++] = ch;
                ch = fgetc(fp);
            }

            number[j] = '\0';

            if(is_float)
            {
                printf("Line %-5d %-20s : FLOATING CONSTANT\n",
                       line_number, number);
            }
            else
            {
                printf("Line %-5d %-20s : INTEGER CONSTANT\n",
                       line_number, number);
            }

            if(ch != EOF)
            {
                ungetc(ch, fp);
            }

            continue;
        }

        // CHARACTER CONSTANT
        if(ch == '\'')
        {
            char constant[100];
            int j = 0;

            constant[j++] = ch;
            ch = fgetc(fp);

            while(ch != '\'' && ch != EOF)
            {
                constant[j++] = ch;
                ch = fgetc(fp);
            }

            if(ch == '\'')
            {
                constant[j++] = ch;
            }

            constant[j] = '\0';

            printf("Line %-5d %-20s : CHARACTER CONSTANT\n",
                   line_number, constant);

            continue;
        }

        // STRING CONSTANT
        if(ch == '"')
        {
            char string[200];
            int j = 0;

            string[j++] = ch;
            ch = fgetc(fp);

            while(ch != '"' && ch != EOF)
            {
                string[j++] = ch;
                ch = fgetc(fp);
            }

            if(ch == '"')
            {
                string[j++] = ch;
            }

            string[j] = '\0';

            printf("Line %-5d %-20s : STRING CONSTANT\n",
                   line_number, string);

            continue;
        }

        // SPECIAL CHARACTER AND BRACKET CHECKING
        if(is_special(ch))
        {
            // OPENING PARENTHESIS
            if(ch == '(')
            {
                round_lines[++round_top] = line_number;
            }

            // CLOSING PARENTHESIS
            else if(ch == ')')
            {
                if(round_top == -1)
                {
                    printf("Line %-5d %-20s : MISSING OPENING PARENTHESIS\n",
                           line_number, "ERROR");

                    check_special(ch, line_number);
                    continue;
                }
                else
                {
                    round_top--;
                }
            }

            // OPENING CURLY BRACKET
            else if(ch == '{')
            {
                // Check missing closing parenthesis
                while(round_top >= 0)
                {
                    printf("Line %-5d %-20s : MISSING CLOSING PARENTHESIS\n",
                           round_lines[round_top], "ERROR");

                    round_top--;
                }

                curly_lines[++curly_top] = line_number;
            }

            // CLOSING CURLY BRACKET
            else if(ch == '}')
            {
                if(curly_top == -1)
                {
                    printf("Line %-5d %-20s : MISSING OPENING CURLY BRACKET\n",
                           line_number, "ERROR");

                    check_special(ch, line_number);
                    continue;
                }
                else
                {
                    curly_top--;
                }
            }

            // OPENING SQUARE BRACKET
            else if(ch == '[')
            {
                square_lines[++square_top] = line_number;
            }

            // CLOSING SQUARE BRACKET
            else if(ch == ']')
            {
                if(square_top == -1)
                {
                    printf("Line %-5d %-20s : MISSING OPENING SQUARE BRACKET\n",
                           line_number, "ERROR");

                    check_special(ch, line_number);
                    continue;
                }
                else
                {
                    square_top--;
                }
            }

            // CHECK MISSING CLOSING SQUARE BRACKET BEFORE SEMICOLON
            if(ch == ';')
            {
                while(square_top >= 0)
                {
                    printf("Line %-5d %-20s : MISSING CLOSING SQUARE BRACKET\n",
                           square_lines[square_top], "ERROR");

                    square_top--;
                }
            }

            check_special(ch, line_number);
            continue;
        }
        // OPERATOR
        if(is_operator(ch))
        {
            check_operator(ch, fp, &line_number);
            continue;
        }
    }
    // CHECK UNMATCHED PARENTHESES AT EOF
    while(round_top >= 0)
    {
        printf("Line %-5d %-20s : MISSING CLOSING PARENTHESIS\n",
               round_lines[round_top], "ERROR");

        round_top--;
    }

    // CHECK UNMATCHED CURLY BRACKETS AT EOF
    while(curly_top >= 0)
    {
        printf("Line %-5d %-20s : MISSING CLOSING CURLY BRACKET\n",
               curly_lines[curly_top], "ERROR");

        curly_top--;
    }
    // CHECK UNMATCHED SQUARE BRACKETS AT EOF
    while(square_top >= 0)
    {
        printf("Line %-5d %-20s : MISSING CLOSING SQUARE BRACKET\n",
               square_lines[square_top], "ERROR");

        square_top--;
    }
    fclose(fp);
    return 0;
}