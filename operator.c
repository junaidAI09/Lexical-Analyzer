#include<stdio.h>
int is_operator(char ch)
{
     if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '%' ||
        ch == '=' || ch == '<' ||
        ch == '>' || ch == '!' ||
        ch == '&' || ch == '|' ||
        ch == '^' || ch == '~')
    {
        return 1;
    }

    return 0;
}

void check_operator(char ch,FILE *fp,int *line_number){
       if(ch=='+')
       {
        int next=fgetc(fp);
        if(next=='+'){
          printf("Line %-5d %-20s : OPERATOR (INCREMENT)\n",  *line_number, "++");
        }
          else if(next=='='){
            printf("Line %-5d %-20s : OPERATOR (ADDITION ASSIGNMENT)\n", *line_number, "+=");
        }else{
           printf("Line %-5d %-20c : OPERATOR (ADDITION)\n", *line_number, ch);
           if(next != EOF)
           {
            ungetc(next,fp);
           }
       }
      }

       if(ch=='-')
       {
        int next=fgetc(fp);
        if(next=='-')
        {
            printf("Line %-5d %-20s : OPERATOR (DECREMENT)\n", *line_number, "--");
        }
            else if(next=='='){
            printf("Line %-5d %-20s : OPERATOR (SUBRACTION ASSIGNMENT)\n", *line_number, "-=");
          }
        else{
         printf("Line %-5d %-20c : OPERATOR (SUBTRACTION)\n", *line_number, ch);
         if(next != EOF){
          ungetc(next,fp);
         }
       }
      }

       if(ch=='*')
       {
        int next=fgetc(fp);
        if(next=='='){
          printf("Line %-5d %-20s : OPERATOR (MULTIPLICATION ASSIGNMENT)\n", *line_number, "*=");
        }else{
        printf("Line %-5d %-20c : OPERATOR (MULTIPLIER)\n", *line_number, ch);
        if(next!=EOF){
          ungetc(next,fp);
        }
      }
     }

         if(ch=='/')
       {
        int next=fgetc(fp);
        if(next=='/'){
          while((next=fgetc(fp)) != '\n' && next != EOF)//Removing Single Line Comments
          {
          }
          if(next=='\n')
          {
            (*line_number)++;
          }
        }
        else if(next=='*')
        {
         int prev=0;
         int closed=0;
         while((next=fgetc(fp)) != EOF){/* Removing Multi line Comments*/
          if(next=='\n'){
            (*line_number)++;
          }
          if(prev == '*'&&next=='/'){ 
            closed=1;
            break;
          }
          prev=next;
        }
          if(closed==0){
           printf("Line %-5d %-20s : MULTI-LINE COMMENT WITHOUT TERMINATION\n", *line_number, "ERROR");
          }
        }
          else if(next=='='){
          printf("Line %-5d %-20s : OPERATOR (DIVISION ASSIGNMENT)\n", *line_number, "/=");
          }else{
        printf("Line %-5d %-20c : OPERATOR (DIVISION)\n", *line_number, ch);
        if(next!=EOF){
          ungetc(next,fp);
        }
      }
     }


         if(ch=='%')
       {
        int next=fgetc(fp);
        if(next=='='){
          printf("Line %-5d %-20s : OPERATOR (MODULUS ASSIGNMENT)\n", *line_number, "%=");
        }else{
        printf("Line %-5d %-20c : OPERATOR (MODULUS)\n", *line_number, ch);
        if(next!=EOF){
          ungetc(next,fp);
        }
      }
     }


  if(ch=='<')
  {
        int next=fgetc(fp);
        if(next == '<'){
          int next2=fgetc(fp);
          if(next2=='='){
          printf("Line %-5d %-20s : OPERATOR (LEFT SHIFT ASSIGNMENT)\n", *line_number, "<<=");
          }
        else{
        printf("Line %-5d %-20s : OPERATOR (LEFT SHIFT)\n", *line_number, "<<");
        if(next2!=EOF){
          ungetc(next2,fp);
        }
      }
    }
    else if(next =='='){
      printf("Line %-5d %-20s : OPERATOR (LESS THAN OR EQUAL)\n", *line_number, "<=");
    }else{
        printf("Line %-5d %-20c : OPERATOR (LESS THAN)\n", *line_number, ch);
    if(next!=EOF){
      ungetc(next,fp);
    }
  }
}


  if(ch=='>')
  {
         int next=fgetc(fp);
        if(next == '>'){
          int next2=fgetc(fp);
          if(next2=='='){
          printf("Line %-5d %-20s : OPERATOR (RIGHT SHIFT ASSIGNMENT)\n", *line_number, ">>=");
          }
        else{
        printf("Line %-5d %-20s : OPERATOR (RIGHT SHIFT)\n", *line_number, ">>");
        if(next2!=EOF){
          ungetc(next2,fp);
        }
      }
    }
      else if(next =='='){
      printf("Line %-5d %-20s : OPERATOR (GREATER THAN OR EQUAL)\n", *line_number, ">>=");
    } else{
        printf("Line %-5d %-20c : OPERATOR (GREATER THAN)\n", *line_number, ch);
      if(next!=EOF){
       ungetc(next,fp);
      }
   }
 }

         if(ch=='&')
       {
         int next=fgetc(fp);
        if(next == '&'){
          printf("Line %-5d %-20s : OPERATOR (LOGICAL AND)\n", *line_number, "&&");
        }else if(next=='='){
           printf("Line %-5d %-20s : OPERATOR (BITWISE AND ASSIGNMENT)\n", *line_number, "&=");
        }else{
        printf("Line %-5d %-20c : OPERATOR (BITWISE AND)\n", *line_number, ch);
        if(next!=EOF){
          ungetc(next,fp);
        }
      }
    }
         if(ch=='|')
       {
        int next=fgetc(fp);
        if(next == '|'){
          printf("Line %-5d %-20s : OPERATOR (LOGICAL OR)\n", *line_number, "||");
        }else if(next =='='){
           printf("Line %-5d %-20s : OPERATOR (BITWISE OR ASSIGNMENT)\n", *line_number, "|=");
        }else{
        printf("Line %-5d %-20c : OPERATOR (BITWISE OR)\n", *line_number, ch);
        if(next!=EOF){
          ungetc(next,fp);
        }
      }
    }

         if(ch=='^')
       {
         int next=fgetc(fp);
        if(next == '='){
          printf("Line %-5d %-20s : OPERATOR (BITWISE XOR ASSIGNMENT)\n", *line_number, "^=");
        }else{
        printf("Line %-5d %-20c : OPERATOR (BITWISE XOR)\n", *line_number, ch);
        if(next!=EOF){
          ungetc(next,fp);
        }
      }
    }
        
        
         if(ch=='~')
       {
        printf("Line %-5d %-20c : OPERATOR (BITWISE COMPLEMENT)\n", *line_number, ch);
       }


         if(ch=='!')
       {
         int next=fgetc(fp);
        if(next == '='){
          printf("Line %-5d %-20s : OPERATOR (NOT EQUAL)\n", *line_number, "!=");
        }else{
        printf("Line %-5d %-20c : OPERATOR (LOGICAL NOT)\n", *line_number, ch);
        if(next!=EOF){
          ungetc(next,fp);
        }
      }
    }
        
        
         if(ch=='=')
       {
        int next=fgetc(fp);
        if(next=='='){
           printf("Line %-5d %-20s : OPERATOR (EQUAL)\n", *line_number, "==");
        }else{
        printf("Line %-5d %-20c : OPERATOR (ASSIGNMENT)\n", *line_number, ch);
        if(next != EOF){
          ungetc(next,fp);
        }
       }
      }
    


    }


