
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

typedef struct par {
    int type;	//typ parametru
    char* nazev;	//omezeni puvodniho identifikatoru na 50 znaku
    int poradi;
    struct par * next;
} parametry;


/* obsah datove casti */
typedef struct tData{
int type;	//prom dat typ, fce navratovy dat typ
char* navesti;	//
bool funkce;
int pocet_par;
parametry *first;
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

/* obsah datove casti */
typedef struct tRetData{
	int type;	//typ parametru/return ENUM INT_NUM DOUBLE_NUM STR
	bool funkce;
	int pocet_parametru;
	char *navesti;	//prom NULL
	int *typy;		//ENUM pole parametru typu
	char **nazvy;	//NAZVY	polse parametru nazvu
}tRetData;


/* funkce nad tabulkou */

int hashCode ( char* key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, char* key );

void htInsert ( tHTable* ptrht, char* key, tData data );

tData* htRead ( tHTable* ptrht, char* key );

void htDelete ( tHTable* ptrht, char* key );

void htClearAll ( tHTable* ptrht );


/* funkce pro Linearni seznam parametru fukci*/

bool Searchparametr(tHTItem* ptrht,int typ,char* nazev,int poradi);

bool InsertParametr(tHTItem* ptrht,int typ,char* nazev);

void Uvolnitparametry(tHTItem* ptrht);

/*Funkce pomocne*/

void Vlozdata(tData *cil,int typ,char* navesti,bool definice);

/*InterFace TS*/

void INSERT_DIM(int type,char* nazov_dim,tHTable* tabulka);
void INSERT_F(int type, char* nazov_f,tHTable* tabulka);
bool INSERT_PAR(int type,char* nazev_par, char* nazov_f,tHTable* tabulka);
tRetData* SEARCH(char* nazov,tHTable* tabulka);

#endif
