


#include "symtable.h"



/*          -------
** Rozptylovací funkce - jejím úkolem je zpracovat zadaný klíč a přidělit
** mu index v rozmezí 0..HTSize-1.  V ideálním případě by mělo dojít
** k rovnoměrnému rozptýlení těchto klíčů po celé tabulce.  V rámci
** pokusů se můžete zamyslet nad kvalitou této funkce.  (Funkce nebyla
** volena s ohledem na maximální kvalitu výsledku). }
*/

int hashCode ( char* key ) {
	int retval = 1;
	int keylen = strlen(key);
	for ( int i=0; i<keylen; i++ )
		retval += key[i];
	return ( retval % HTSIZE );
}

/*
** Inicializace tabulky s explicitně zřetězenými synonymy.  Tato procedura
** se volá pouze před prvním použitím tabulky.
*/

bool htInit ( tHTable* ptrht ) {
	if(ptrht==NULL)	return false;	//oevereni platnosti ukazatele
	int i=0;
	while(i<HTSIZE)	//projde vsechny polozky pole		{
	{
		(*ptrht)[i]=NULL;	//potreba ukotvit vsechny vytvorene pointery
		i++;
	}
    
    return true;
}

/* TRP s explicitně zřetězenými synonymy.
** Vyhledání prvku v TRP ptrht podle zadaného klíče key.  Pokud je
** daný prvek nalezen, vrací se ukazatel na daný prvek. Pokud prvek nalezen není,
** vrací se hodnota NULL.
**
*/

tHTItem* htSearch ( tHTable* ptrht, char* key ) {
	if(ptrht==NULL)	return NULL;	//oevereni platnosti ukazatele
	int index;
	index=hashCode(key);	//nelezeni indexu pole
	tHTItem *tmp;
	tmp=(*ptrht)[index];	//pomocny prvek
	while(tmp!=NULL)
	{
		if(strcmp(key,tmp->key)==0)	//nalezne, prvek se vraci
		{
			return tmp;
		}
		else
		{
			tmp=tmp->ptrnext;	//nenalezne, posun na dalsi prvek
		}
	}
	return NULL;	//nenasel
}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vkládá do tabulky ptrht položku s klíčem key a s daty
** data.  Protože jde o vyhledávací tabulku, nemůže být prvek se stejným
** klíčem uložen v tabulce více než jedenkrát.  Pokud se vkládá prvek,
** jehož klíč se již v tabulce nachází, aktualizujte jeho datovou část.
**
** Využijte dříve vytvořenou funkci htSearch.  Při vkládání nového
** prvku do seznamu synonym použijte co nejefektivnější způsob,
** tedy proveďte.vložení prvku na začátek seznamu.
**/

/* TODO problem s prepsanim jiz existujici polozky v seznamu*/

bool htInsert ( tHTable* ptrht, char* key, tData data ) {
	if(ptrht==NULL)	return false;	//oevereni platnosti ukazatele
	tHTItem *tmp;
	tmp=htSearch(ptrht,key);
	if(tmp!=NULL)	//prvek jiz existuje, aktualizace zaznamu
	{
		free(tmp->key);	//NEFUNGUJE TADY SE NIKDY NEMA DOSTAT
		tmp->data=data;	//AKTUALIYUJE ALE NECHA PO SOBE PAMET
	}
	else
	{
		int index;
		index=hashCode(key);	//nelezeni indexu pole

		tmp=(tHTItem*) malloc(sizeof(tHTItem));
		if(tmp==NULL)	return false;	//chyba alokace
		tmp->ptrnext=(*ptrht)[index];	//posun dozadu
		tmp->key=key;	//prekopirovani klice a dat
		tmp->data=data;
		tmp->lcht=NULL;
		(*ptrht)[index]=tmp;	//nasataveni noveho prvku
	}
	return true;
}


/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/



/*Funkce pro Lin seznam pro pramametrz funkci*/

bool Searchparametr(tHTItem* ptrht,char* nazev)
{
	parametry *tmp;
	tmp=ptrht->data.first;
	while(tmp!=NULL)
	{
		if(tmp->nazev==nazev)
		{
			return true;
		}
		else
		{
			tmp=tmp->next;
		}
	}
	return false;
}

