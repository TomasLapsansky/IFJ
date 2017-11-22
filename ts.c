


#include "ts.h"



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

void htInit ( tHTable* ptrht ) {
	if(ptrht==NULL)	return;	//oevereni platnosti ukazatele
	int i=0;
	while(i<HTSIZE)	//projde vsechny polozky pole		{
	{
		(*ptrht)[i]=NULL;	//potreba ukotvit vsechny vytvorene pointery
		i++;
	}

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

void htInsert ( tHTable* ptrht, char* key, tData data ) {
	if(ptrht==NULL)	return ;	//oevereni platnosti ukazatele
	tHTItem *tmp;
	tmp=htSearch(ptrht,key);
	if(tmp!=NULL)	//prvek jiz existuje, aktualizace zaznamu
	{
		tmp->data=data;
	}
	else
	{
		int index;
		index=hashCode(key);	//nelezeni indexu pole

		tmp=(tHTItem*) malloc(sizeof(tHTItem));
		if(tmp==NULL)	return;	//chyba alokace
		tmp->ptrnext=(*ptrht)[index];	//posun dozadu
		tmp->key=key;	//prekopirovani klice a dat
		tmp->data=data;
		tmp->lcht=NULL;
		(*ptrht)[index]=tmp;	//nasataveni noveho prvku
	}

}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato funkce zjišťuje hodnotu datové části položky zadané klíčem.
** Pokud je položka nalezena, vrací funkce ukazatel na položku
** Pokud položka nalezena nebyla, vrací se funkční hodnota NULL
**
** Využijte dříve vytvořenou funkci HTSearch.
*/

tData* htRead ( tHTable* ptrht, char* key ) {
	if(ptrht==NULL)	return NULL;	//oevereni platnosti ukazatele
	tHTItem *tmp;
	tmp=htSearch(ptrht,key);
	if(tmp==NULL)	return NULL;	//polozka se nenasla
	else
	{
		return &tmp->data;
	}


}

/*
** TRP s explicitně zřetězenými synonymy.
** Tato procedura vyjme položku s klíčem key z tabulky
** ptrht.  Uvolněnou položku korektně zrušte.  Pokud položka s uvedeným
** klíčem neexistuje, dělejte, jako kdyby se nic nestalo (tj. nedělejte
** nic).
**
** V tomto případě NEVYUŽÍVEJTE dříve vytvořenou funkci HTSearch.
*/

void htDelete ( tHTable* ptrht, char* key ) {
	if(ptrht==NULL)	return ;	//oevereni platnosti ukazatele
	int index;
	index=hashCode(key);	//nelezeni indexu pole
	tHTItem *tmp,*prev=NULL;
	tmp=(*ptrht)[index];	//pomocny aktualni a predesly prvek
	while(tmp!=NULL)
	{
		if(strcmp(key,tmp->key)==0)	//nalezl
		{
			if(prev==NULL)	//je prvni, pouze posun druheho na prvni misto
			{
			(*ptrht)[index]=(*ptrht)[index]->ptrnext;
			free(tmp);
			tmp=NULL;
			}
			else	//nebyl prvni, mazany se preskoci
			{
			prev->ptrnext=tmp->ptrnext;
			free(tmp);
			tmp=NULL;
			}
		}
		else	//nenalezl, posun na dalsi prvek
		{
		prev=tmp;
		tmp=tmp->ptrnext;
		}
	}

}

/* TRP s explicitně zřetězenými synonymy.
** Tato procedura zruší všechny položky tabulky, korektně uvolní prostor,
** který tyto položky zabíraly, a uvede tabulku do počátečního stavu.
*/

void htClearAll ( tHTable* ptrht ) {
	if(ptrht==NULL)	return ;	//oevereni platnosti ukazatele
	int i=0;
	tHTItem *tmp,*prev;
	while(i<HTSIZE)	//projde vsechny polozky pole
	{
		prev=(*ptrht)[i];
		while(prev!=NULL)	//projde cely radek
		{
			tmp=prev;
			prev=prev->ptrnext;	//posun a mazani
			free(tmp);

		}
		(*ptrht)[i]=NULL;	//ukotveni
		i++;
	}

}

/*Funkce pro Lin seznam pro pramametrz funkci*/

bool Searchparametr(tHTItem* ptrht,int typ,char* nazev,int poradi)
{
	parametry *tmp;
	tmp=ptrht->data.first;
	while(tmp!=NULL)
	{
		if((tmp->poradi==poradi)&&(strcmp(tmp->nazev,nazev)==0)&&(tmp->type==typ))
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
	free(tmp);
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

/*InterFace TS*/

void INSERT_DIM(int type,char* nazov_dim,tHTable* tabulka)
{
	tData dato;
	dato.first=NULL;
	dato.funkce=false;
	dato.navesti=NULL;
	dato.pocet_par=0;
	dato.type=type;
	htInsert (tabulka,nazov_dim,dato);

}

void INSERT_F(int type, char* nazov_f,tHTable* tabulka)
{
	tData dato;
	dato.first=NULL;
	dato.funkce=true;
	dato.navesti=nazov_f;
	dato.pocet_par=0;
	dato.type=type;
	htInsert (tabulka,nazov_f,dato);
}

bool INSERT_PAR(int type,char* nazev_par, char* nazov_f,tHTable* tabulka)
{
	tHTItem* tmp;
	tmp=htSearch(tabulka,nazov_f);
	if(tmp==NULL)	return false;
	InsertParametr(tmp,type,nazev_par);
	if(tmp->lcht==NULL)
	{
		tmp->lcht = (tHTable*) malloc ( sizeof(tHTable) );
		if(tmp->lcht==NULL)	return false;
		htInit(tmp->lcht);
	}
	INSERT_DIM(type,nazev_par,tmp->lcht);
	return true;
}

tRetData* SEARCH(char* nazov,tHTable* tabulka)
{
	tRetData* help;
	help=(tRetData*)malloc(sizeof(tRetData));
	tHTItem* tmp;
	tmp=htSearch(tabulka,nazov);
	if(tmp==NULL)	return NULL;
	help->funkce=tmp->data.funkce;
	help->navesti=tmp->data.navesti;
	help->type=tmp->data.type;
	help->pocet_parametru=tmp->data.pocet_par;
	int *pole_i;
	pole_i=(int*)malloc(sizeof(int)*help->pocet_parametru);
	if(pole_i==NULL)	return NULL;
	parametry *pomoc;
	pomoc=tmp->data.first;
	for (int i=0;i<help->pocet_parametru;i++)
	{
		pole_i[i]=pomoc->type;
		pomoc=pomoc->next;
	}
	help->typy=pole_i;

	char **pole_char;
	pole_char=(char**)malloc(sizeof(char*)*help->pocet_parametru);
	if(*pole_char==NULL)	return NULL;
	pomoc=tmp->data.first;
	for (int i=0;i<help->pocet_parametru;i++)
	{
		pole_char[i]=pomoc->nazev;
		pomoc=pomoc->next;
	}
	help->nazvy=pole_char;
	return help;
}
