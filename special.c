#include <stdio.h>
int is_special(char ch)
{
     if (ch == ';' || ch == '(' || ch == ')' ||
        ch == '{' || ch == '}' ||
        ch == '[' || ch == ']' ||
        ch == ',' || ch == ':')
    {
        return 1;
    }

    return 0;
}

void check_special(char ch , int line_number){
if(ch==';')
{
printf("Line %-5d %-20c : SPECIAL CHARACTER (STATEMENT TERMINATOR)\n", line_number, ch);
}
 if(ch=='(')
{    
 printf("Line %-5d %-20c : SPECIAL CHARACTER (OPENING PARENTHESIS)\n", line_number, ch);
}
if (ch == ')')
{
    printf("Line %-5d %-20c : SPECIAL CHARACTER (CLOSING PARENTHESIS)\n", line_number, ch);
}
if (ch == '{')
{
    printf("Line %-5d %-20c : SPECIAL CHARACTER (OPENING CURLY BRACKET)\n", line_number, ch);
}
if (ch == '}')
{
    printf("Line %-5d %-20c : SPECIAL CHARACTER (CLOSING CURLY BRACKET)\n", line_number, ch);
}
if (ch == '[')
{
    printf("Line %-5d %-20c : SPECIAL CHARACTER (OPENING SQUARE BRACKET)\n", line_number, ch);
}
if (ch == ']')
{
    printf("Line %-5d %-20c : SPECIAL CHARACTER (CLOSING SQUARE BRACKET)\n", line_number, ch);
}
if (ch == ',')
{
    printf("Line %-5d %-20c : SPECIAL CHARACTER (COMMA)\n", line_number, ch);
}
if (ch == ':')
{
    printf("Line %-5d %-20c : SPECIAL CHARACTER (COLON)\n", line_number, ch);
}
}