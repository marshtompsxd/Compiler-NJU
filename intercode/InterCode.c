#include "InterCode.h"
#include "../common.h"
#include "ICTable.h"
#include "ParsingNode.h"

static int StructSpecifierGenerate(ParsingNode* node);
static int SpecifierGenerate(ParsingNode* node);

static InterCodeListHead* VarDecGenerateInParam(ParsingNode* node);
static InterCodeListHead* ParamDecGenerate(ParsingNode* node);
static InterCodeListHead* VarListGenerate(ParsingNode* node);
static InterCodeListHead* VarDecGenerateInFunction(ParsingNode* node, int size, bool ifDec);
static InterCodeListHead* DecGenerateInFunction(ParsingNode* node, int size);
static InterCodeListHead* DecListGenerateInFunction(ParsingNode* node, int size);
static InterCodeListHead* DefGenerateInFunction(ParsingNode* node);
static InterCodeListHead* DefListGenerateInFunction(ParsingNode* node);
static InterCodeListHead* StmtListGenerate(ParsingNode* node);
static InterCodeListHead* CompStGenerate(ParsingNode* node);
static InterCodeListHead* FunDecGenerate(ParsingNode* node);

static InterCodeListHead* ArgsGenerate(ParsingNode* node, ArgListHead* alist);
static InterCodeListHead* ExpGenerate(ParsingNode* node, Operand* result);
static InterCodeListHead* StmtGenerate(ParsingNode* node);


static void ExtDefGenerate(ParsingNode* node);
static void ExtDefListGenerate(ParsingNode* node);
static void ProgramGenerate(ParsingNode* node);

static InterCodeListHead* ConditionRELOPGenerate(ParsingNode* node, int LIndexT, int LIndexF);
static InterCodeListHead* ConditionANDGenerate(ParsingNode* node, int LIndexT, int LIndexF);
static InterCodeListHead* ConditionORGenerate(ParsingNode* node, int LIndexT, int LIndexF);
static InterCodeListHead* ConditionNOTGenerate(ParsingNode* node, int LIndexT, int LIndexF);
static InterCodeListHead* ConditionOtherGenerate(ParsingNode* node, int LIndexT, int LIndexF);
static InterCodeListHead* ConditionGenerate(ParsingNode* node, int LIndexT, int LIndexF);

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

static InterCodeListHead* VarDecGenerateInFunction(ParsingNode* node, int size, bool ifDec)
{
    assert(skind(node) == AVarDec);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1 && !ifDec)return list;

    if(node->childrenNum == 4)
    {
        int num = thirdchild(node)->int_value;
        InterCodeListHead* sublist = VarDecGenerateInFunction(firstchild(node), size*num, true);
        MergeInterCodeList(sublist, list);
    }
    else
    {
        Operand* address;
        ICVarEntry* VE = LookUpForICVarEntry(firstchild(node)->IDname);
        assert(VE!=NULL);
        address = NewVOperand(OVALUE, VE->VIndex);
        InterCodeEntry* ICE = NewInterCodeEntryDEC(address, size);
        InsertEntryIntoInterCodeList(ICE, list);
    }
    return list;
}

static InterCodeListHead* DecGenerateInFunction(ParsingNode* node, int size)
{
    assert(skind(node) == ADec);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 3)
    {
        Operand* left = GetLvalueIDOperand(firstchild(node));
        Operand* right = NewTOperand(OVALUE);
        InterCodeListHead* sublist = ExpGenerate(thirdchild(node), right);
        MergeInterCodeList(sublist, list);

        InterCodeEntry* ICE1 = NewInterCodeEntryASSIGN(left, right);
        InsertEntryIntoInterCodeList(ICE1, list);
    }
    else
    {
        InterCodeListHead* sublist = VarDecGenerateInFunction(firstchild(node), size, false);
        MergeInterCodeList(sublist, list);
    }


    return list;
}

