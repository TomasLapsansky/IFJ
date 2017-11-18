
/*
Vytvoril David Dejmal xdejma00 2017
prepracvany projekt c016 z predmetu IAL
*/


#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HTSIZE 19	//velikost tabulky musi byt prvocislo pro funkcnost hashcode()

typedef enum
{
	inte=0,doub=1,stri=2
}dattyp;


typedef struct par {
    dattyp typ;	//typ parametru
    char nazev[50];	//omezeni puvodniho identifikatoru na 50 znaku
    int poradi;
    struct par * next;
} parametry;


typedef struct tlist //ADT seznam
{
	parametry *first;	//ukazatelnaprvní prvek seznamu
}Seznam_parametru;


/* obsah datove casti */
typedef struct tData{
dattyp navrat_typ;	//prom dat typ, fce navratovy dat typ
char navesti[50];	//prom \0
bool definice;
Seznam_parametru seznam;
}tData;



/*Datová položka TRP s explicitně řetězenými synonymy*/
 typedef struct tHTItem{
	char* key;				/* klíč = identifikator */
	tData data;				/* obsah */
	struct tHTItem* ptrnext;	/* ukazatel na další synonymum */
	void* lcht;	//ukazatel na vnocene tabulky
} tHTItem;

/* TRP s explicitně zřetězenými synonymy. */
typedef tHTItem* tHTable[HTSIZE];

/* funkce nad tabulkou */

int hashCode ( char* key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, char* key );

void htInsert ( tHTable* ptrht, char* key, tData data );

tData* htRead ( tHTable* ptrht, char* key );

void htDelete ( tHTable* ptrht, char* key );

void htClearAll ( tHTable* ptrht );


/* funkce pro Linearni seznam parametru fukci*/

bool Searchparametr(Seznam_parametru *seznam,dattyp typ,char* nazev,int poradi);

bool InsertParametr(Seznam_parametru* seznam,dattyp typ,char* nazev);

void Initseznam (Seznam_parametru* seznam);

void Uvolnitparametry(Seznam_parametru *seznam);

/*Funkce pomocne*/

void Vlozdata(tData *cil,dattyp typ,char* navesti,bool definice);


#endif
