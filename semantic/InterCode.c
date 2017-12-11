#include "InterCode.h"
#include "../common.h"
#include "list.h"
#include "check.h"

ICVarTableHead* RootICVarTable;
ICFunTableHead* RootICFunTable;
InterCodeListHead* RootInterCodeList;


static void InitICTable()
{
    RootICVarTable = (ICVarTableHead*)malloc(sizeof(ICVarTableHead));
    RootICVarTable->head = NULL;

    RootICFunTable = (ICFunTableHead*)malloc(sizeof(ICFunTableHead));
    RootICFunTable->head = NULL;

    RootInterCodeList = (InterCodeListHead*)malloc(sizeof(InterCodeListHead));
    RootInterCodeList->head = NULL;

    GenerateICVarTable(RootSymbolTable);
    GenerateICFunTable(RootSymbolTable);

}


void InterCodeGenerator()
{
    InitICTable();
    printf("print ICVarTable\n");
    CheckElemInICVarTable(RootICVarTable);
    printf("print ICFunTable\n");
    CheckElemInICFunTable(RootICFunTable);
}