static InterCodeListHead* DecListGenerateInFunction(ParsingNode* node, int size)
{
    assert(skind(node) == ADecList);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        InterCodeListHead* sublist = DecGenerateInFunction(firstchild(node),size);
        MergeInterCodeList(sublist, list);
    }
    else
    {
        InterCodeListHead* sublist1 = DecGenerateInFunction(firstchild(node),size);
        InterCodeListHead* sublist2 = DecListGenerateInFunction(thirdchild(node), size);
        MergeInterCodeList(sublist1, list);
        MergeInterCodeList(sublist2, list);
    }


    return list;
}

static int StructSpecifierGenerate(ParsingNode* node)
{
    assert(skind(node) == AStructSpecifier);
    assert(0);
}

static int SpecifierGenerate(ParsingNode* node)
{
    assert(skind(node) == ASpecifier);
    if(skind(firstchild(node)) == ATYPE)return 4;
    else return StructSpecifierGenerate(firstchild(node));
}

static InterCodeListHead* DefGenerateInFunction(ParsingNode* node)
{
    assert(skind(node) == ADef);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    int size = SpecifierGenerate(firstchild(node));
    InterCodeListHead* sublist = DecListGenerateInFunction(secondchild(node), size);
    MergeInterCodeList(sublist, list);

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
        MergeInterCodeList(sublist2, list);
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

    if(node->childrenNum == 1)
        return ConditionOtherGenerate(node, LIndexT, LIndexF);
    else if(skind(secondchild(node)) == ARELOP)
        return ConditionRELOPGenerate(node, LIndexT, LIndexF);
    else if(skind(secondchild(node)) == AAND)
        return ConditionANDGenerate(node, LIndexT, LIndexF);
    else if(skind(secondchild(node)) == AOR)
        return ConditionORGenerate(node, LIndexT, LIndexF);
    else if(skind(firstchild(node)) == ANOT)
        return ConditionNOTGenerate(node, LIndexT, LIndexF);
    else if(skind(firstchild(node)) == ALP)
        return ConditionGenerate(secondchild(node), LIndexT, LIndexF);
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
        if(skind(firstchild(node)) == AMINUS)
        {
            Operand* t = NewTOperand(OVALUE);
            Operand* zero = NewICOperand(0);
            InterCodeListHead* sublist = ExpGenerate(secondchild(node), t);
            MergeInterCodeList(sublist, list);

            if(result!=NULL)
            {
                InterCodeEntry* ICE = NewInterCodeEntryBINOP(ISUB, result, zero, t);
                InsertEntryIntoInterCodeList(ICE, list);
            }

            return list;
        }
        else if(skind(firstchild(node)) == ANOT)
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
        else assert(0);
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
            if(strcmp(firstchild(node)->IDname, "read") == 0)
            {
                InterCodeEntry* ICE = NewInterCodeEntryREAD(result);
                InsertEntryIntoInterCodeList(ICE, list);
            }
            else
            {
                InterCodeEntry* ICE = NewInterCodeEntryCALL(result, firstchild(node)->IDname);
                InsertEntryIntoInterCodeList(ICE, list);
            }
            return list;
        }
        else if(skind(secondchild(node)) == ADOT) // structure field
        {
            assert(0);
        }
        else assert(0);
    }
    else if(node->childrenNum == 4)
    {
        if(skind(firstchild(node)) == AID)
        {
            ArgListHead* alist = (ArgListHead*)malloc(sizeof(ArgListHead));
            alist->head = NULL;
            InterCodeListHead* sublist = ArgsGenerate(thirdchild(node), alist);
            MergeInterCodeList(sublist, list);

            if(strcmp(firstchild(node)->IDname, "write") == 0)
            {
                InterCodeEntry* ICE = NewInterCodeEntryWRITE(alist->head->arg);
                InsertEntryIntoInterCodeList(ICE, list);

            }
            else
            {
                ArgEntry* AE;
                for(AE = alist->head; AE!=NULL; AE = AE->next)
                {
                    InterCodeEntry* AICE = NewInterCodeEntryARG(AE->arg);
                    InsertEntryIntoInterCodeList(AICE, list);
                }
                InterCodeEntry* ICE = NewInterCodeEntryCALL(result, firstchild(node)->IDname);
                InsertEntryIntoInterCodeList(ICE, list);
            }




            return list;
        }
        else
        {
            assert(0);
        }
    }


}

