#include "semantic.h"
#include "list.h"
#include "check.h"
#include <stdlib.h>

#define SYM_STACK_SIZE 100

static FieldList* VarDecAnalysisInStruct(ParsingNode* node, Type* InheritType);
static FieldList* DecAnalysisInStruct(ParsingNode* node, Type* InheritType);
static FieldList* DecListAnalysisInStruct(ParsingNode* node, Type* InheritType);
static FieldList* DefAnalysisInStruct(ParsingNode* node);
static FieldList* DefListAnalysisInStruct(ParsingNode* node);
static Type* StructSpecifierAnalysis(ParsingNode* node);
static Type* TYPEAnalysis(ParsingNode* node);
static Type* SpecifierAnalysis(ParsingNode* node);
static void VarDecAnalysisGlobal(ParsingNode* node, Type* InheritType);
static void ExtDecListAnalysis(ParsingNode* node, Type* InheritType);
static void ExtDefAnalysis(ParsingNode* node);
static void ExtDefListAnalysis(ParsingNode* node);

static int sym_top;
static int struct_top;

static SymbolTableHead* RootSymbolTable;
static SymbolTableHead* CurrentSymbolTable;
//static SymbolTableHead* SymbolTableStack[SYM_STACK_SIZE];

static StructTypeTableHead* RootStructTypeTable;
static StructTypeTableHead* CurrentStructTypeTable;

bool SemanticSwitch;

static void InitSymbolTable()
{
	SemanticSwitch = true;

	sym_top = 0;
	CurrentSymbolTable = RootSymbolTable = (SymbolTableHead*)malloc(sizeof(SymbolTableHead));
	RootSymbolTable->head = NULL;

	struct_top = 0;
	CurrentStructTypeTable = RootStructTypeTable = (StructTypeTableHead*)malloc(sizeof(StructTypeTableHead));
	RootStructTypeTable->head = NULL;

}


static FieldList* VarDecAnalysisInStruct(ParsingNode* node, Type* InheritType)
{
	assert(node->SymbolIndex == AVarDec);

	if(node->childrenNum == 4)
	{
		ParsingNode* TypeNode = thirdchild(node);

		FieldList* FL;
		Type* subType = (Type*)malloc(sizeof(Type));

		subType->kind = ARRAY;
		subType->array.elem = InheritType;
		subType->array.size = TypeNode->int_value;
		FL = VarDecAnalysisInStruct(node->firstchild, subType);

		return FL;
	}
	else
	{
		ParsingNode* IDNode = node->firstchild;

		FieldList* FL = (FieldList*)malloc(sizeof(FieldList));
		FL->name = (char*)malloc(strlen(IDNode->IDname));
		strcpy(FL->name, IDNode->IDname);
		FL->type = InheritType;
		FL->lineno = IDNode->lineno;
		FL->tail = NULL;

		return FL;
	}
}

static FieldList* DecAnalysisInStruct(ParsingNode* node, Type* InheritType)
{
	assert(node->SymbolIndex == ADec);

	if(node->childrenNum == 3)
	{
		assert(0);
		FieldList* FL;
		return FL;
	}
	else
	{
		return VarDecAnalysisInStruct(node->firstchild, InheritType);
	}
}

static FieldList* DecListAnalysisInStruct(ParsingNode* node, Type* InheritType)
{
	assert(node->SymbolIndex == ADecList);

	if(node->childrenNum == 3)
	{
		FieldList* FL;
		FL = DecAnalysisInStruct(node->firstchild, InheritType);
		FL->tail = DecListAnalysisInStruct(thirdchild(node), InheritType);
		return FL;
	}
	else
	{
		return DecAnalysisInStruct(node->firstchild, InheritType);
	}
}

static FieldList* DefAnalysisInStruct(ParsingNode* node)
{
	assert(node->SymbolIndex == ADef);

	Type* InheritType = SpecifierAnalysis(node->firstchild); 
	return DecListAnalysisInStruct(secondchild(node), InheritType);
}

static FieldList* DefListAnalysisInStruct(ParsingNode* node)
{
	assert(node->SymbolIndex == ADefList);

	if(node->kind!=Dummy)
	{
		FieldList* FL;
		FieldList* FLT;
		FL = DefAnalysisInStruct(node->firstchild);
		FLT = FLTail(FL);
		FLT->tail = DefListAnalysisInStruct(node->firstchild->nextsibiling);
		return FL;
	}
	else
	{
		return NULL;
	}
}

