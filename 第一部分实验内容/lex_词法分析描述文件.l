/* scanner for a toy Pascal-like language */
%{
/* need this for the call to atof() below */
#include <math.h>
#include <stdio.h>
%}
DIGIT [0-9]
LETTER [A-Za-z]
ID ([_]|{LETTER})({LETTER}|{DIGIT}|[_])*

%%

[ \t\n]+          /* eat up whitespace */
{DIGIT}+"."{DIGIT}+ { printf("(2, %s)\n", yytext); }
{DIGIT}+ {printf("(2, %s)\n", yytext);}
var {printf("(21, \"var\")\n");}
if {printf("(22, \"if\")\n");}
then {printf("(23, \"then\")\n");}
else {printf("(24, \"else\")\n");}
while {printf("(25, \"while\")\n");}
for {printf("(26, \"for\")\n");}
begin {printf("(27, \"begin\")\n");}
writeln {printf("(28, \"writeln\")\n");}
procedure {printf("(29, \"procedure\")\n");}
end {printf("(30, \"end\")\n");}
{ID} {printf("(1, \"%s\")\n", yytext);}
"+" {printf("(3, \"+\")\n");}
"-" {printf("(4, \"-\")\n");}
"*" {printf("(5, \"*\")\n");}
"/" {printf("(6, \"/\")\n");}
"=" {printf("(7, \"=\")\n");}
">" {printf("(8, \">\")\n");}
"<" {printf("(9, \"<\")\n");}
"<>" {printf("(10, \"<>\")\n");}
"<=" {printf("(11, \"<=\")\n");}
">=" {printf("(12, \">=\")\n");}
";" {printf("(17, \";\")\n");}
":=" {printf("(20, \":=\")\n");}
. {printf("(100, \"error\")\n");}

%%

main( argc, argv )
int argc;
char **argv;
{
//printf("please input file name:");
char fileName[100] = "in.txt";
//gets(fileName);
freopen(fileName, "r", stdin);
yylex(); 
}

yywrap()
{
return 1;
} 
