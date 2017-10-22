%{
#include <stdio.h>
#include "lex.yy.h"
#include "ParsingNode.h"

int prev_error_lineno = 0;

void yyerror(char* msg );

void ErrorTypeBHandler(int lineno, char* msg);

%}

%union {
    struct ParsingNode *node;
}


%token <node> INT FLOAT ID SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV OR AND
%token <node> DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE
%token <node> END

%type <node> Program ExtDefList ExtDef Specifier ExtDecList VarDec StructSpecifier 
%type <node> OptTag Tag FunDec VarList ParamDec CompSt StmtList Stmt Exp Def DefList Dec DecList Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS 
%left STAR DIV
%right NOT
%nonassoc LOWER_THAN_RP
%left LP RP LB RB DOT
%nonassoc LOWER_THAN_ELSE LOWER_THAN_SEMI LOWER_THAN_RC
%nonassoc ELSE SEMI RC COMMA

%%

/*High-level Definitions*/
Program : ExtDefList                            {$$ = GenerateVariableNode(AProgram, 1, $1);ParsingRoot = $$;}
    ;

ExtDefList :                                    {$$ = NULL;}
    | ExtDef ExtDefList                         {$$ = GenerateVariableNode(AExtDefList, 2, $1, $2);}
    ;

ExtDef : Specifier ExtDecList SEMI              {$$ = GenerateVariableNode(AExtDef, 3, $1, $2, $3);}
    | Specifier SEMI                            {$$ = GenerateVariableNode(AExtDef, 2, $1, $2);}
    | Specifier FunDec CompSt                   {$$ = GenerateVariableNode(AExtDef, 3, $1, $2, $3);}
    | Specifier error %prec LOWER_THAN_SEMI     {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"}\", maybe Missing \";\".");}                    
    | Specifier ExtDecList error SEMI           {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\".");}
    ;

ExtDecList : VarDec                             {$$ = GenerateVariableNode(AExtDecList, 1, $1);}
    | VarDec COMMA ExtDecList                   {$$ = GenerateVariableNode(AExtDecList, 3, $1, $2, $3);}
    ;

/*Specifiers*/
Specifier : TYPE                                {$$ = GenerateVariableNode(ASpecifier, 1, $1);}    
    | StructSpecifier                           {$$ = GenerateVariableNode(ASpecifier, 1, $1);}
    ;

StructSpecifier : STRUCT OptTag LC DefList RC   {$$ = GenerateVariableNode(AStructSpecifier, 5, $1, $2, $3, $4, $5);}
    | STRUCT Tag                                {$$ = GenerateVariableNode(AStructSpecifier, 2, $1, $2);}
    ;

OptTag :                                        {$$ = NULL;}
    | ID                                        {$$ = GenerateVariableNode(AOptTag, 1, $1);}
    ;

Tag : ID                                        {$$ = GenerateVariableNode(ATag, 1, $1);}
    ;

/*Declarators*/
VarDec : ID                                     {$$ = GenerateVariableNode(AVarDec, 1, $1);}
    | VarDec LB INT RB                          {$$ = GenerateVariableNode(AVarDec, 4, $1, $2, $3, $4);}
    | VarDec LB INT error RB                    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \"]\", maybe Missing \"]\".");}
    | VarDec LB error RB                        {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"[\".");}
    ;

FunDec : ID LP VarList RP                       {$$ = GenerateVariableNode(AFunDec, 4, $1, $2, $3, $4);}
    | ID LP RP                                  {$$ = GenerateVariableNode(AFunDec, 3, $1, $2, $3);}
    | ID LP error RP                            {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"(\".");}
    ;

VarList : ParamDec COMMA VarList                {$$ = GenerateVariableNode(AVarList, 3, $1, $2, $3);}
    | ParamDec                                  {$$ = GenerateVariableNode(AVarList, 1, $1);}
    ;

ParamDec : Specifier VarDec                     {$$ = GenerateVariableNode(AParamDec, 2, $1, $2);}
    ;

/*Statements*/
CompSt : LC DefList StmtList RC                 {$$ = GenerateVariableNode(ACompSt, 4, $1, $2, $3, $4);}
    |   LC error %prec LOWER_THAN_RC            {ErrorTypeBHandler(prev_error_lineno, "Missing \"}\"");}
    |   LC error RC                             {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \"}\".");}
    ;

StmtList :                                      {$$ = NULL;}
    | Stmt StmtList                             {$$ = GenerateVariableNode(AStmtList, 2, $1, $2);}
    ;

