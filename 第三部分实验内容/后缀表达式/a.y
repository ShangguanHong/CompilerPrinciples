%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
void yyerror(char *);
int yylex();
%}
%token NUMBER
%left '+' '-'
%left '*' '/'
%%
lines:  lines expr '\n'     {printf("\n");}
        |lines '\n'
        |
        |error '\n'        
        ;

expr:   expr '+' expr       {printf("+");}
        |expr '-' expr      {printf("-");} 
        |expr '*' expr      {printf("*");}
        |expr '/' expr      {printf("/");}
        |'(' expr ')'
        |NUMBER             {printf("%d", $1);}
        ;
%%
void yyerror(char *s) {
    printf("%s\n", s);
}
int yylex() {
    int c;
    while((c = getchar()) == ' ');
    if(isdigit(c)) {
        ungetc(c, stdin);
        scanf("%d", &yylval);
        return NUMBER;
    }
    return c;
}
int main() {
    yyparse();
    return 0;
}