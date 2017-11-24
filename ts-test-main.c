

#include "ts.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>



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


	tHTable* ptrht;
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	htInit ( ptrht );

	printf("TEST 01 - INIT\n");

	htPrintTable(ptrht);

	printf("TEST 02 - INSERT_DIM 3X\n");
	if(INSERT_DIM(1,"promena a",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	if(INSERT_DIM(0,"promena b",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
		if(INSERT_DIM(2,"promena c",ptrht)!=OK)
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

	if(INSERT_F("funkce blb",ptrht)!=OK)
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

		printf("TEST 03 - INSERT_parametr 3X + nastaveni navratovych typu\n");

if(INSERT_PAR(0,"parametr a","funkce ahoj",ptrht)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	if(INSERT_PAR(3,"parametr b","funkce ahoj",ptrht)!=OK)
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

		tHTItem *itemptr;
		itemptr=htSearch (ptrht,"funkce ahoj");
		testprintfparam(itemptr->data.first);

		printf("TEST 04 - SEARCH,DELETE_SEARCH\n");

		tRetData *help;
		help=SEARCH("asddg",ptrht);
		if(help==NULL)
		{
			printf("Nedansel jsem neco co tam neni");
		}
		DELETE_SEARCH(help);

		help=SEARCH("funkce ahoj",ptrht);
		if(help==NULL)
		{
			printf("Nedansel jsem neco co tam je\n");
			return 1;
		}
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

	printf("TEST 05 - INSERT do LC TS\n");


	tHTable *pomocptr;
	help=SEARCH("funkce ahoj",ptrht);
	pomocptr=help->LocalTS;
	DELETE_SEARCH(help);

		if(INSERT_DIM(2,"promena abc",pomocptr)!=OK)
	{
		printf("\nInsert neni ok\n");
		return 1;
	}
	htPrintTable(pomocptr);


	DELETE_TS(ptrht);



/*
	tHTable* ptrht;
	ptrht = (tHTable*) malloc ( sizeof(tHTable) );
	tHTItem* itemptr;

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
		itemptr=htSearch (ptrht,"krusovice");
		if(itemptr!=NULL)	printf("nasel jsem\n");
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

	itemptr=htSearch (ptrht,"krusovice");
	itemptr->lcht = (tHTable*) malloc ( sizeof(tHTable) );
	htPrintTable(ptrht);

	printf ("\n[TEST06] init = prazdno v seznam v seznamu (s2)\n");
	htInit ( itemptr->lcht );
	htPrintTable(itemptr->lcht);

	printf ("\n[TEST07] 8x htInsert() s2\n");
	Vlozdata(&dato,1,"a",true);
	htInsert ( itemptr->lcht, "korgon s2", dato );
	Vlozdata(&dato,0,"b",true);
	htInsert ( itemptr->lcht, "zlaty bazant s2",dato);
	Vlozdata(&dato,2,"c",true);
	htInsert ( itemptr->lcht, "gambrinus s2", dato);
	Vlozdata(&dato,0,"nav s2",true);
	htInsert ( itemptr->lcht, "starobrno s2", dato);
	htInsert ( itemptr->lcht, "plzen s2", dato);
	Vlozdata(&dato,0,"nafi",true);
	htInsert (itemptr->lcht, "velvet s2", dato);
	Vlozdata(&dato,0,"ngggg s2",false);
	htInsert (itemptr->lcht, "kelt s2", dato);
	Vlozdata(&dato,1,"navessssssi s2",false);
	htInsert ( itemptr->lcht, "kofola s2", dato);

	htPrintTable(itemptr->lcht);


	printf("\n[TEST08] vytvoreni ln seznamu parametru fuknci v s2 kofola\n");
	tHTItem* itemptr2;
	itemptr2=htSearch(itemptr->lcht,"kelt s2");
	if(itemptr2==NULL)
	{
		printf("\nnenasel");
		return 0;
	}

	if(InsertParametr(itemptr2,0,"parametr")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}
	testprintfparam(itemptr2->data.first);
	htPrintTable(itemptr->lcht);

	printf("\n[TEST09] inseret 4x ln seznamu parametru fuknci v s2 kofola\n");

	if(InsertParametr(itemptr2,2,"pole")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}

	if(InsertParametr(itemptr2,1,"struct")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}
	if(InsertParametr(itemptr2,0,"arra")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}
	if(InsertParametr(itemptr2,1,"help")==false)
	{
		printf("chyba alokcae\n");
		return 0;
	}

	testprintfparam(itemptr2->data.first);

	htPrintTable(itemptr->lcht);
	printf("\n[TEST10] delete TS\n");

	printf("jdu na delete");

	DELETE_TS(ptrht);


*/

/*
	printf("-----------------------------------------------------------------");

	printf("TEST A InseretDim\n");

	tHTable* helping;
	helping = (tHTable*) malloc ( sizeof(tHTable) );
	htInit ( helping );

	INSERT_DIM(1,"promena",helping);
	htPrintTable(helping);

	printf("TEST B InseretFunce\n");

	INSERT_F(2,"funkce",helping);
	htPrintTable(helping);

	printf("TEST C InseretParametry\n");
	printf("jdu vkladat");

	if(INSERT_PAR(0,"paramert1","funkce",helping)!=OK)	printf("problem");


	if(INSERT_PAR(2,"paramert2","funkce",helping)!=OK)	printf("problem");


	if(INSERT_PAR(1,"paramert3","funkce",helping)!=OK)	printf("problem");


	htPrintTable(helping);
	tHTItem* itemptr3;
	itemptr3=htSearch (helping,"funkce");
	testprintfparam(itemptr3->data.first);

	printf("TEST D search\n");
	tRetData *helpdata;
	helpdata=SEARCH("funkce",helping);
	if(helpdata==NULL)	return 1;
	printf("vypis:\nnavesti:%s\nje to funkce:%d\npocet param:%d\nnavrat typ:%d\n",helpdata->navesti,helpdata->funkce,helpdata->pocet_parametru,helpdata->type);
	for (int i=0;i<helpdata->pocet_parametru;i++)
	{
		printf("typ:%d\n",helpdata->typy[i]);

	}
	for (int i=0;i<helpdata->pocet_parametru;i++)
	{
		printf("nazvy:%s\n",helpdata->nazvy[i]);

	}
	DELETE_SEARCH(helpdata);
	printf("TEST D vlozit 2x stejny parametr\n");
	if(INSERT_PAR(1,"paramert3","funkce",helping)==4)	printf("vracen SEM_TYPE_ERROR\ntest ok\n");


	DELETE_TS(helping);
	return 0;

	*/
}
