#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "ParsingNode.h"
#include "text.h"

char* symbolsTable[48] = 
		{"INT", "FLOAT", "ID", "SEMI", "COMMA", "ASSIGNOP", "RELOP", 
		"PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT", "NOT", "TYPE",
		"LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE", "WHILE",
		"Program", "ExtDefList", "ExtDef", "Specifier", "ExtDecList",
		"VarDec", "StructSpecifier", "OptTag", "Tag", "FunDec", "VarList", 
		"ParamDec", "CompSt", "StmtList", "Stmt", "Exp", "Def", "DefList", 
		"Dec","DecList", "Args"};

char* typeTables[2] = {"int", "float"};

ParsingNode* ParsingRoot = NULL;

bool ParsingSwitch = true;

ParsingNode* GenerateSimpleTerminalNode(int TerminalType, int lineno)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	node->SymbolIndex = TerminalType;
	node->lineno = lineno;
	node->firstchild = NULL;
	node->nextsibiling = NULL;
	node->childrenNum = 0;

	#ifdef TERMINAL_DEBUG
	printf("Terminal %s at %d\n", symbolsTable[node->SymbolIndex], node->lineno);
	#endif

	return node;
}

ParsingNode* GenerateIDNode(int lineno, char* text)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	node->SymbolIndex = AID;
	node->lineno = lineno;
	node->firstchild = NULL;
	node->nextsibiling = NULL;
	node->childrenNum = 0;

	node->IDname = (char*)malloc(strlen(text));
    strcpy(node->IDname, text);
    
    #ifdef TERMINAL_DEBUG
    printf("Terminal %s : %s at %d\n", symbolsTable[node->SymbolIndex], node->IDname, node->lineno);
    #endif
    
    return node;
}

ParsingNode* GenerateTypeNode(int TerminalType, int lineno, char* text)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	node->SymbolIndex = TerminalType;
	node->lineno = lineno;
	node->firstchild = NULL;
	node->nextsibiling = NULL;
	node->childrenNum = 0;

	if(TerminalType == ATYPE)
	{
		if(strcmp(text, "int")==0)node->type = int_type;
		else node->type = float_type;
		
		#ifdef TERMINAL_DEBUG
		printf("Terminal %s : %s at %d\n", symbolsTable[node->SymbolIndex], typeTables[node->type], node->lineno);
		#endif
	}
	else if(TerminalType == AINT)
	{
		node->int_value = StrToInt(text);

		#ifdef TERMINAL_DEBUG
		printf("Terminal %s : %d at %d\n", symbolsTable[node->SymbolIndex], node->int_value, node->lineno);
		#endif
	}
	else
	{
		node->float_value = atof(text);

		#ifdef TERMINAL_DEBUG
		printf("Terminal %s : %f at %d\n", symbolsTable[node->SymbolIndex], node->float_value, node->lineno);
		#endif
	}
	return node;
}

ParsingNode* GenerateVariableNode(int VariableType, int childrenNum, ...)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	ParsingNode *previous;
	ParsingNode *child;
	node->SymbolIndex = VariableType;
	node->nextsibiling = NULL;
	node->childrenNum = childrenNum;



	va_list arg_ptr;
	va_start(arg_ptr, childrenNum);
	int i;
	for(i=0;i<childrenNum;i++)
	{
		child = va_arg(arg_ptr, ParsingNode*);
		if(child == NULL)
		{
			node->childrenNum--;
			continue;
		}
		child->parent = node;
		if(i == 0)
		{
			node->firstchild = child;
			node->lineno = child->lineno;
		}
		else 
		{
			previous->nextsibiling = child;
		}
		previous = child;
	}
	va_end(arg_ptr);

	if(node->childrenNum == 0)return NULL;

	#ifdef VARIABLE_DEBUG
	printf("Variable %s at %d\n",symbolsTable[node->SymbolIndex], node->lineno);
	#endif

	return node;
}

void SetDepthOfParsingTree(ParsingNode* node, int depth)
{
	if(!ParsingSwitch) return;
	node->depth = depth;
	ParsingNode* child = node->firstchild;
	int i;
	for(i=0;i<node->childrenNum;i++)
	{
		SetDepthOfParsingTree(child, depth+1);
		child = child->nextsibiling;
	}
	return;
}

void PrintSpace(ParsingNode* node)
{
	int i;
	for(i=0;i<node->depth*2;i++) printf(" ");
}

void PrintParsingNode(ParsingNode* node)
{
	PrintSpace(node);
	if(node->childrenNum != 0)
	{
		printf("%s (%d)\n",symbolsTable[node->SymbolIndex], node->lineno );
	}
	else
	{
		if(node->SymbolIndex == AID)
			printf("%s: %s\n",symbolsTable[node->SymbolIndex], node->IDname );
		else if(node->SymbolIndex == ATYPE)
			printf("%s: %s\n",symbolsTable[node->SymbolIndex], typeTables[node->type] );
		else if(node->SymbolIndex == AINT)
			printf("%s: %d\n",symbolsTable[node->SymbolIndex], node->int_value );
		else if(node->SymbolIndex == AFLOAT)
			printf("%s: %f\n",symbolsTable[node->SymbolIndex], node->float_value );
		else printf("%s\n",symbolsTable[node->SymbolIndex] );
	}
	return;
}

void PreorderPrintParsingTree(ParsingNode* node)
{
	if(!ParsingSwitch)return;
	PrintParsingNode(node);
	ParsingNode* child = node->firstchild;
	int i;
	for(i=0;i<node->childrenNum;i++)
	{
		PreorderPrintParsingTree(child);
		child = child->nextsibiling;
	}
	return;
}