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
static InterCodeListHead* ExpGenerate(ParsingNode* node, Operand* place);
static InterCodeListHead* StmtGenerate(ParsingNode* node);


static void ExtDefGenerate(ParsingNode* node);
static void ExtDefListGenerate(ParsingNode* node);
static void ProgramGenerate(ParsingNode* node);

InterCodeListHead* ConditionRELOPGenerate(ParsingNode* node, int LIndexT, int LIndexF);
InterCodeListHead* ConditionANDGenerate(ParsingNode* node, int LIndexT, int LIndexF);
InterCodeListHead* ConditionORGenerate(ParsingNode* node, int LIndexT, int LIndexF);
InterCodeListHead* ConditionNOTGenerate(ParsingNode* node, int LIndexT, int LIndexF);
InterCodeListHead* ConditionOtherGenerate(ParsingNode* node, int LIndexT, int LIndexF);
InterCodeListHead* ConditionGenerate(ParsingNode* node, int LIndex1, int LIndex2);

ICVarTableHead* RootICVarTable;
ICFunTableHead* RootICFunTable;
InterCodeListHead* RootInterCodeList;
int VIndex, TIndex, LIndex;

static void InitICTable()
{
    VIndex = TIndex = LIndex = 0;

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

InterCodeListHead* ConditionRELOPGenerate(ParsingNode* node, int LIndexT, int LIndexF)
{
    assert(skind(secondchild(node)) == ARELOP);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    Operand* op1 = NewTOperand(OVALUE);
    Operand* op2 = NewTOperand(OVALUE);

    InterCodeListHead* sublist1 = ExpGenerate(firstchild(node), op1);
    InterCodeListHead* sublist2 = ExpGenerate(thirdchild(node), op2);

    int relop = (secondchild(node))->relop_kind;

    InterCodeEntry* ICE1 = NewInterCodeEntryIFGT(op1, op2, relop, LIndexT);
    InterCodeEntry* ICE2 = NewInterCodeEntryGT(LIndexF);

    MergeInterCodeList(sublist1, list);
    MergeInterCodeList(sublist2, list);
    InsertEntryIntoInterCodeList(ICE1, list);
    InsertEntryIntoInterCodeList(ICE2, list);

    return list;
}

InterCodeListHead* ConditionANDGenerate(ParsingNode* node, int LIndexT, int LIndexF)
{
    assert(skind(secondchild(node)) == AAND);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    int LIndex1 = NewLabelIndex();

    InterCodeListHead* sublist1 = ConditionGenerate(firstchild(node), LIndex1, LIndexF);
    InterCodeListHead* sublist2 = ConditionGenerate(thirdchild(node), LIndexT, LIndexF);

    InterCodeEntry* ICE = NewInterCodeEntryLABELDEC(LIndex1);

    MergeInterCodeList(sublist1, list);
    InsertEntryIntoInterCodeList(ICE, list);
    MergeInterCodeList(sublist2, list);

    return list;

}

InterCodeListHead* ConditionORGenerate(ParsingNode* node, int LIndexT, int LIndexF)
{
    assert(skind(secondchild(node)) == AOR);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    int LIndex1 = NewLabelIndex();

    InterCodeListHead* sublist1 = ConditionGenerate(firstchild(node), LIndexT, LIndex1);
    InterCodeListHead* sublist2 = ConditionGenerate(thirdchild(node), LIndexT, LIndexF);

    InterCodeEntry* ICE = NewInterCodeEntryLABELDEC(LIndex1);

    MergeInterCodeList(sublist1, list);
    InsertEntryIntoInterCodeList(ICE, list);
    MergeInterCodeList(sublist2, list);

    return list;

}

InterCodeListHead* ConditionNOTGenerate(ParsingNode* node, int LIndexT, int LIndexF)
{
    return ConditionGenerate(secondchild(node), LIndexF, LIndexT );
}

InterCodeListHead* ConditionOtherGenerate(ParsingNode* node, int LIndexT, int LIndexF)
{
    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    Operand* t = NewTOperand(OVALUE);
    Operand* zero = NewICOperand(0);

    InterCodeListHead* sublist = ExpGenerate(node, t);

    InterCodeEntry* ICE1 = NewInterCodeEntryIFGT(t, zero, NEQ, LIndexT);
    InterCodeEntry* ICE2 = NewInterCodeEntryGT(LIndexF);

    MergeInterCodeList(sublist, list);
    InsertEntryIntoInterCodeList(ICE1, list);
    InsertEntryIntoInterCodeList(ICE2, list);
}

InterCodeListHead* ConditionGenerate(ParsingNode* node, int LIndexT, int LIndexF)
{
    assert(skind(node) == AExp);

    if(skind(secondchild(node)) == ARELOP)
        return ConditionRELOPGenerate(node, LIndexT, LIndexF);
    else if(skind(secondchild(node)) == AAND)
        return ConditionANDGenerate(node, LIndexT, LIndexF);
    else if(skind(secondchild(node)) == AOR)
        return ConditionORGenerate(node, LIndexT, LIndexF);
    else if(skind(firstchild(node)) == ANOT)
        return ConditionNOTGenerate(node, LIndexT, LIndexF);
    else
        return ConditionOtherGenerate(node, LIndexT, LIndexF);
}



static InterCodeListHead* ExpGenerate(ParsingNode* node, Operand* result)
{
    assert(skind(node) == AExp);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        Operand* right;
        if(skind(firstchild(node)) == AID)
        {
            ICVarEntry* VE = LookUpForICVarEntry(node->IDname);
            assert(VE!=NULL);
            right = NewVOperand(OVALUE, VE->VIndex);
        }
        else if(skind(firstchild(node)) == AINT)
        {
            right = NewICOperand(node->int_value);
        }
        else if(skind(firstchild(node)) == AFLOAT)
        {
            right = NewFCOperand(node->float_value);
        }
        else assert(0);

        if(result!=NULL)
        {
            InterCodeEntry* ICE = NewInterCodeEntryASSIGN(result, right);
            InsertEntryIntoInterCodeList(ICE, list);
        }

        return list;
    }
    else if(node->childrenNum == 2)
    {
        return NULL;
    }
    else if(node->childrenNum == 3)
    {

        if(IsArithmeticNode(secondchild(node)))
        {
            Operand* op1 = NewTOperand(OVALUE);
            Operand* op2 = NewTOperand(OVALUE);

            InterCodeListHead* sublist1 = ExpGenerate(firstchild(node), op1);
            InterCodeListHead* sublist2 = ExpGenerate(firstchild(node), op2);

            MergeInterCodeList(sublist1, list);
            MergeInterCodeList(sublist2, list);

            if(result!= NULL)
            {
                int kind = arithmeticConvert(skind(secondchild(node)));
                InterCodeEntry* ICE = NewInterCodeEntryBINOP(kind, result, op1, op2);
                InsertEntryIntoInterCodeList(ICE, list);
            }

            return list;

        }
        else if(IsRELOPNode(secondchild(node)) || IsLogicNode(secondchild(node)))
        {

        }
        else if(skind(secondchild(node)) == AASSIGNOP)
        {
            Operand* left = GetLvalueOperand(firstchild(node));
            Operand* right = NewTOperand(OVALUE);
            InterCodeListHead* sublist = ExpGenerate(thirdchild(node), right);

            InterCodeEntry* ICE1 = NewInterCodeEntryASSIGN(left, right);
            MergeInterCodeList(sublist, list);
            InsertEntryIntoInterCodeList(ICE1, list);

            if(result!=NULL){
                InterCodeEntry* ICE2 = NewInterCodeEntryASSIGN(result, left);
                InsertEntryIntoInterCodeList(ICE2, list);
            }


            return list;
        }
        else if(skind(firstchild(node)) == ALP) // ( exp )
        {
            return ExpGenerate(secondchild(node), result);
        }
        else if(skind(firstchild(node)) == AID) // call function
        {

        }
        else if(skind(secondchild(node)) == ADOT) // structure field
        {

        }
        else assert(0);
    }
    else
    {
        return NULL;
    }


}

static InterCodeListHead* StmtGenerate(ParsingNode* node)
{
    assert(skind(node) == AStmt);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        CompStGenerate(firstchild(node));
    }
    else if(node->childrenNum == 2)
    {
        InterCodeListHead* sublist = ExpGenerate(firstchild(node), NULL);
        MergeInterCodeList(sublist, list);
        return list;
    }
    else if(node->childrenNum == 3)
    {
        assert(0);
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