Stmt : Exp SEMI                                 {$$ = GenerateVariableNode(AStmt, 2, $1, $2);}
    | CompSt                                    {$$ = GenerateVariableNode(AStmt, 1, $1);}
    | RETURN Exp SEMI                           {$$ = GenerateVariableNode(AStmt, 3, $1, $2, $3);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE   {$$ = GenerateVariableNode(AStmt, 5, $1, $2, $3, $4, $5);}
    | IF LP Exp RP Stmt ELSE Stmt               {$$ = GenerateVariableNode(AStmt, 7, $1, $2, $3, $4, $5, $6, $7);}
    | WHILE LP Exp RP Stmt                      {$$ = GenerateVariableNode(AStmt, 5, $1, $2, $3, $4, $5);}
    | Exp error %prec LOWER_THAN_RP             {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
    | Exp error SEMI                            {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\", maybe Missing \";\".");}
    | Exp error COMMA                           {ErrorTypeBHandler(prev_error_lineno, "Syntax error near \",\".");}
    | RETURN Exp error SEMI                     {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \";\".");}
    | Exp error RP SEMI                         {ErrorTypeBHandler(prev_error_lineno, "Syntax error near \")\"");}
    ;

/*Local Definitions*/
DefList :                                       {$$ = NULL;}
    | Def DefList                               {$$ = GenerateVariableNode(ADefList, 2, $1, $2);}
    ;

Def : Specifier DecList SEMI                    {$$ = GenerateVariableNode(ADef, 3, $1, $2, $3);}
    | Specifier DecList error SEMI              {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
    | Specifier DecList error %prec LOWER_THAN_SEMI {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
    | Specifier VarDec ASSIGNOP Exp MINUS error SEMI {ErrorTypeBHandler(prev_error_lineno, "Missing \";\".");}
    ;

DecList : Dec                                   {$$ = GenerateVariableNode(ADecList, 1, $1);}
    | Dec COMMA DecList                         {$$ = GenerateVariableNode(ADecList, 3, $1, $2, $3);}
    ;

Dec : VarDec                                    {$$ = GenerateVariableNode(ADec, 1, $1);}
    | VarDec ASSIGNOP Exp                       {$$ = GenerateVariableNode(ADec, 3, $1, $2, $3);}
    ;

/*Expressions*/
Exp : Exp ASSIGNOP Exp                          {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp AND Exp                               {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp OR Exp                                {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp RELOP Exp                             {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp PLUS Exp                              {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp MINUS Exp                             {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp STAR Exp                              {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp DIV Exp                               {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | LP Exp RP                                 {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | MINUS Exp                                 {$$ = GenerateVariableNode(AExp, 2, $1, $2);}
    | NOT Exp                                   {$$ = GenerateVariableNode(AExp, 2, $1, $2);}
    | ID LP Args RP                             {$$ = GenerateVariableNode(AExp, 4, $1, $2, $3, $4);}
    | ID LP RP                                  {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | Exp LB Exp RB                             {$$ = GenerateVariableNode(AExp, 4, $1, $2, $3, $4);}
    | Exp DOT ID                                {$$ = GenerateVariableNode(AExp, 3, $1, $2, $3);}
    | ID                                        {$$ = GenerateVariableNode(AExp, 1, $1);}
    | INT                                       {$$ = GenerateVariableNode(AExp, 1, $1);} 
    | FLOAT                                     {$$ = GenerateVariableNode(AExp, 1, $1);}
    | Exp LB Exp error RB                       {ErrorTypeBHandler(prev_error_lineno, "Missing \"]\".");}
    | Exp LB error RB                           {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"[\".");}
    | ID LP error RP                            {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"(\".");}
    | ID LP Args error RP                       {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \")\".");}
    | ID LP Args error RB RP                    {ErrorTypeBHandler(prev_error_lineno, "Syntax error before \")\".");} 
    | ID LP Args error %prec LOWER_THAN_RP      {ErrorTypeBHandler(prev_error_lineno, "Syntax error after \"(\".");}
    ;

Args : Exp COMMA Args                           {$$ = GenerateVariableNode(AArgs, 3, $1, $2, $3);}
    | Exp                                       {$$ = GenerateVariableNode(AArgs, 1, $1);}
    ;

%%


void yyerror(char* msg __attribute__((unused))) {  
    ParsingSwitch = false;
    prev_error_lineno = yylineno;  
    //printf("syntax error\n");
}

void ErrorTypeBHandler(int lineno, char* msg){
    ParsingSwitch = false;
    printf("\033[31mError type B at Line %d: %s\033[0m\n", lineno, msg);
}