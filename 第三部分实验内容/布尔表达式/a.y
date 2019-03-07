%{
#include <stdlib.h>
#include <stdio.h>
int yylex(void);
void yyerror(char *);
%}
%token TRUE
%token FALSE
%left '|' "||"
%left '&' "&&"
%right '~' '!'
%%
lines:  lines expr '\n'     {if($2 == 1){printf("true\n");} else {printf("false\n");}}
        |lines '\n'
        |
        |error '\n'
        ;
expr:   expr '|' expr       {if($1 == 0 && $3 == 0) {$$ = 0;} else {$$ = 1;}}
        |expr "||" expr     {if($1 == 0 && $3 == 0) {$$ = 0;} else {$$ = 1;}}
        |expr '&' expr      {if($1 == 1 && $3 == 1) {$$ = 1;} else {$$ = 0;}}
        |expr "&&" expr     {if($1 == 1 && $3 == 1) {$$ = 1;} else {$$ = 0;}}
        |'~' expr           {if($2 == 1) {$$ = 0;} else {$$ = 1;}}
        |'!'expr            {if($2 == 1) {$$ = 0;} else {$$ = 1;}}
        |'(' expr ')'       {$$ = $2;}
        |TRUE               {$$ = 1;}
        |FALSE              {$$ = 0;}
        ;

%%
void yyerror(char *s) {
    printf("%s\n", s);
}
int main(void) {
    yyparse();
    return 0;
}