//
// Created by sunxudong on 12/27/17.
//

#include <symbol_table.h>
#include "../common.h"
#include "../intercode/IC.h"
#include "../intercode/ICTable.h"
#include "../intercode/InterCode.h"
#include "spim.h"

int VSize;
int TSize;
int VBegin;
int TBegin;
int* VOffset;
int* TOffset;

AIRE* AIRV;
AISE* AISV;

void InitRootInterCodeList()
{
    InterCodeEntry *ICVhead, *ICVtail;
    ICVhead = RootInterCodeList->head;
    ICVtail = ICVhead->prev;

    ICVhead->prev = NULL;
    ICVtail->next = NULL;

    AIRV = (AIRE*)malloc(sizeof(AIRE)*4);
    AISV = (AISE*)malloc(sizeof(AISV)*100);
}

void GetVTSize()
{
    TSize = TIndex;
    VSize = 0;
    ICVarEntry* ICV;
    for(ICV = RootICVarTable->head; ICV != NULL; ICV = ICV->next)
    {
        Type* TP = ICV->VariableType;
        if(TP->kind == BASIC)VSize++;
        else if(TP->kind == ARRAY)
        {
            assert(TP->array.dim == 1);
            VSize = VSize + TP->array.DimSize[0];
        }
        else assert(0);
    }

    VOffset = (int*)malloc((unsigned)4*VIndex);
    TOffset = (int*)malloc((unsigned)4*TIndex);

    int i;
    int offset = 0;
    VOffset[0] = 0;
    for(ICV = RootICVarTable->head; ICV->next != NULL; ICV = ICV->next)
    {
        ICVarEntry* ICVnxt = ICV->next;
        Type* TP = ICV->VariableType;
        if(TP->kind == BASIC)
        {
            offset++;
            VOffset[ICVnxt->VIndex] = offset;
        }
        else if(TP->kind == ARRAY)
        {
            assert(TP->array.dim == 1);
            offset = offset + TP->array.DimSize[0];
            VOffset[ICVnxt->VIndex] = offset;
        }
        else assert(0);
    }

    offset = 0;
    for(i = 0; i<TIndex; i++)
    {
        TOffset[i] = offset;
        offset++;
    }

    VBegin = 8;                 // v_i is at ( $fp - ( VBegin + VOffset[i]*4 )) in stack
    TBegin = VBegin + VSize*4;  // t_i is at ( $fp - ( TBegin + TOffset[i]*4 )) in stack


    /* now in static data segment(64K):
     *
     *         --------------  high address
     *         |   T data   |
     *         --------------
     *         |   V data   |
     *         --------------  <- $gp (points to the middle of 64K DATA SEGMENT)
     *         |            |
     *         |            |
     *         |            |
     *         --------------  low address
     */



}

void MachineCodePreparation(FILE* stream)
{
    fprintf(stream,
            ".data\n"
            "_prompt: .asciiz \"Enter an integer:\"\n"
            "_ret: .asciiz \"\\n\"\n"
            ".globl main\n"
            ".text\n"
            "read:\n"
            "  li $v0, 4\n"
            "  la $a0, _prompt\n"
            "  syscall\n"
            "  li $v0, 5\n"
            "  syscall\n"
            "  jr $ra\n\n"
            "write:\n"
            "  li $v0, 1\n"
            "  syscall\n"
            "  li $v0, 4\n"
            "  la $a0, _ret\n"
            "  syscall\n"
            "  move $v0, $0\n"
            "  jr $ra\n\n");
}

void FUNGenerator(InterCode* IC, FILE* stream, int argNum)
{
    fprintf(stream, "%s:\n", IC->FUN.funName);

    if(strcmp(IC->FUN.funName, "main") == 0)
    {
        assert(argNum == 0);

        int frameSize = 2 * 4;
        fprintf(stream, "  subu $sp, $sp, %d\n", frameSize );
        fprintf(stream, "  sw $fp, (%d - 8)($sp)\n", frameSize);
        fprintf(stream, "  addi $fp, $sp, %d\n", frameSize);

        /* now in main function:
         *
         *                         high address
         *         --------------  <- $fp
         *         |   blank    |
         *         --------------
         *         |   old fp   |
         *         --------------  <- $sp
         *                         low address
         */
    }
    else
    {
        int frameSize = 2 * 4;
        fprintf(stream, "  subu $sp, $sp, %d\n", frameSize );
        fprintf(stream, "  sw $ra, (%d - 4)($sp)\n", frameSize);
        fprintf(stream, "  sw $fp, (%d - 8)($sp)\n", frameSize);
        fprintf(stream, "  addi $fp, $sp, %d\n", frameSize);

        assert(0);
        // To-Do: load args into static data segment

       /* now in xxx function:
        *                         high address
        *         --------------
        *         |            |
        *         |    args    |
        *         |            |
        *         --------------  <- $fp
        *         |  ret addr  |
        *         --------------
        *         |   old fp   |
        *         --------------  <- $sp
        *                         low address
        */

    }
}


InterCodeEntry* ParamFunGenerator(InterCodeEntry* ICV, FILE* stream)
{
    InterCodeEntry* entry;
    int argNum = 0;
    for( entry = ICV;entry->IC->kind==IPARAM; entry = entry->next)
    {
        if(argNum<=3)
        {
            Operand* op = entry->IC->PARAM.parameter;
            AIRV[argNum].kind = op->kind;
            assert(op->kind == OVAR);
            AIRV[argNum].Index = op->VIndex;
        }
        else
        {
            Operand* op = entry->IC->PARAM.parameter;
            AISV[argNum - 4].kind = op->kind;
            assert(op->kind == OVAR);
            AISV[argNum - 4].Index = op->VIndex;
        }
        argNum++;
    }

    assert(entry->IC->kind == IFUNCTION);


    FUNGenerator(entry->IC, stream, argNum);

    return entry;


}

void MachineCodeGenerator(char* filename)
{
    FILE* fp;

    if(filename == NULL)
    {
        fp = stdout;
    }
    else
    {
        fp = fopen(filename, "w");
        assert(fp != NULL);
    }

    InitRootInterCodeList();
    MachineCodePreparation(fp);
    GetVTSize();


    InterCodeEntry* ICV ;
    for (ICV = RootInterCodeList->head;  ICV->next!=NULL ; ICV = ICV->next)
    {
        InterCode* IC = ICV->IC;
        switch (IC->kind)
        {
            case IFUNCTION: {
                FUNGenerator(IC, fp, 0); break;
            }
            case IPARAM: {
                ICV = ParamFunGenerator(ICV, fp); break;
            }
            case IASSIGN:break;
            default:assert(0);
        }
    }

}