static InterCodeListHead* ArgsGenerate(ParsingNode* node, ArgListHead* alist)
{
    assert(skind(node) == AArgs);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        Operand* t = NewTOperand(OVALUE);
        InterCodeListHead* sublist = ExpGenerate(firstchild(node), t);
        ArgEntry* AE = NewArgEntry(t);
        PushEntryIntoArgList(AE, alist);
        MergeInterCodeList(sublist, list);
        return list;

    }
    else
    {
        Operand* t = NewTOperand(OVALUE);
        InterCodeListHead* sublist1 = ExpGenerate(firstchild(node), t);
        ArgEntry* AE = NewArgEntry(t);
        PushEntryIntoArgList(AE, alist);
        InterCodeListHead* sublist2 = ArgsGenerate(thirdchild(node), alist);

        MergeInterCodeList(sublist1, list);
        MergeInterCodeList(sublist2, list);
        return list;
    }

}

static InterCodeListHead* StmtGenerate(ParsingNode* node)
{
    assert(skind(node) == AStmt);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        InterCodeListHead* sublist = CompStGenerate(firstchild(node));
        MergeInterCodeList(sublist, list);
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
        Operand* t = NewTOperand(OVALUE);
        InterCodeListHead* sublist = ExpGenerate(secondchild(node), t);
        InterCodeEntry* ICE = NewInterCodeEntryRET(t);
        MergeInterCodeList(sublist, list);
        InsertEntryIntoInterCodeList(ICE, list);
        return list;
    }
    else if(node->childrenNum == 5)
    {
        if(skind(firstchild(node)) == AIF)
        {
            int LIndex1 = NewLabelIndex();
            int LIndex2 = NewLabelIndex();
            InterCodeEntry* ICE1 = NewInterCodeEntryLABELDEC(LIndex1);
            InterCodeEntry* ICE2 = NewInterCodeEntryLABELDEC(LIndex2);

            InterCodeListHead* sublist1 = ConditionGenerate(thirdchild(node), LIndex1, LIndex2);
            InterCodeListHead* sublist2 = StmtGenerate(fifthchild(node));

            MergeInterCodeList(sublist1, list);
            InsertEntryIntoInterCodeList(ICE1, list);
            MergeInterCodeList(sublist2, list);
            InsertEntryIntoInterCodeList(ICE2, list);
        }
        else
        {
            int LIndex1 = NewLabelIndex();
            int LIndex2 = NewLabelIndex();
            int LIndex3 = NewLabelIndex();
            InterCodeEntry* ICE1 = NewInterCodeEntryLABELDEC(LIndex1);
            InterCodeEntry* ICE2 = NewInterCodeEntryLABELDEC(LIndex2);
            InterCodeEntry* ICE3 = NewInterCodeEntryLABELDEC(LIndex3);

            InterCodeEntry* ICEGT1 = NewInterCodeEntryGT(LIndex1);

            InterCodeListHead* sublist1 = ConditionGenerate(thirdchild(node), LIndex2, LIndex3);
            InterCodeListHead* sublist2 = StmtGenerate(fifthchild(node));

            InsertEntryIntoInterCodeList(ICE1, list);
            MergeInterCodeList(sublist1, list);
            InsertEntryIntoInterCodeList(ICE2, list);
            MergeInterCodeList(sublist2, list);
            InsertEntryIntoInterCodeList(ICEGT1, list);
            InsertEntryIntoInterCodeList(ICE3, list);

        }
        return list;

    }
    else if(node->childrenNum == 7)
    {
        int LIndex1 = NewLabelIndex();
        int LIndex2 = NewLabelIndex();
        int LIndex3 = NewLabelIndex();
        InterCodeEntry* ICE1 = NewInterCodeEntryLABELDEC(LIndex1);
        InterCodeEntry* ICE2 = NewInterCodeEntryLABELDEC(LIndex2);
        InterCodeEntry* ICE3 = NewInterCodeEntryLABELDEC(LIndex3);

        InterCodeEntry* ICEGT3 = NewInterCodeEntryGT(LIndex3);

        InterCodeListHead* sublist1 = ConditionGenerate(thirdchild(node), LIndex1, LIndex2);
        InterCodeListHead* sublist2 = StmtGenerate(fifthchild(node));
        InterCodeListHead* sublist3 = StmtGenerate(seventhchild(node));

        MergeInterCodeList(sublist1, list);
        InsertEntryIntoInterCodeList(ICE1, list);
        MergeInterCodeList(sublist2, list);
        InsertEntryIntoInterCodeList(ICEGT3, list);
        InsertEntryIntoInterCodeList(ICE2, list);
        MergeInterCodeList(sublist3, list);
        InsertEntryIntoInterCodeList(ICE3, list);

        return list;

    }
    else assert(0);
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

    InterCodeListHead* sublist1 = DefListGenerateInFunction(secondchild(node));
    MergeInterCodeList(sublist1, list);
    InterCodeListHead* sublist2 = StmtListGenerate(thirdchild(node));
    MergeInterCodeList(sublist2, list);
    return list;
}