bool InsertParametr(tHTItem* ptrht,int typ,char* nazev)
{
	parametry * tmp;
	tmp=(parametry*)malloc(sizeof(parametry));
	if(tmp==NULL)	return false;
	tmp->nazev=nazev;
	tmp->type=typ;
	if(ptrht->data.first==NULL)
	{
		tmp->poradi=0;
		ptrht->data.pocet_par=1;
		ptrht->data.first=tmp;
	}
	else
	{
		parametry* help=ptrht->data.first;
		int poradi=1;
		while(help->next!=NULL)
		{
			poradi++;
			help=help->next;
		}
			tmp->poradi=poradi;
			help->next=tmp;
			ptrht->data.pocet_par++;
	}
	return true;
}


void Uvolnitparametry(tHTItem* ptrht)
{
	parametry* tmp;
	while (ptrht->data.first != NULL){	//projde cely seznam a od zacatku ho zacne odalokovávat
	tmp = ptrht->data.first;
	ptrht->data.first = ptrht->data.first->next;	//posun o jeden prvek niz v seznamu
	free(tmp->nazev);
	free(tmp);
	}
}

/*InterFace TS*/

int INSERT_DIM(int type,char* nazov_dim,tHTable* tabulka)
{
	char * pamet;
	pamet=(char*)malloc(sizeof(char)*(strlen(nazov_dim)+1));
	if(pamet==NULL)	return ALLOC_ERROR;
	for (unsigned int i=0;i<=(strlen(nazov_dim));i++)
	{
		pamet[i]=tolower(nazov_dim[i]);
	}
	pamet[strlen(nazov_dim)]='\0';

	tData dato;
	dato.first=NULL;
	dato.funkce=false;
	dato.navesti=NULL;
	dato.pocet_par=0;
	dato.type=type;
	dato.definovana=false;
	if(htInsert (tabulka,pamet,dato)==false)
	{

		return ALLOC_ERROR;
	}

	return OK;
}

int INSERT_F(char* nazov_f,tHTable* tabulka)
{
	char * pamet;
	pamet=(char*)malloc(sizeof(char)*(strlen(nazov_f)+1));
	if(pamet==NULL)	return ALLOC_ERROR;
	for (unsigned int i=0;i<=(strlen(nazov_f));i++)
	{
		pamet[i]=tolower(nazov_f[i]);
	}
	pamet[strlen(nazov_f)]='\0';

	tData dato;
	dato.first=NULL;
	dato.funkce=true;
	dato.navesti=pamet;
	dato.pocet_par=0;
	dato.type=-1;
	dato.definovana=false;
	if(htInsert (tabulka,pamet,dato)==false)	return ALLOC_ERROR;


	tHTItem* tmp;
	tmp=htSearch(tabulka,pamet);
	if(tmp==NULL)	return ALLOC_ERROR;
	tmp->lcht = (tHTable*) malloc ( sizeof(tHTable) );
	if(tmp->lcht==NULL)	return ALLOC_ERROR;
	htInit(tmp->lcht);


	return OK;
}

int INSERT_F_TYPE(int type,char* nazov_f,tHTable* tabulka)
{
	char * pamet;
	pamet=(char*)malloc(sizeof(char)*(strlen(nazov_f)+1));
	if(pamet==NULL)	return ALLOC_ERROR;
	for (unsigned int i=0;i<=(strlen(nazov_f));i++)
	{
		pamet[i]=tolower(nazov_f[i]);
	}
	pamet[strlen(nazov_f)]='\0';

	tHTItem *tmp;
	tmp=htSearch(tabulka,pamet);
	free(pamet);
	if(tmp==NULL)
	{
		return UNEXIST;
	}
	else
	{
		tmp->data.type=type;
		return OK;
	}
}

int INSERT_PAR(int type,char* nazev_par, char* nazov_f,tHTable* tabulka)
{
	char * pamet;
	pamet=(char*)malloc(sizeof(char)*(strlen(nazov_f)+1));
	if(pamet==NULL)	return ALLOC_ERROR;
	for (unsigned int i=0;i<=(strlen(nazov_f));i++)
	{
		pamet[i]=tolower(nazov_f[i]);
	}
	pamet[strlen(nazov_f)]='\0';


	tHTItem* tmp;
	tmp=htSearch(tabulka,pamet);
	free(pamet);

	pamet=(char*)malloc(sizeof(char)*(strlen(nazev_par)+1));
	if(pamet==NULL)	return ALLOC_ERROR;
	for (unsigned int i=0;i<=(strlen(nazev_par));i++)
	{
		pamet[i]=tolower(nazev_par[i]);
	}
	pamet[strlen(nazev_par)]='\0';



	if(Searchparametr(tmp,pamet)==true)	return SEM_TYPE_ERROR;
	if(InsertParametr(tmp,type,pamet)==false)	return ALLOC_ERROR;
	INSERT_DIM(type,pamet,tmp->lcht);
	return OK;
}

