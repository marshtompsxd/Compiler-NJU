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
static InterCodeListHead* DefGenerateInFunction(ParsingNode* node);
static InterCodeListHead* DefListGenerateInFunction(ParsingNode* node);
static InterCodeListHead* StmtListGenerate(ParsingNode* node);
static InterCodeListHead* CompStGenerate(ParsingNode* node);
static InterCodeListHead* FunDecGenerate(ParsingNode* node);

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

static InterCodeListHead* DefGenerateInFunction(ParsingNode* node)
{
    assert(skind(node) == ADef);
    // need fix
    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    return list;
}

static InterCodeListHead* DefListGenerateInFunction(ParsingNode* node)
{
    assert(skind(node) == ADefList);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->kind != Dummy)
    {
        InterCodeListHead* sublist1 = DefGenerateInFunction(firstchild(node));
        MergeInterCodeList(sublist1, list);
        InterCodeListHead* sublist2 =DefListGenerateInFunction(secondchild(node));
        MergeInterCodeList(sublist1, list);
        return list;
    }
    else return list;
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
    assert(skind(firstchild(node)) == ANOT);
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

    return list;
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
            ICVarEntry* VE = LookUpForICVarEntry(firstchild(node)->IDname);
            assert(VE!=NULL);
            right = NewVOperand(OVALUE, VE->VIndex);
        }
        else if(skind(firstchild(node)) == AINT)
        {
            right = NewICOperand(firstchild(node)->int_value);
        }
        else if(skind(firstchild(node)) == AFLOAT)
        {
            right = NewFCOperand(firstchild(node)->float_value);
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
            InterCodeListHead* sublist2 = ExpGenerate(thirdchild(node), op2);

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
            int LIndex1 = NewLabelIndex();
            int LIndex2 = NewLabelIndex();

            InterCodeEntry *ICE2 = NewInterCodeEntryLABELDEC(LIndex1);
            InterCodeEntry *ICE4 = NewInterCodeEntryLABELDEC(LIndex2);
            InterCodeListHead* sublist = ConditionGenerate(node, LIndex1, LIndex2);


            if(result!=NULL)
            {
                Operand *zero = NewICOperand(0);
                InterCodeEntry *ICE1 = NewInterCodeEntryASSIGN(result, zero);
                InsertEntryIntoInterCodeList(ICE1, list);
            }
            MergeInterCodeList(sublist, list);
            InsertEntryIntoInterCodeList(ICE2, list);
            if(result!=NULL) {
                Operand *one = NewICOperand(1);
                InterCodeEntry *ICE3 = NewInterCodeEntryASSIGN(result, one);
                InsertEntryIntoInterCodeList(ICE3, list);
            }
            InsertEntryIntoInterCodeList(ICE4, list);
            return list;


        }
        else if(skind(secondchild(node)) == AASSIGNOP)
        {
            Operand* left;
            if(skind(firstchild(firstchild(node))) == AID)
            {
                left = GetLvalueIDOperand(firstchild(node));
            }
            else
            {
                assert(0);
                left = NewTOperand(OVALUE);
                InterCodeListHead* sublist1 = ExpGenerate(firstchild(node), left);
                MergeInterCodeList(sublist1, list);
            }

            Operand* right = NewTOperand(OVALUE);
            InterCodeListHead* sublist2 = ExpGenerate(thirdchild(node), right);
            MergeInterCodeList(sublist2, list);

            InterCodeEntry* ICE1 = NewInterCodeEntryASSIGN(left, right);
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
        assert(0);
    }


}

static InterCodeListHead* StmtGenerate(ParsingNode* node)
{
    assert(skind(node) == AStmt);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        //CompStGenerate(firstchild(node));
        return list;
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

static InterCodeListHead* StmtListGenerate(ParsingNode* node)
{
    assert(skind(node) == AStmtList);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->kind != Dummy)
    {
        InterCodeListHead* sublist1 = StmtGenerate(firstchild(node));
        MergeInterCodeList(sublist1, list);
        InterCodeListHead* sublist2 = StmtListGenerate(secondchild(node));
        MergeInterCodeList(sublist2, list);
        return list;
    }
    else return list;
}

static InterCodeListHead* CompStGenerate(ParsingNode* node)
{
    assert(skind(node) == ACompSt);


    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    //InterCodeListHead* sublist1 = DefListGenerateInFunction(secondchild(node));
    //MergeInterCodeList(sublist1, list);
    InterCodeListHead* sublist2 = StmtListGenerate(thirdchild(node));
    MergeInterCodeList(sublist2, list);
    return list;
}

static InterCodeListHead* FunDecGenerate(ParsingNode* node)
{
    assert(skind(node) == AFunDec);


    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;
    //...
    return list;
}

static void ExtDefGenerate(ParsingNode* node)
{
    assert(skind(node) == AExtDef);

    if(node->childrenNum == 3)
    {
        if(skind(secondchild(node)) == AFunDec)
        {
            //InterCodeListHead* sublist1 = FunDecGenerate(secondchild(node));
            //MergeInterCodeList(sublist1, RootInterCodeList);
            InterCodeListHead* sublist2 = CompStGenerate(thirdchild(node));
            MergeInterCodeList(sublist2, RootInterCodeList);
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

    ProgramGenerate(ParsingRoot);
    PrintInterCodeList(RootInterCodeList);
}