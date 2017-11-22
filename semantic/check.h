#ifndef __CHECK_H__
#define __CHECK_H__

#include "symbol_table.h"
#include "../common.h"

//Error Type 15
void CheckSameNameInStruct(FieldList* FL)
{
	if(FL==NULL)return;
	FieldList* former;
	FieldList* later;
	for(former = FL; former->tail != NULL; former = former->tail)
	{
		for(later = former->tail; later != NULL; later = later->tail)
		{
			if(strcmp(former->name, later->name)==0)
			{
				SemanticSwitch = false;
				printf("\033[31mError type 15 at Line %d: Redefined field \"%s\".\033[0m\n", 
					later->lineno, later->name );
			}
		}
	}
}

//Error Type 3 and 16
void CheckSameVarNameInSymbolTable(char* varname, int lineno, SymbolTableHead* table, bool isVar)
{
	SymbolTableEntry* SE;
	for(SE = table->head; SE != NULL; SE = SE->tail)
	{
		if(SE->kind == VAR && strcmp(varname, SE->Variable.VariableName)==0)
		{
			SemanticSwitch = false;
			if(isVar)
			{
				printf("\033[31mError type 3 at Line %d: Redefined variable \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
			else
			{
				printf("\033[31mError type 16 at Line %d: Duplicated name \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
		}
	}
}

void CheckSameFunNameInSymbolTable(char* funname, int lineno, SymbolTableHead* table)
{
	SymbolTableEntry* SE;
	for(SE = table->head; SE != NULL; SE = SE->tail)
	{
		if(SE->kind == FUN && strcmp(funname, SE->Function.FunName)==0)
		{
			SemanticSwitch = false;
			printf("\033[31mError type 4 at Line %d: Redefined function \"%s\".\033[0m\n", 
					lineno,funname);
			return;
		}
	}
}

void CheckSameVarNameInStructTypeTable(char* varname, int lineno, StructTypeTableHead* table, bool isVar)
{
	StructTypeTableEntry* STE;
	for(STE = table->head; STE != NULL; STE = STE->tail)
	{
		if(strcmp(varname, STE->TP->structure.structname)==0)
		{
			SemanticSwitch = false;
			if(isVar)
			{
				printf("\033[31mError type 3 at Line %d: Redefined variable \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
			else
			{
				printf("\033[31mError type 16 at Line %d: Duplicated name \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
		}
	}	
}

void CheckSameVarNameInParamList(char* varname, int lineno, ParamList* PL)
{
	SymbolTableEntry* SE;
	for(SE = PL->head; SE != NULL; SE = SE->tail)
	{
		if(strcmp(varname, SE->Variable.VariableName)==0)
		{
			SemanticSwitch = false;
			printf("\033[31mError type 3 at Line %d: Redefined variable \"%s\".\033[0m\n", 
					lineno,varname);
			return;
		}
	}
}

static char* basictype[2] = {"int", "float"};

static void PrintType(Type* type)
{
	if(type->kind == BASIC)
	{
		printf("basic type : %s\n", basictype[type->basic]);
	}
	else if(type->kind == ARRAY)
	{
		printf("array size : %d, array elem type : \n", type->array.size);
		PrintType(type->array.elem);
	}
	else
	{
		printf("struct member : \n");
		FieldList* FL;
		for(FL = type->structure.member; FL != NULL; FL = FL->tail)
		{
			printf("\t");
			printf("name : %s ", FL->name);
			PrintType(FL->type);
		}
	}
}

void CheckElemInTable(SymbolTableHead* table)
{
	SymbolTableEntry* SE;
	printf("---------------------------------------------------\n");
	for(SE = table->head; SE != NULL; SE = SE->tail)
	{
		if(SE->kind == VAR)
		{
			printf("VAR : %s at line : %d, type : ", SE->Variable.VariableName, SE->lineno);
			PrintType(SE->Variable.VariableType);
			printf("----------------------------------------------------\n");
		}
		else if(SE->kind == FUN)
		{
			printf("FUN : %s at line : %d : ", SE->Function.FunName, SE->lineno);
			printf("Ret Type : ");
			PrintType(SE->Function.RetType);
			printf("\n");
			printf("ParamList : \n");
			SymbolTableEntry* PLE;
			for(PLE = SE->Function.PL->head;PLE!=NULL;PLE = PLE->tail)
			{
				printf("name : %s ", PLE->Variable.VariableName);
				PrintType(PLE->Variable.VariableType);
			}

			printf("----------------------------------------------------\n");
		}
	}
	printf("\n\n");
}

#endif