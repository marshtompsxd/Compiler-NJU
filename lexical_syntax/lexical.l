%{
#include <stdio.h>
#include "syntax.tab.h"
#include "ParsingNode.h"


int yycolumn = 1;
#define YY_USER_ACTION \
 yycolumn += yyleng;

void MysteriousCharacterHandler(char* msg, int lineno);
void IllegalOctNumberHandler(char* msg, int lineno);
void IllegalHexNumberHandler(char* msg, int lineno);
void IllegalFloatNumberHandler(char* msg, int lineno);
void CommentUntilEOF(int lineno);
int EmitCommentBlock();
%}

%option yylineno
letter          [a-zA-Z]
letter_         [a-zA-Z_]
digit           [0-9]
oct_digit       [0-7]
hex_digit       [0-9a-fA-F]
TYPE            "int"|"float"
FLOAT           ([0-9]*\.[0-9]+|[0-9]+\.)([eE][+-]?{digit}+)?
INT             0|[1-9]{digit}*|0{oct_digit}+|0[xX]{hex_digit}+
IL_OCT_INT      0{digit}+
IL_HEX_INT      0[xX][0-9a-zA-Z]+
ID              [a-zA-Z_]+[0-9a-zA-Z_]*
RELOP           ">"|"<"|">="|"<="|"=="|"!="
COMMENTLINE     \/\/[^\n]*
COMMENTBLOCK    \/\*
WS              [ \t]+

%%
{FLOAT}         {yylval.node = GenerateTypeNode(AFLOAT, yylineno, yytext);return FLOAT;}
{INT}           {yylval.node = GenerateTypeNode(AINT, yylineno, yytext);return INT;}
{IL_OCT_INT}    {IllegalOctNumberHandler(yytext, yylineno);yylval.node = GenerateTypeNode(AINT, yylineno, "0");return INT;}
{IL_HEX_INT}    {IllegalHexNumberHandler(yytext, yylineno);yylval.node = GenerateTypeNode(AINT, yylineno, "0");return INT;}
{TYPE}          {yylval.node = GenerateTypeNode(ATYPE, yylineno, yytext);return TYPE;}
"struct"        {yylval.node = GenerateSimpleTerminalNode(ASTRUCT, yylineno);return STRUCT;}
"return"        {yylval.node = GenerateSimpleTerminalNode(ARETURN, yylineno);return RETURN;}
"if"            {yylval.node = GenerateSimpleTerminalNode(AIF, yylineno);return IF;}
"else"          {yylval.node = GenerateSimpleTerminalNode(AELSE, yylineno);return ELSE;}
"while"         {yylval.node = GenerateSimpleTerminalNode(AWHILE, yylineno);return WHILE;}
{ID}            {yylval.node = GenerateIDNode(yylineno, yytext);return ID;}
";"             {yylval.node = GenerateSimpleTerminalNode(ASEMI, yylineno);return SEMI;}
","             {yylval.node = GenerateSimpleTerminalNode(ACOMMA, yylineno);return COMMA;}
"="             {yylval.node = GenerateSimpleTerminalNode(AASSIGNOP, yylineno);return ASSIGNOP;}
{RELOP}         {yylval.node = GenerateRELOPNode(yylineno, yytext);return RELOP;}
"+"             {yylval.node = GenerateSimpleTerminalNode(APLUS, yylineno);return PLUS;}
"-"             {yylval.node = GenerateSimpleTerminalNode(AMINUS, yylineno);return MINUS;}
"*"             {yylval.node = GenerateSimpleTerminalNode(ASTAR, yylineno);return STAR;}
"/"             {yylval.node = GenerateSimpleTerminalNode(ADIV, yylineno);return DIV;}
"&&"            {yylval.node = GenerateSimpleTerminalNode(AAND, yylineno);return AND;}
"||"            {yylval.node = GenerateSimpleTerminalNode(AOR, yylineno);return OR;}
"."             {yylval.node = GenerateSimpleTerminalNode(ADOT, yylineno);return DOT;}
"!"             {yylval.node = GenerateSimpleTerminalNode(ANOT, yylineno);return NOT;}
"("             {yylval.node = GenerateSimpleTerminalNode(ALP, yylineno);return LP;}
")"             {yylval.node = GenerateSimpleTerminalNode(ARP, yylineno);return RP;}
"["             {yylval.node = GenerateSimpleTerminalNode(ALB, yylineno);return LB;}
"]"             {yylval.node = GenerateSimpleTerminalNode(ARB, yylineno);return RB;}
"{"             {yylval.node = GenerateSimpleTerminalNode(ALC, yylineno);return LC;}
"}"             {yylval.node = GenerateSimpleTerminalNode(ARC, yylineno);return RC;}
\n              {yycolumn=1;}
{COMMENTLINE}   {;}
{COMMENTBLOCK}  {if(EmitCommentBlock())return 0;}
{WS}            {;}
.               {MysteriousCharacterHandler(yytext, yylineno);}

%%

void MysteriousCharacterHandler(char* msg, int lineno)
{
    ParsingSwitch = false;
    printf("\033[31mError type A at Line %d: Mysterious character \"%s\".\033[0m\n", lineno, msg);    
}

void IllegalOctNumberHandler(char* msg, int lineno)
{
    ParsingSwitch = false;
    printf("\033[31mError type A at Line %d: Illegal octal number \"%s\".\033[0m\n",lineno, msg );
}

void IllegalHexNumberHandler(char* msg, int lineno)
{
    ParsingSwitch = false;
    printf("\033[31mError type A at Line %d: Illegal hexadecimal number \"%s\".\033[0m\n",lineno, msg );
}

void IllegalFloatNumberHandler(char* msg, int lineno)
{
    ParsingSwitch = false;
    printf("\033[31mError type A at Line %d: Illegal float number \"%s\".\033[0m\n",lineno, msg );
}

void CommentUntilEOF(int lineno)
{
    ParsingSwitch = false;
    printf("\033[31mError type A at Line %d: block comment met EOF.\033[0m\n",lineno);   
}

int EmitCommentBlock()
{
    char c1, c2;
    c1 = 0;
    c2 = (char)input();
    while(!(c1 == '*' && c2 == '/'))
    {
        if(c2 == EOF)
        {
           CommentUntilEOF(yylineno);
           return 1;
        }
        c1 = c2;
        c2 = (char)input();
    }
    return 0;
}