bool DEFINED(char* nazov_f,tHTable* tabulka)
{
	char * pamet;
	pamet=(char*)malloc(sizeof(char)*(strlen(nazov_f)+1));
	if(pamet==NULL)	return ALLOC_ERROR;
	for (unsigned int i=0;i<=(strlen(nazov_f));i++)
	{
		pamet[i]=tolower(nazov_f[i]);
	}
	pamet[strlen(nazov_f)]='\0';

	tHTItem *tmp;
	tmp=htSearch(tabulka,pamet);
	free(pamet);
	if(tmp==NULL)
	{
		return false;
	}
	else
	{
		tmp->data.definovana=true;
		return true;
	}

}

tRetData* SEARCH(char* nazov,tHTable* tabulka)
{
	char * pamet;
	pamet=(char*)malloc(sizeof(char)*(strlen(nazov)+1));
	if(pamet==NULL)	return NULL;
	for (unsigned int i=0;i<=(strlen(nazov));i++)
	{
		pamet[i]=tolower(nazov[i]);
	}
	pamet[strlen(nazov)]='\0';

	tHTItem* tmp;
	tmp=htSearch(tabulka,pamet);
	free(pamet);
	if(tmp==NULL)	return NULL;


	tRetData* help;
	help=(tRetData*)malloc(sizeof(tRetData));
	if(help==NULL)
	{
		//printf("chyba malloc");
		return NULL;
	}
	help->funkce=tmp->data.funkce;
	help->definovana=tmp->data.definovana;
	help->navesti=tmp->data.navesti;
	help->type=tmp->data.type;
	help->pocet_parametru=tmp->data.pocet_par;
	help->LocalTS=tmp->lcht;
	int *pole_i;
	pole_i=(int*)calloc(help->pocet_parametru,sizeof(int));
	if(pole_i==NULL)		{
		//printf("chyba calloc");
		return NULL;
	}
	parametry *pomoc;
	pomoc=tmp->data.first;
	for (int i=0;i<help->pocet_parametru;i++)
	{
		pole_i[i]=pomoc->type;
		pomoc=pomoc->next;
	}
	help->typy=pole_i;

	char **pole_char;
	pole_char=(char**)calloc((help->pocet_parametru),sizeof(char*));

	if(pole_char==NULL)		{
		//printf("chyba calloc char SEARCH\n");
		return NULL;
	}
	pomoc=tmp->data.first;
	for (int i=0;i<help->pocet_parametru;i++)
	{
		pole_char[i]=pomoc->nazev;
		pomoc=pomoc->next;
	}
	help->nazvy=pole_char;
	return help;
}

void DELETE_SEARCH(tRetData* retdato)
{
	if(retdato!=NULL)
	{
	free(retdato->typy);
	retdato->typy=NULL;
	free(retdato->nazvy);
	retdato->nazvy=NULL;
	free(retdato);
	retdato=NULL;
	}

}

void DELETE_TS(tHTable* ptrht)
{

	if(ptrht==NULL)	return ;	//oevereni platnosti ukazatele
	int i=0;
	tHTItem *tmp,*prev;

	while(i<HTSIZE)	//projde vsechny polozky pole
	{
		prev=(*ptrht)[i];

		while(prev!=NULL)	//projde cely radek
		{
			DELETE_TS(prev->lcht);
			prev=prev->ptrnext;	//posun
		}
		i++;
	}

	i=0;
	while(i<HTSIZE)	//projde vsechny polozky pole
	{

		prev=(*ptrht)[i];	//smaze lin seznamy
		while(prev!=NULL)	//projde cely radek
		{
			Uvolnitparametry(prev);
			prev=prev->ptrnext;	//posun
		}

		prev=(*ptrht)[i];	//skok zpet na zacatek radku

		while(prev!=NULL)	//projde cely radek
		{


			tmp=prev;
			prev=prev->ptrnext;	//posun a mazani
			free(tmp->key);
			free(tmp);

		}
		(*ptrht)[i]=NULL;	//ukotveni
		i++;
	}

	free(ptrht);
	ptrht=NULL;
}

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
