
/*
Vytvoril David Dejmal xdejma00 2017
prepracvany projekt c016 z predmetu IAL
*/


#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include "structs.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/*
velikost tabulky musi byt prvocislo pro funkcnost hashcode()
male bude tvorit dlouhe seznamy = dlouhy pristup k prvku
velke bude alokovat prazdne bloky = zbytecne zabirana pamet
NUTNO OPTIMALIZOVAT
*/
#define HTSIZE 19

/*
struktura popisujici jeden parametr v linearnim seznamu
*/
typedef struct par {
    int type;	//typ parametru
    char* nazev;	//ukazatel na id
		int poradi;		//poradi parametru
    struct par * next;	//dalsi parametr
} parametry;


/*
obsah datove casti tHTItem
data v jednotlive polozce hash table

*/
typedef struct tData{
int type;	//prom dat typ, fce navratovy dat typ
char* navesti;	//pomocny retezec pro tvoru 3ad kodu, je stejne jako key
bool funkce;	//pokud je to funkce=true
int pocet_par;
parametry *first;	//hlavicka lin seznamu parametru
}tData;



/*
Datová položka TRP s explicitně řetězenými synonymy
polozka v hash table
*/
 typedef struct tHTItem{
	char* key;				/* klíč = id*/
	tData data;				/* obsah */
	struct tHTItem* ptrnext;	/* ukazatel na další synonymum */
	void* lcht;		//ukazatel na vnocene tabulky
} tHTItem;

/*
TRP s explicitně zretezenymi synonymy.
hash tabulka
*/
typedef tHTItem* tHTable[HTSIZE];

/*
struktura pro vystupni komunikaci (interface)
*/
typedef struct tRetData{
	int type;									//typ parametru
	bool funkce;							//pokud je to funkce=true prom=false
	int pocet_parametru;
	char *navesti;						//fce=id  prom=NULL	slouzi pro generator
	int *typy;								//pole typu paramtru
	char **nazvy;							//pole id paramatru
	tHTable *LocalTS;
}tRetData;

/*InterFace TS*/

/*
do tabulky vlozi promenou daneho typu a id
POZOR pokud v dane tabulce uz existuje neco se stejnym nazvem prepisuje!!!
pred pouzitim volej SEARCH() !!!
ALLOC_ERROR / OK
*/
enum Errors INSERT_DIM(int type,char* nazov_dim,tHTable* tabulka);

/*
stejne jako INSERT_DIM
do tabulky vlozi funkci podle id
vklada navratovy typ -1 !
POZOR pokud v dane tabulce uz existuje neco se stejnym nazvem prepisuje!!!
pred pouzitim volej SEARCH() !!!
ALLOC_ERROR / OK
*/
enum Errors INSERT_F(char* nazov_f,tHTable* tabulka);

/*
nastavi navratovy typ funkce
*/
bool INSERT_F_TYPE(int type,char* nazov_f,tHTable* tabulka);

/*
v tabulce najde funkci do ni prida parametr a vlozi ho taky do jeji localni tabulky symbolu
true -> vse se povedlo
flase -> funkce neni v TS,chyba alokace
ALLOC_ERROR / OK / SEM_TYPE_ERROR pokud se pokusite zadat podruhe stejny parametr
*/
enum Errors INSERT_PAR(int type,char* nazev_par, char* nazov_f,tHTable* tabulka);

/*
hleda polozku v tabulce a vraci tretdata
NULL pri nenalezeni i chybe malloc
POZOR nutno odlaokovat!!!
po každém zavolani nutvo volat DELETE_SEARCH
*/
tRetData* SEARCH(char* nazov,tHTable* tabulka);

/*
korekne uvolni data cele struktury
*/
void DELETE_SEARCH(tRetData* retdato);

/*
korekne uvolni celou tabulku symbolu
*/
void DELETE_TS(tHTable* global_tabulka);

/* funkce nad tabulkou */

int hashCode ( char* key );

void htInit ( tHTable* ptrht );

tHTItem* htSearch ( tHTable* ptrht, char* key );

bool htInsert ( tHTable* ptrht, char* key, tData data );


/* funkce pro Linearni seznam parametru fukci*/

bool Searchparametr(tHTItem* ptrht,char* nazev);

bool InsertParametr(tHTItem* ptrht,int typ,char* nazev);

void Uvolnitparametry(tHTItem* ptrht);

char* low(char *sring);


#endif