static Type* StructSpecifierAnalysis(ParsingNode* node)
{
	assert(node->SymbolIndex == AStructSpecifier);

	Type* SpecifierType = (Type*)malloc(sizeof(Type));
	SpecifierType->kind = STRUCTURE;

	if(secondchild(node)->SymbolIndex == AOptTag)
	{
		//set structname
		ParsingNode* OptTagNode = secondchild(node);
		if(OptTagNode->kind!=Dummy)
		{
			ParsingNode* IDNode = OptTagNode->firstchild;
			SpecifierType->structure.structname = (char*)malloc(strlen(IDNode->IDname));
			strcpy(SpecifierType->structure.structname, IDNode->IDname);
		}
		else
		{
			SpecifierType->structure.structname = NULL;
		}

		//set struct field list
		
		SpecifierType->structure.member = DefListAnalysisInStruct(fourthchild(node));
		
		//ATTENTION: CHECK ERROR 15 !!!
		CheckSameNameInStruct(SpecifierType->structure.member);

		StructTypeTableEntry* STE = (StructTypeTableEntry*)malloc(sizeof(StructTypeTableEntry));
		STE->lineno = node->lineno;
		STE->TP = SpecifierType;
		STE->tail = NULL;

		//ATTENTION: CHECK ERROR 16 !!!
		CheckSameVarNameInSymbolTable(STE->TP->structure.structname, STE->lineno, CurrentSymbolTable, false);
		CheckSameVarNameInStructTypeTable(STE->TP->structure.structname, STE->lineno, CurrentStructTypeTable, false);
		InsertItemIntoStructTypeTable(STE, CurrentStructTypeTable);

		return SpecifierType;	
	}
	else
	{
		ParsingNode* TagNode = secondchild(node);
		ParsingNode* IDNode = TagNode->firstchild;

		// Need repair!!!!!
		SpecifierType = GetStructTypeFromTypeTable(IDNode->IDname, CurrentStructTypeTable);
		
		//ATTENTION: CHECK ERROR 17 !!!
		if(SpecifierType == NULL)
		{
			printf("\033[31mError type 17 at Line %d: Undefined structure \"%s\".\033[0m\n", 
					node->lineno,IDNode->IDname);
		}

		return SpecifierType;
	}
}

static Type* TYPEAnalysis(ParsingNode* node)
{
	assert(node->SymbolIndex == ATYPE);

	Type* SpecifierType = (Type*)malloc(sizeof(Type));
	SpecifierType->kind = BASIC;
	SpecifierType->basic = node->type;

	return SpecifierType;
}

static Type* SpecifierAnalysis(ParsingNode* node)
{
	assert(node->SymbolIndex == ASpecifier);

	if(node->firstchild->SymbolIndex == ATYPE)
	{
		return TYPEAnalysis(node->firstchild);
	}
	else
	{
		return StructSpecifierAnalysis(node->firstchild);
	}
}

static void VarDecAnalysisGlobal(ParsingNode* node, Type* InheritType)
{
	assert(node->SymbolIndex == AVarDec);

	if(node->childrenNum == 4)
	{
		ParsingNode* TypeNode = thirdchild(node);

		Type* subType = (Type*)malloc(sizeof(Type));
		subType->kind = ARRAY;
		subType->array.elem = InheritType;
		subType->array.size = TypeNode->int_value;

		VarDecAnalysisGlobal(node->firstchild, subType);
	}
	else
	{
		ParsingNode* IDNode = node->firstchild;

		SymbolTableEntry* SE = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
		SE->kind = VAR;
		SE->lineno = IDNode->lineno;
		SE->Variable.VariableName = (char*)malloc(strlen(IDNode->IDname));
		strcpy(SE->Variable.VariableName, IDNode->IDname);
		SE->Variable.VariableType = InheritType;
		SE->tail = NULL;

		//ATTENTION: CHECK ERROR 3 !!!
		CheckSameVarNameInSymbolTable(SE->Variable.VariableName, SE->lineno, CurrentSymbolTable, true);
		CheckSameVarNameInStructTypeTable(SE->Variable.VariableName, SE->lineno, CurrentStructTypeTable, true);
		InsertItemIntoSymbolTable(SE, CurrentSymbolTable);
	}
}

static void ExtDecListAnalysis(ParsingNode* node, Type* InheritType)
{
	assert(node->SymbolIndex == AExtDecList);

	if(node->childrenNum == 3)
	{
		VarDecAnalysisGlobal(node->firstchild, InheritType);
		ExtDecListAnalysis(thirdchild(node), InheritType);
	}
	else
	{
		VarDecAnalysisGlobal(node->firstchild, InheritType);
	}
}

static void ExtDefAnalysis(ParsingNode* node)
{
	assert(node->SymbolIndex == AExtDef);

	Type* InheritType = SpecifierAnalysis(node->firstchild);

	if(InheritType == NULL)return;

	if(secondchild(node)->SymbolIndex == AExtDecList)
	{
		ExtDecListAnalysis(secondchild(node), InheritType);
	}
	else if(secondchild(node)->SymbolIndex == AFunDec)
	{
		
	}
	return;
}

static void ExtDefListAnalysis(ParsingNode* node)
{
	assert(node->SymbolIndex == AExtDefList);

	if(node->kind != Dummy)
	{
		ExtDefAnalysis(node->firstchild);
		ExtDefListAnalysis(secondchild(node));
	}
	else return;

}

void SemanticAnalysis(ParsingNode* node)
{
	assert(node->SymbolIndex == AProgram);

	InitSymbolTable();
	ExtDefListAnalysis(node->firstchild);

	printf("check elem in root table\n");
	CheckElemInTable(RootSymbolTable);
}
