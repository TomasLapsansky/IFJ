

#include "ts.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define RUN_TEST1	//MAKRO pro prelozeni TEST1/TEST2

/* tiskne celou tabulku */
void htPrintTable( tHTable* ptrht ) {
	int maxlen = 0;
	int sumcnt = 0;

	printf ("------------HASH TABLE--------------\n");
	for ( int i=0; i<HTSIZE; i++ ) {
		printf ("%i:",i);
		int cnt = 0;
		tHTItem* ptr = (*ptrht)[i];
		while ( ptr != NULL ) {
			printf (" [%s,data:%d,%s,%d,pocet=%d,pointer=%p]",ptr->key,ptr->data.type,ptr->data.navesti,ptr->data.funkce,ptr->data.pocet_par,ptr->lcht);
				cnt++;
			ptr = ptr->ptrnext;
		}
		printf ("\n");

		if (cnt > maxlen)
			maxlen = cnt;
		sumcnt+=cnt;
	}

	printf ("------------------------------------\n");
	printf ("Items count %i   The longest list %i\n",sumcnt,maxlen);
	printf ("------------------------------------\n");
}

void testprintfparam(parametry *seznam)
{
	parametry *tmp;
	tmp=seznam;
	while(tmp!=NULL)
	{
		printf("[%d, %d %s]\n",tmp->poradi,tmp->type,tmp->nazev);
		tmp=tmp->next;
	}
}

/*Pomocne funkce*/

void Vlozdata(tData *cil,int typ,char* navesti,bool funkce)
{
	cil->funkce=funkce;
	cil->type=typ;
	cil->navesti=navesti; //pozor na delky
	cil->first=NULL;
	cil->pocet_par=0;
}






