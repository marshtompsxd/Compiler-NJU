#ifndef __CHECK_H__
#define __CHECK_H__

#include "symbol_table.h"
#include "../common.h"
#include <stdlib.h>

//Error Type 15
// need repair
void CheckDuplicatedFieldNameInOneStruct(Type* TP)
{
	assert(TP->kind == STRUCTURE);
	FieldList* FL = TP->structure.member;
	if(FL==NULL)return;
	FieldList* former;
	FieldList* later;

	for(former = FL; former->tail != NULL; former = former->tail)
	{
		/*
		if(TP->structure.structname != NULL)
		{
			if(strcmp(former->name, TP->structure.structname) == 0)
			{
				SemanticSwitch = false;
				printf("\033[31mError type 15 at Line %d: Redefined field \"%s\".\033[0m\n", 
					later->lineno, later->name );
			}
		}
		*/

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
void CheckSameVarNameInSymbolTable(char* varname, int lineno, SymbolTableHead* table, int Name)
{
	SymbolTableEntry* SE;
	for(SE = table->head; SE != NULL; SE = SE->tail)
	{
		if(SE->kind == VAR && strcmp(varname, SE->Variable.VariableName)==0)
		{
			SemanticSwitch = false;
			if(Name == VarName)
			{
				printf("\033[31mError type 3 at Line %d: Redefined variable \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
			else if(Name == StructName)
			{
				printf("\033[31mError type 16 at Line %d: Duplicated name \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
			else 
			{
				printf("\033[31mError type 15 at Line %d: Redefined field \"%s\".\033[0m\n", 
					lineno, varname );
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

void CheckSameFieldNameInStruct(char* fieldname, int lineno, Type* TP, int Name)
{
	assert(TP->kind == STRUCTURE);

	FieldList* FL;
	for(FL = TP->structure.member; FL!=NULL; FL = FL->tail)
	{
		if(strcmp(fieldname, FL->name) == 0)
		{
			SemanticSwitch = false;
			if(Name == VarName)
			{
				printf("\033[31mError type 3 at Line %d: Redefined variable \"%s\".\033[0m\n", 
					lineno,fieldname);
				return;
			}
			else if(Name == StructName)
			{
				printf("\033[31mError type 16 at Line %d: Duplicated name \"%s\".\033[0m\n", 
					lineno,fieldname);
				return;
			}
			else 
			{
				printf("\033[31mError type 15 at Line %d: Redefined field \"%s\".\033[0m\n", 
					lineno, fieldname );
				return;
			}
		}
	}
}

void CheckSameVarNameInStructTypeTable(char* varname, int lineno, StructTypeTableHead* table, int Name)
{
	StructTypeTableEntry* STE;
	for(STE = table->head; STE != NULL; STE = STE->tail)
	{
		if(strcmp(varname, STE->TP->structure.structname)==0)
		{
			SemanticSwitch = false;
			if(Name == VarName)
			{
				printf("\033[31mError type 3 at Line %d: Redefined variable \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
			else if(Name == StructName)
			{
				printf("\033[31mError type 16 at Line %d: Duplicated name \"%s\".\033[0m\n", 
					lineno,varname);
				return;
			}
			else 
			{
				printf("\033[31mError type 15 at Line %d: Redefined field \"%s\".\033[0m\n", 
					lineno, varname );
				return;
			}
		}

		CheckSameFieldNameInStruct(varname, lineno, STE->TP, Name);
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

bool CheckTypeEquivalence(Type* T1, Type* T2)
{
	if(T1 == NULL || T2 == NULL)return false;
	if(T1->kind != T2->kind)return false;
	if(T1->kind == BASIC)
	{
		if(T1->basic !=  T2->basic)return false;
	}
	else if(T1->kind == ARRAY)
	{
		if(!CheckTypeEquivalence(T1->array.elem, T2->array.elem))return false;
	}
	else if(T1->kind == STRUCTURE)
	{
		FieldList* FL1 = T1->structure.member;
		FieldList* FL2 = T2->structure.member;
		while(FL1 != NULL && FL2 != NULL)
		{
			if(!CheckTypeEquivalence(FL1->type, FL2->type))return false;
			FL1 = FL1->tail;
			FL2 = FL2->tail;
		}
		if(FL1 != NULL || FL2 != NULL)return false;
	}
	return true;
}

bool IsTypeInt(Type* T)
{
	return T->kind == BASIC && T->basic == int_type;
}

bool IsTypeFloat(Type* T)
{
	return T->kind == BASIC && T->basic == float_type;
}

bool IsTypeStruct(Type* T)
{
	return T->kind == STRUCTURE;
}

bool IsArray(Type* T)
{
	return T->kind == ARRAY;
}

char* GenerateTypeString(Type* TP)
{
	if(TP->kind == BASIC)
	{
		if(TP->basic == int_type)return "int";
		else return "float";
	}
	else if(TP->kind == ARRAY)
	{
		char* tmp = (char*)malloc(100);
		strcpy(tmp, "[]");
		strcat(tmp, GenerateTypeString(TP->array.elem));
		return tmp;
	}
	else 
	{
		char* tmp = (char*)malloc(100);
		strcpy(tmp, "struct ");
		strcat(tmp, TP->structure.structname);
		return tmp;
	}
}

char* GenerateParamString(ParamList* PL)
{
	char* str = (char*)malloc(100);
	strcpy(str, "(");
	SymbolTableEntry* SE;
	for(SE = PL->head; SE != NULL; SE = SE->tail)
	{
		strcat(str, GenerateTypeString(SE->Variable.VariableType));
		if(SE->tail != NULL) strcat(str, ", ");
	}
	strcat(str, ")");
	return str;
}

bool CheckParamEquivalence(ParamList* PL1, ParamList* PL2)
{
	SymbolTableEntry* SE1 = PL1->head;
	SymbolTableEntry* SE2 = PL2->head;
	while(SE1 != NULL && SE2 != NULL)
	{
		if(!CheckTypeEquivalence(SE1->Variable.VariableType, SE2->Variable.VariableType))
			return false;
		SE1 = SE1->tail;
		SE2 = SE2->tail;
	}
	if(SE1 != NULL || SE2 != NULL)return false;

	return true;
}


#endif