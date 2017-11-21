#ifndef __LIST_H__
#define __LIST_H__

#include "symbol_table.h"

FieldList* FLTail(FieldList* FL)
{
	while(FL->tail!=NULL)
	{
		FL = FL->tail;
	}
	return FL;
}

void InsertItemIntoSymbolTable(SymbolTableEntry* item, SymbolTableHead* table)
{
	/* you can choose to insert at head but I don't like it...
	item->tail = table->head;
	table->head = item;
	*/

	/*I prefer to insert at tail even though it is slower...
	*/
	if(table->head == NULL)
	{
		item->tail = NULL;
		table->head = item;
	}
	else
	{
		SymbolTableEntry* SE;
		for(SE = table->head; SE->tail != NULL; SE = SE->tail);
		SE->tail = item;
		item->tail = NULL;
	}
}

void InsertItemIntoStructTypeTable(StructTypeTableEntry* item, StructTypeTableHead* table)
{
	/* you can choose to insert at head but I don't like it...
	item->tail = table->head;
	table->head = item;
	*/

	/*I prefer to insert at tail even though it is slower...
	*/
	if(table->head == NULL)
	{
		item->tail = NULL;
		table->head = item;
	}
	else
	{
		StructTypeTableEntry* STE;
		for(STE = table->head; STE->tail != NULL; STE = STE->tail);
		STE->tail = item;
		item->tail = NULL;
	}
}


Type* GetStructTypeFromTypeTable(char* structname, StructTypeTableHead* table)
{
	StructTypeTableEntry* STE;
	for(STE = table->head; STE != NULL; STE = STE->tail)
	{
		if(strcmp(structname, STE->TP->structure.structname)==0)
		{
			return STE->TP;			
		}
	}
	return NULL;
}

#endif