


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

bool Searchparametr(Seznam_parametru *seznam,dattyp typ,char* nazev,int poradi)
{
	parametry *tmp;
	tmp=seznam->first;
	while(tmp!=NULL)
	{
		if((tmp->poradi==poradi)&&(strcmp(tmp->nazev,nazev)==0)&&(tmp->typ==typ))
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

bool InsertParametr(Seznam_parametru* seznam,dattyp typ,char* nazev)
{
	parametry * tmp;
	tmp=(parametry*)malloc(sizeof(parametry));
	if(tmp==NULL)	return false;
	strcpy(tmp->nazev,nazev);
	tmp->typ=typ;
	if(seznam->first==NULL)
	{
		tmp->poradi=0;
		seznam->first=tmp;
	}
	else
	{
		parametry* help=seznam->first;
		int poradi=1;
		while(help->next!=NULL)
		{
			poradi++;
			help=help->next;
		}
			tmp->poradi=poradi;
			help->next=tmp;
	}
	return true;
}

void Initseznam (Seznam_parametru* seznam)
{
	seznam->first=NULL;
}

void Uvolnitparametry(Seznam_parametru *seznam)
{
	parametry* tmp;
	while (seznam->first != NULL){	//projde cely seznam a od zacatku ho zacne odalokovávat
	tmp = seznam->first;
	seznam->first = seznam->first->next;	//posun o jeden prvek niz v seznamu
	free(tmp);
	}
}


/*Pomocne funkce*/

void Vlozdata(tData *cil,dattyp typ,char* navesti,bool definice)
{
	cil->definice=definice;
	cil->navrat_typ=typ;
	strcpy(cil->navesti,navesti); //pozor na delky
	Initseznam(&cil->seznam);
}
