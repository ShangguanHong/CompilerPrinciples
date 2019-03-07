%{
#include <stdlib.h>
void yyerror(char *);
#include "a.tab.h"
%}
%%
[ \t]+
1|[tT][rR][uU][eE]           {yylval = 1; return TRUE;}
0|[fF][aA][lL][sS][eE]       {yylval = 0; return FALSE;}
[&]{2}|[|]{2}                {return *yytext;}
[~!&|()\n]                   {return *yytext;}
.                            {yyerror("无效字符");}
%%
int yywrap()
{
    return 1;  
}