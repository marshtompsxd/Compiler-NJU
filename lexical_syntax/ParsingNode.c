#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include "ParsingNode.h"
#include "text.h"

static char* symbolsTable[48] = 
		{"INT", "FLOAT", "ID", "SEMI", "COMMA", "ASSIGNOP", "RELOP", 
		"PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT", "NOT", "TYPE",
		"LP", "RP", "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE", "WHILE",
		"Program", "ExtDefList", "ExtDef", "Specifier", "ExtDecList",
		"VarDec", "StructSpecifier", "OptTag", "Tag", "FunDec", "VarList", 
		"ParamDec", "CompSt", "StmtList", "Stmt", "Exp", "Def", "DefList", 
		"Dec","DecList", "Args"};

static char* typeTable[2] = {"int", "float"};

char* relopTable[6] = {"==", "<", ">", "!=", "<=", ">="};

ParsingNode* ParsingRoot = NULL;

bool ParsingSwitch = true;

bool CheckLvalue(ParsingNode* node)
{
	assert(node->SymbolIndex == AExp);
	if(node->childrenNum == 1)
	{
		if(node->firstchild->SymbolIndex == AID)return true;
	}
	else if(node->childrenNum == 3)
	{
		if(node->firstchild->SymbolIndex == AExp
			&& secondchild(node)->SymbolIndex == ADOT
			&& thirdchild(node)->SymbolIndex == AID)return true;
	}
	else if(node->childrenNum == 4)
	{
		if(node->firstchild->SymbolIndex == AExp
			&& secondchild(node)->SymbolIndex == ALB
			&& thirdchild(node)->SymbolIndex == AExp
			&& fourthchild(node)->SymbolIndex == ARB)return true;
	}
	return false;
}

bool IsArithmeticNode(ParsingNode* node)
{
	if(node->SymbolIndex == APLUS 
		|| node->SymbolIndex == AMINUS
		|| node->SymbolIndex == ASTAR
		|| node->SymbolIndex == ADIV)
		return true;
	else return false;
}

bool IsLogicNode(ParsingNode* node)
{
	if(node->SymbolIndex == AOR || node->SymbolIndex == AAND)return true;
	else return false;
}

bool IsRELOPNode(ParsingNode* node)
{
	return node->SymbolIndex == ARELOP;
}

ParsingNode* GenerateSimpleTerminalNode(int TerminalType, int lineno)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	node->kind = Terminal;
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
	node->kind = Terminal;
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

ParsingNode* GenerateRELOPNode(int lineno, char* text)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	node->kind = Terminal;
	node->SymbolIndex = ARELOP;
	node->lineno = lineno;
	node->firstchild = NULL;
	node->nextsibiling = NULL;
	node->childrenNum = 0;

	if(strcmp(text, "==") == 0)node->relop_kind = EQ;
	else if(strcmp(text, "<") == 0)node->relop_kind = LT;
	else if(strcmp(text, ">") == 0)node->relop_kind = GT;
	else if(strcmp(text, "!=") == 0)node->relop_kind = NEQ;
	else if(strcmp(text, "<=") == 0)node->relop_kind = LEQ;
	else node->relop_kind = GEQ;

	#ifdef TERMINAL_DEBUG
    printf("Terminal RELOP : %s at %d\n", text, node->lineno);
    #endif

    return node;

}

ParsingNode* GenerateTypeNode(int TerminalType, int lineno, char* text)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	node->kind = Terminal;
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
		printf("Terminal %s : %s at %d\n", symbolsTable[node->SymbolIndex], typeTable[node->type], node->lineno);
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
		node->float_value = (float)strtod(text, NULL);

		#ifdef TERMINAL_DEBUG
		printf("Terminal %s : %f at %d\n", symbolsTable[node->SymbolIndex], node->float_value, node->lineno);
		#endif
	}
	return node;
}

ParsingNode* GenerateDummyNode(int VariableType)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	node->kind = Dummy;
	node->SymbolIndex = VariableType;
	node->nextsibiling = NULL;
	node->firstchild = NULL;
	node->childrenNum = 0;

	return node;
}

ParsingNode* GenerateVariableNode(int VariableType, int childrenNum, ...)
{
	ParsingNode *node = (ParsingNode*)malloc(sizeof(ParsingNode));
	ParsingNode *previous;
	ParsingNode *child;
	node->kind = Variable;
	node->SymbolIndex = VariableType;
	node->nextsibiling = NULL;
	node->childrenNum = childrenNum;

	va_list arg_ptr;
	va_start(arg_ptr, childrenNum);
	int i;
	int dummy_num = 0;
	bool met_first = false;
	for(i=0;i<childrenNum;i++)
	{
		child = va_arg(arg_ptr, ParsingNode*);
		if(i == 0)
		{
			node->firstchild = child;
		}
		else 
		{
			previous->nextsibiling = child;
		}

		if(child->kind == Dummy)
		{
			dummy_num++;
		}
		else
		{
			if(!met_first)
			{
				node->lineno = child->lineno;
				met_first = true;
			}
		}

		child->parent = node;
		previous = child;
	}
	va_end(arg_ptr);

	if(node->childrenNum == dummy_num)
	{
		node->kind = Dummy;
	}

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
}

static void PrintSpace(ParsingNode* node)
{
	if(node->kind == Dummy)return;
	int i;
	for(i=0;i<node->depth*2;i++) printf(" ");
}

static void PrintParsingNode(ParsingNode* node)
{
	PrintSpace(node);
	if(node->kind == Variable)
	{
		printf("%s (%d)\n",symbolsTable[node->SymbolIndex], node->lineno );
	}
	else if(node->kind == Terminal)
	{
		if(node->SymbolIndex == AID)
			printf("%s: %s\n",symbolsTable[node->SymbolIndex], node->IDname );
		else if(node->SymbolIndex == ARELOP)
			printf("%s: %s\n",symbolsTable[node->SymbolIndex], relopTable[node->relop_kind] );
		else if(node->SymbolIndex == ATYPE)
			printf("%s: %s\n",symbolsTable[node->SymbolIndex], typeTable[node->type] );
		else if(node->SymbolIndex == AINT)
			printf("%s: %d\n",symbolsTable[node->SymbolIndex], node->int_value );
		else if(node->SymbolIndex == AFLOAT)
			printf("%s: %f\n",symbolsTable[node->SymbolIndex], node->float_value );
		else printf("%s\n",symbolsTable[node->SymbolIndex] );
	}
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
}

void PostorderFreeParsingTree(ParsingNode* node)
{
    if(!ParsingSwitch)return;
    if(node->kind == Terminal)
    {
        if(node->SymbolIndex == AID)free(node->IDname);
        free(node);
    }
    else if(node->kind == Dummy)
	{
		free(node);
	}
    else
    {
        ParsingNode* child = node->firstchild;
        int i;
        for(i=0;i<node->childrenNum;i++)
        {
            PostorderFreeParsingTree(child);
            child = child->nextsibiling;
        }
        free(node);
    }

}

void SyntaxOutput(ParsingNode* node)
{
	SetDepthOfParsingTree(node, 0);
	//PreorderPrintParsingTree(node);
}