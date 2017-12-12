#include "InterCode.h"
#include "../common.h"
#include "ICTable.h"
#include "ParsingNode.h"


static void VarDecGenerateInStruct(ParsingNode* node);
static void DecGenerateInStruct(ParsingNode* node);
static void DecListGenerateInStruct(ParsingNode* node);
static void DefGenerateInStruct(ParsingNode* node);
static void DefListGenerateInStruct(ParsingNode* node);

static void StructSpecifierGenerate(ParsingNode* node);
static void TYPEGenerate(ParsingNode* node);
static void SpecifierGenerate(ParsingNode* node);
static void VarDecGenerateGlobal(ParsingNode* node);
static void ExtDecListGenerate(ParsingNode* node);

static void VarDecGenerateInParam(ParsingNode* node);
static void ParamDecGenerate(ParsingNode* node);
static void VarListGenerate(ParsingNode* node);
static void VarDecGenerateInFunction(ParsingNode* node);
static void DecGenerateInFunction(ParsingNode* node);
static void DecListGenerateInFunction(ParsingNode* node);
static void DefGenerateInFunction(ParsingNode* node);
static void DefListGenerateInFunction(ParsingNode* node);
static void StmtListGenerate(ParsingNode* node);
static void CompStGenerate(ParsingNode* node);
static void FunDecGenerate(ParsingNode* node);

static void ArgsGenerate(ParsingNode* node);
static Operand* ExpGenerate(ParsingNode* node);
static void StmtGenerate(ParsingNode* node);


static void ExtDefGenerate(ParsingNode* node);
static void ExtDefListGenerate(ParsingNode* node);
static void ProgramGenerate(ParsingNode* node);


ICVarTableHead* RootICVarTable;
ICFunTableHead* RootICFunTable;
InterCodeListHead* RootInterCodeList;
int VIndex, TIndex;

static void InitICTable()
{
    VIndex = TIndex = 0;

    RootICVarTable = (ICVarTableHead*)malloc(sizeof(ICVarTableHead));
    RootICVarTable->head = NULL;

    RootICFunTable = (ICFunTableHead*)malloc(sizeof(ICFunTableHead));
    RootICFunTable->head = NULL;

    RootInterCodeList = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    RootInterCodeList->head = NULL;

    GenerateICVarTable(RootSymbolTable);
    GenerateICFunTable(RootSymbolTable);

}

static void DefGenerateInFunction(ParsingNode* node)
{
    assert(skind(node) == ADef);
}

static void DefListGenerateInFunction(ParsingNode* node)
{
    assert(skind(node) == ADefList);

    if(node->kind != Dummy)
    {
        DefGenerateInFunction(firstchild(node));
        DefListGenerateInFunction(secondchild(node));
    }
    else return;
}

static Operand* ExpGenerate(ParsingNode* node)
{
    assert(skind(node) == AExp);

    

}

static void StmtGenerate(ParsingNode* node)
{
    assert(skind(node) == AStmt);

    if(node->childrenNum == 1)
    {
        CompStGenerate(firstchild(node));
    }
    else if(node->childrenNum == 2)
    {
        ExpGenerate(firstchild(node));
    }
    else if(node->childrenNum == 3)
    {
        Operand* retValue = ExpGenerate(secondchild(node));
        // new ret code...
    }
}

static void StmtListGenerate(ParsingNode* node)
{
    assert(skind(node) == AStmtList);

    if(node->kind != Dummy)
    {
        StmtGenerate(firstchild(node));
        StmtListGenerate(secondchild(node));
    }
    else return;
}

static void CompStGenerate(ParsingNode* node)
{
    assert(skind(node) == ACompSt);

    DefListGenerateInFunction(secondchild(node));
    StmtListGenerate(thirdchild(node));
}

static void ExtDefGenerate(ParsingNode* node)
{
    assert(skind(node) == AExtDef);

    if(node->childrenNum == 3)
    {
        if(skind(secondchild(node)) == AFunDec)
        {
            CompStGenerate(secondchild(node));
        }
    }
    else return;
}

static void ExtDefListGenerate(ParsingNode* node)
{
    assert(skind(node) == AExtDefList);

    if(node->kind != Dummy)
    {
        ExtDefGenerate(firstchild(node));
        ExtDefListGenerate(secondchild(node));
    }
    else return;
}

static void ProgramGenerate(ParsingNode* node)
{
    ExtDefListGenerate(firstchild(node));
}

void InterCodeGenerator()
{
    InitICTable();
    printf("print ICVarTable\n");
    CheckElemInICVarTable(RootICVarTable);
    printf("print ICFunTable\n");
    CheckElemInICFunTable(RootICFunTable);
}