static InterCodeListHead* VarDecGenerateInParam(ParsingNode* node)
{
    assert(skind(node) == AVarDec);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        Operand* param = GetLvalueIDOperand(node);
        InterCodeEntry* ICE = NewInterCodeEntryPARAM(param);
        InsertEntryIntoInterCodeList(ICE, list);
    }
    else
    {
        InterCodeListHead* sublist = VarDecGenerateInParam(firstchild(node));
        MergeInterCodeList(sublist, list);
    }
    return list;
}

static InterCodeListHead* ParamDecGenerate(ParsingNode* node)
{
    assert(skind(node) == AParamDec);

    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;
    InterCodeListHead* sublist = VarDecGenerateInParam(secondchild(node));
    MergeInterCodeList(sublist, list);

    return list;
}

static InterCodeListHead* VarListGenerate(ParsingNode* node)
{
    assert(skind(node) == AVarList);
    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    if(node->childrenNum == 1)
    {
        InterCodeListHead* sublist = ParamDecGenerate(firstchild(node));
        MergeInterCodeList(sublist, list);
    }
    else
    {
        InterCodeListHead* sublist1 = ParamDecGenerate(firstchild(node));
        InterCodeListHead* sublist2 = VarListGenerate(thirdchild(node));
        MergeInterCodeList(sublist1, list);
        MergeInterCodeList(sublist2, list);
    }
    return list;
}

static InterCodeListHead* FunDecGenerate(ParsingNode* node)
{
    assert(skind(node) == AFunDec);


    InterCodeListHead* list = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    list->head = NULL;

    InterCodeEntry* ICE = NewInterCodeEntryFUN(firstchild(node)->IDname);
    InsertEntryIntoInterCodeList(ICE, list);

    if(node->childrenNum == 4)
    {
        InterCodeListHead* sublist = VarListGenerate(thirdchild(node));
        MergeInterCodeList(sublist, list);
    }

    return list;
}

static void ExtDefGenerate(ParsingNode* node)
{
    assert(skind(node) == AExtDef);

    if(node->childrenNum == 3)
    {
        if(skind(secondchild(node)) == AFunDec)
        {
            InterCodeListHead* sublist1 = FunDecGenerate(secondchild(node));
            MergeInterCodeList(sublist1, RootInterCodeList);
            InterCodeListHead* sublist2 = CompStGenerate(thirdchild(node));
            MergeInterCodeList(sublist2, RootInterCodeList);
        }
    }
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
    //printf("print ICFunTable\n");
    //CheckElemInICFunTable(RootICFunTable);

    ProgramGenerate(ParsingRoot);
    PrintInterCodeList(RootInterCodeList);
}