/* Hlavni funkce pro testovani */
int main( ) {


/********************* SCRIPT START ******************************************/
	printf ("Hash Table - testing script\n");
	printf ("---------------------------\n");
	printf ("\nLet's set HTSIZE to 19 ( must be prvocislo )\n");

#ifndef RUN_TEST2
	tHTable* ptrht;
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	htInit ( ptrht );

	printf("TEST 01 - INIT\n");

	htPrintTable(ptrht);

	printf("TEST 02 - INSERT_DIM 3X\n");
	if(INSERT_DIM(1,"promena A",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	if(INSERT_DIM(0,"proMena b",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
		if(INSERT_DIM(2,"promEna c",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	htPrintTable(ptrht);

		printf("TEST 02 - INSERT_F 3X\n");
	if(INSERT_F("funkce ahoj",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}

	if(INSERT_F("funkce zdraviM",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
		if(INSERT_F("funkce cauky",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	htPrintTable(ptrht);

		printf("TEST 03 - INSERT_parametr 3X + nastaveni navratoveho typu\n");

if(INSERT_PAR(0,"paraAAAetr a","funkce ahoj",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	if(INSERT_PAR(3,"parametR b","funkce ahoj",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	if(INSERT_PAR(2,"parametr c","funkce ahoj",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}

		if(INSERT_F_TYPE(2,"funkce ahoj",ptrht)!=true)
	{
		printf("\nInsert typ neni ok\n");
		return 1;
	}
		htPrintTable(ptrht);

		printf("\nVYPIS PARAMETRU funkce ahoj\n\n");

		tHTItem *itemptr;
		itemptr=htSearch (ptrht,"funkce ahoj");
		testprintfparam(itemptr->data.first);

		printf("TEST 04 - SEARCH,DELETE_SEARCH\n");

		tRetData *help;
		help=SEARCH("asSDdg",ptrht);
		if(help==NULL)
		{
			printf("Nenasel jsem neco co tam neni - OK\n");
		}
		DELETE_SEARCH(help);

		help=SEARCH("funkce AHOJ",ptrht);
		if(help==NULL)
		{
			printf("Nenasel jsem neco co tam je - FAIL\n");
			return 1;
		}
		printf("\nPODROBNY VYPIS FUNKCE AHOJ");

		printf("vypis:\nnavesti:%s\nje to funkce:%d\npocet param:%d\nnavrat typ:%d\n",help->navesti,help->funkce,help->pocet_parametru,help->type);
		printf("local TS pointer:%p\n", (void *)help->LocalTS);

		for (int i=0;i<help->pocet_parametru;i++)
		{
			printf("typ:%d\n",help->typy[i]);

		}
		for (int i=0;i<help->pocet_parametru;i++)
		{
			printf("nazvy:%s\n",help->nazvy[i]);

		}

	DELETE_SEARCH(help);

	printf("TEST 05 - INSERT do local TS funkce ahoj\n");


	tHTable *pomocptr;
	help=SEARCH("funkce ahoj",ptrht);
	pomocptr=help->LocalTS;
	DELETE_SEARCH(help);

		if(INSERT_DIM(2,"promENA aBC",pomocptr)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
			if(INSERT_DIM(2,"promena Abc",pomocptr)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
			if(INSERT_DIM(0,"promena ABC",pomocptr)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	htPrintTable(pomocptr);

	printf("\n3x INSERT case sensitiv => 1xINSERT promena abc\n");

	DELETE_TS(ptrht);


#endif // RUN_TEST2

#ifndef RUN_TEST1

	tHTable* ptrht;
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	tHTItem* itemptrr;

	htInit ( ptrht );
	htPrintTable(ptrht);

	tData dato;
	Vlozdata(&dato,0,"navesti",true);


	printf ("\n[TEST01] init = prazdno\n");
	htInit ( ptrht );
	htPrintTable(ptrht);

	printf ("\n[TEST02] 1x htInsert()\n");
	htInsert( ptrht, "krusovice", dato );
	htPrintTable(ptrht);

	printf ("\n[TEST03] hledam neco co tam je\n");
		itemptrr=htSearch (ptrht,"krusovice");
		if(itemptrr!=NULL)	printf("nasel jsem\n");
		else 	printf("nenasel jsem\n");

	printf ("\n[TEST04] 8x htInsert()\n");
	Vlozdata(&dato,1,"a",true);
	htInsert ( ptrht, "korgon", dato );
	Vlozdata(&dato,0,"b",true);
	htInsert ( ptrht, "zlaty bazant",dato);
	Vlozdata(&dato,2,"c",true);
	htInsert ( ptrht, "gambrinus", dato);
	Vlozdata(&dato,0,"nav",true);
	htInsert ( ptrht, "starobrno", dato);
	htInsert ( ptrht, "plzen", dato);
	Vlozdata(&dato,0,"nafi",true);
	htInsert ( ptrht, "velvet", dato);
	Vlozdata(&dato,0,"ngggg",false);
	htInsert ( ptrht, "kelt", dato);
	Vlozdata(&dato,1,"navessssssi",false);
	htInsert ( ptrht, "kofola", dato);

		htPrintTable(ptrht);



	printf ("\n[TEST05] tabulka v tabulce \n");

	itemptrr=htSearch (ptrht,"krusovice");
	itemptrr->lcht = (tHTable*) malloc ( sizeof(tHTable) );
	htPrintTable(ptrht);

	printf ("\n[TEST06] init = prazdno v seznam v seznamu (s2)\n");
	htInit ( itemptrr->lcht );
	htPrintTable(itemptrr->lcht);

	printf ("\n[TEST07] 8x htInsert() s2\n");
	Vlozdata(&dato,1,"a",true);
	htInsert ( itemptrr->lcht, "korgon s2", dato );
	Vlozdata(&dato,0,"b",true);
	htInsert ( itemptrr->lcht, "zlaty bazant s2",dato);
	Vlozdata(&dato,2,"c",true);
	htInsert ( itemptrr->lcht, "gambrinus s2", dato);
	Vlozdata(&dato,0,"nav s2",true);
	htInsert ( itemptrr->lcht, "starobrno s2", dato);
	htInsert ( itemptrr->lcht, "plzen s2", dato);
	Vlozdata(&dato,0,"nafi",true);
	htInsert (itemptrr->lcht, "velvet s2", dato);
	Vlozdata(&dato,0,"ngggg s2",false);
	htInsert (itemptrr->lcht, "kelt s2", dato);
	Vlozdata(&dato,1,"navessssssi s2",false);
	htInsert ( itemptrr->lcht, "kofola s2", dato);

	htPrintTable(itemptrr->lcht);


	printf("\n[TEST08] vytvoreni ln seznamu parametru fuknci v s2 kofola\n");
	tHTItem* itemptrr2;
	itemptrr2=htSearch(itemptrr->lcht,"kelt s2");
	if(itemptrr2==NULL)
	{
		printf("\nnenasel");
		return 0;
	}

	if(InsertParametr(itemptrr2,0,"parametr")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}
	testprintfparam(itemptrr2->data.first);
	htPrintTable(itemptrr->lcht);

	printf("\n[TEST09] inseret 4x ln seznamu parametru fuknci v s2 kofola\n");

	if(InsertParametr(itemptrr2,2,"pole")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}

	if(InsertParametr(itemptrr2,1,"struct")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}
	if(InsertParametr(itemptrr2,0,"arra")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}
	if(InsertParametr(itemptrr2,1,"help")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}

	testprintfparam(itemptrr2->data.first);

	htPrintTable(itemptrr->lcht);
	printf("\n[TEST10] delete TS\n");

	printf("jdu na delete");

	DELETE_TS(ptrht);


#endif // RUN_TEST1

}
