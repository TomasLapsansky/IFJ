/**
 * @Name IFJ17 Syntakticka a sematicka analyza
 * @author Tomas Lapsansky (xlapsa00)
 * @file parser.c
 * @date 15.11.2017
 */

#include "parser.h"
#include <string.h>

extern TOKEN token;
extern int error;			//error code
extern int line;			//line number
extern tHTable* ptrht;		//HASH table
extern tHTable* global_ptrht;   //odkaz na globalnu TS - pouziva sa pri volani funkcii
extern tStack *s;

bool loaded_token = false;

//spracovanie ID		TODO
int id(tRetData **ins_id, TOKEN *ins_token, tHTable* use_ptrht) {
	
    if((ins_token->name == LENGTH) || (ins_token->name == SUBSTR) || (ins_token->name == ASC) || (ins_token->name == CHR)) {    //prednostna podmienka pre vstavane funkcie
        *ins_id = SEARCH(ins_token->data, use_ptrht);   //pri vstavanych funkciach nie je potrebne overovat ich pritomnost
        return F_ID;
    } else if(ins_token->name == ID) {
		*ins_id = SEARCH(ins_token->data, use_ptrht);
		
		if((*ins_id) == NULL) {
			return UNEXIST;
		} else {
		
			if((*ins_id)->funkce)
				return F_ID;
			else
				return DIM_ID;
		}
	} else if(ins_token->name == INVALIDCHAR) {
		return UNEXIST;
	} else
		return NON_ID;
}

//main
int parser(void) {
    
    //Vkladania vstavanych funkcii pre syntakticku a sematicku analyzu
    
    char *nazov_f = (char*)malloc(sizeof(char) * 50);
    char *par = (char*)malloc(sizeof(char) * 50);
    
    //Length(s As String) As Integer
    strcpy(nazov_f, "Length");
    INSERT_F(nazov_f, ptrht);
    INSERT_F_TYPE(INTEGER, nazov_f, ptrht);
    
    strcpy(par, "s");
    INSERT_PAR(STRING, par, nazov_f, ptrht);
    
    //SubStr(s As String, i As Integer, n As Integer) As String
    strcpy(nazov_f, "SubStr");
    INSERT_F(nazov_f, ptrht);
    INSERT_F_TYPE(STRING, nazov_f, ptrht);
    
    strcpy(par, "s");
    INSERT_PAR(STRING, par, nazov_f, ptrht);
    
    strcpy(par, "i");
    INSERT_PAR(INTEGER, par, nazov_f, ptrht);
    
    strcpy(par, "n");
    INSERT_PAR(INTEGER, par, nazov_f, ptrht);
    
    //Asc(s As String, i As Integer) As Integer
    strcpy(nazov_f, "Asc");
    INSERT_F(nazov_f, ptrht);
    INSERT_F_TYPE(INTEGER, nazov_f, ptrht);
    
    strcpy(par, "s");
    INSERT_PAR(STRING, par, nazov_f, ptrht);
    
    strcpy(par, "i");
    INSERT_PAR(INTEGER, par, nazov_f, ptrht);
    
    //Chr(i As Integer) As String
    strcpy(nazov_f, "Chr");
    INSERT_F(nazov_f, ptrht);
    INSERT_F_TYPE(STRING, nazov_f, ptrht);
    
    strcpy(par, "i");
    INSERT_PAR(INTEGER, par, nazov_f, ptrht);
    
    free(nazov_f);
    free(par);
    
	line = 1;
	return p_start();
}

//<p_start>		<p_declare> <p_scope>
int p_start(void) {
	
	if((error = Get_Token(&token)) != OK) {
		return error;
	}
	
	if((error = p_declare()) != OK)
		return error;
	
	if((error = p_scope()) != OK)
		return error;
	
	return OK;
}//p_start

//<p_declare>		ε
//<p_declare>		Declare Function ID (<p_parameter> As <p_type> "EOL" <p_declare>
//<p_declare>		Function ID (<p_parameter> As <p_type> "EOL" <p_body> <p_declare>
int p_declare(void) {
	
	tRetData *idData = NULL;//pre korektnost prekladu
	TOKEN idToken;
	
	switch(token.name) {
			
		case(DECLARE):						//Declare
			
			if((error = Get_Token(&token)) != OK)
				return error;//gettoken
			
			if(token.name != FUNCTION)		//Declare Function
				return SYN_A_ERROR;
			
			Init_Token(&idToken);
			if((error = Get_Token(&idToken)) != OK)
				return error;//gettoken
			
			//tRetData *idData = NULL;
			if((error = id(&idData, &idToken, ptrht)) != UNEXIST) {	//Declare Function ID
				int ret;
				
				if(error == NON_ID)
					ret = SYN_A_ERROR;
				else //if(ret == DIM_ID || ret == F_ID)
					ret = SEM_ERROR;
				
				Clear_Token(&idToken);
				DELETE_SEARCH(idData);
				return ret;
			}
			DELETE_SEARCH(idData);
			
			INSERT_F(idToken.data, ptrht);
			
			if((error = Get_Token(&token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if(token.name != LEFTPAREN) {	//Declare Function ID(
				Clear_Token(&idToken);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(&token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if((error = p_declare_parameter(idToken.data)) != OK) {		//Declare Function ID(<p_declare_parameter>)
				Clear_Token(&idToken);
				return error;
			}
			
			if((error = Get_Token(&token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if(token.name != AS) {			//Declare Function ID(<p_declare_parameter>) As
				Clear_Token(&idToken);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(&token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if((error = p_type()) != OK) {	//Declare Function ID(<p_declare_parameter>) As <p_type>
				Clear_Token(&idToken);
				return error;
			}
			
			INSERT_F_TYPE(token.name, idToken.data, ptrht);
			
			Clear_Token(&idToken);
			
			if((error = Get_Token(&token)) != OK)
				return error;//gettoken
			
			if(token.name != EOL_)			//Declare Function ID(<p_declare_parameter>) As <p_type> EOL
				return SYN_A_ERROR;
			
			if((error = Get_Token(&token)) != OK)
				return error;//gettoken
			
			return p_declare();				//prechod do potencialneho dalsieho stavu
			
			break;
			
		case(FUNCTION):					//Function
			
			if((error = Get_Token(&token)) != OK)
				return error;//gettoken
			
			//tRetData *idData = NULL;
			if((error = id(&idData, &token, ptrht)) != F_ID) {	//Function ID
				int ret;
				
				if(error == NON_ID)
					ret = SYN_A_ERROR;
				else {//if(error == DIM_ID || error == UNEXIST)
					ret = SEM_ERROR;
				}
				
				DELETE_SEARCH(idData);
				return ret;
			}
			
			if((error = Get_Token(&token)) != OK) {
				DELETE_SEARCH(idData);
				return error;//gettoken
			}
			
			if(token.name != LEFTPAREN) {	//Function ID(
				DELETE_SEARCH(idData);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(&token)) != OK) {
				DELETE_SEARCH(idData);
				return error;//gettoken
			}
			
			int pocet_parametrov = 0;
			if((error = p_parameter(idData, &pocet_parametrov)) != OK) {		//Function ID(<p_parameter>)
				DELETE_SEARCH(idData);
				return error;
			}
			
			//Semanticka kontrola poctu parametrov vo funkcii
			if(idData->pocet_parametru != pocet_parametrov) {
				DELETE_SEARCH(idData);
				return SEM_TYPE_ERROR;
			}
			
			if((error = Get_Token(&token)) != OK) {
				DELETE_SEARCH(idData);
				return error;//gettoken
			}
			
			if(token.name != AS) {			//Function ID(<p_parameter>) As
				DELETE_SEARCH(idData);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(&token)) != OK) {
				DELETE_SEARCH(idData);
				return error;//gettoken
			}
			
			if((error = p_type()) != OK) {	//Function ID(<p_parameter>) As <p_type>
				DELETE_SEARCH(idData);
				return error;
			}
			
			//Semanticka kontrola navratoveho typu funkcie
			if(idData->type != token.name) {
				DELETE_SEARCH(idData);
				return SEM_ERROR;
			}
			
			if((error = Get_Token(&token)) != OK) {
				DELETE_SEARCH(idData);
				return error;//gettoken
			}
			
			if(token.name != EOL_) {		//Function ID(<p_parameter>) As <p_type> EOL
				DELETE_SEARCH(idData);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(&token)) != OK) {
				DELETE_SEARCH(idData);
				return error;//gettoken
			}
			
			//zmena ptrht na lokalnu TS kvoli vstupu do funkcie
			//implementovany zasobnik kvoli moznemu viacnasobnemu znoreniu
			stackPush(s, ptrht);
			ptrht = idData->LocalTS;
			
			if((error = p_body(idData->type)) != OK) {		//Function ID(<p_parameter>) As <p_type> EOL <p_body>
                DELETE_SEARCH(idData);
				return error;
			}
            DELETE_SEARCH(idData);
			
			//opatovne vratenie ptrht
			ptrht = stackPop(s);
			
			if(token.name != END)			//Function ID(<p_parameter>) As <p_type> EOL <p_body> End
				return SYN_A_ERROR;
			
			if((error = Get_Token(&token)) != OK)
				return error;//gettoken
			
			if(token.name != FUNCTION)		//Function ID(<p_parameter>) As <p_type> EOL <p_body> End Function
				return SYN_A_ERROR;
			
			if((error = Get_Token(&token)) != OK)
				return error;//gettoken
			
			if(token.name != EOL_)		//Function ID(<p_parameter>) As <p_type> EOL <p_body> End Function EOL
				return SYN_A_ERROR;
			
			if((error = Get_Token(&token)) != OK)
				return error;//gettoken
			
			return p_declare();				//prechod do potencialneho dalsieho stavu
			
			break;
			
		case(SCOPE):					//ε
			
			return OK;
			
		default:						//ERROR
			return SYN_A_ERROR;
	}//switch
	
}//p_declare

//<p_body>		ε
//<p_body>		<p_prikaz> EOL <p_body>
int p_body(int return_type) {
	
	if((error = p_prikaz(return_type)) == E_OK) {
		return OK;
	} else if(error != OK) {
		return error;
	}
	
	if(!loaded_token) {		//vola sa, ak prikaz nebol vyrazom, teda nie je nacitany novy token
		if((error = Get_Token(&token)) != OK)
			return error;	//gettoken
	}
	
	loaded_token = false;
	
	if(token.name != EOL_)
		return SYN_A_ERROR;
	
	//line++;	//pocitadlo riadku pre vypis pri chybe
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	return p_body(return_type);
	
}

//<p_type>		Integer
//<p_type>		Double
//<p_type>		String
int p_type(void) {
	switch(token.name) {
		case(INTEGER):
		case(DOUBLE):
		case(STRING):
        case(BOOLEAN_):
        case(INT_NUM):
        case(DOUBLE_NUM):
        case(STR):
        case(BL):
			return OK;
		default:
			return SYN_A_ERROR;
	}
}

//<p_scope>		Scope EOL <p_body> End Scope EOF
int p_scope(void) {
	if(token.name != SCOPE)	//Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if(token.name != EOL_)		//Scope <p_body> End
		return SYN_A_ERROR;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if((error = p_body(0)) != OK) {	//Scope <p_body>
		return error;
	}
	
	if(token.name != END)		//Scope <p_body> End
		return SYN_A_ERROR;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if(token.name != SCOPE)		//Scope <p_body> End Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if(token.name == EOL_) {	//Scope <p_body> End Scope EOL
		if((error = Get_Token(&token)) != OK)
			return error;	//gettoken
	}
	
	
	
	if(token.name != EOF_)		//Scope <p_body> End Scope EOL EOF
		return SYN_A_ERROR;
	
	return OK;
}

//<p_parameter>	ε)
//<p_parameter>	ID As <p_type>)
//<p_parameter>	ID As <p_type>, <p_nextparameter>
int p_parameter(tRetData *funcData, int *pocet_parametrov) {
	
	if(token.name == RIGHTPAREN) {	//ε)
		return OK;
	}
	
	stackPush(s, ptrht);
	ptrht = funcData->LocalTS;
	
	tRetData *idData = NULL;
	if((error = id(&idData, &token, ptrht)) != DIM_ID) {	//ID
		int ret;
		
		if(error == NON_ID)
			ret = SYN_A_ERROR;
		else //if(error == F_ID || error == UNEXIST)
			ret = SEM_TYPE_ERROR;
		
		DELETE_SEARCH(idData);
		return ret;
	}
	
	ptrht = stackPop(s);
	
	if(strcmp(funcData->nazvy[*pocet_parametrov], token.data) != 0) {
		DELETE_SEARCH(idData);
		return SEM_TYPE_ERROR;
	}
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if(token.name != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK))	//ID As <p_type>
		return error;
	
	if(funcData->typy[*pocet_parametrov] != token.name) {
		DELETE_SEARCH(idData);
		return SEM_TYPE_ERROR;
	}
	DELETE_SEARCH(idData);
	
	//inkrement poctu parametrov po korektnom prejdeni
	(*pocet_parametrov)++;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_nextparameter>
			
			if((error = Get_Token(&token)) != OK)
				return error;	//gettoken
			
			return p_nextparameter(funcData, pocet_parametrov);
		default:
			return SYN_A_ERROR;
	}
}

//<p_nextparameter>	ID As <p_type>)
//<p_nextparameter>	ID As <p_type>, <p_nextparameter>
int p_nextparameter(tRetData *funcData, int *pocet_parametrov) {
	
	tRetData *idData = NULL;
	if((error = id(&idData, &token, ptrht)) != DIM_ID) {	//ID
		int ret;
		
		if(error == NON_ID)
			ret = SYN_A_ERROR;
		else //if(error == F_ID || error == UNEXIST)
			ret = SEM_TYPE_ERROR;
		
		DELETE_SEARCH(idData);
		return ret;
	}
	
	if(strcmp(funcData->nazvy[*pocet_parametrov], token.data) != 0) {
		DELETE_SEARCH(idData);
		return SEM_TYPE_ERROR;
	}
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if(token.name != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK))	//ID As <p_type>
		return error;
	
	if(funcData->typy[*pocet_parametrov] != token.name) {
		DELETE_SEARCH(idData);
		return SEM_TYPE_ERROR;
	}
	DELETE_SEARCH(idData);
	
	//inkrement poctu parametrov po korektnom prejdeni
	(*pocet_parametrov)++;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_nextparameter>
			
			if((error = Get_Token(&token)) != OK)
				return error;	//gettoken
			
			return p_nextparameter(funcData, pocet_parametrov);
		default:
			return SYN_A_ERROR;
	}
}

//<p_declare_parameter>	ε)
//<p_declare_parameter>	ID As <p_type>)
//<p_declare_parameter>	ID As <p_type>, <p_declare_nextparameter>
int p_declare_parameter(char* funcName) {
	
	if(token.name == RIGHTPAREN) {	//ε)
		return OK;
	}
	
	tRetData *idData = NULL;
	if((error = id(&idData, &token, ptrht)) != UNEXIST) {	//ID
		int ret;
		
		if(error == NON_ID)
			ret = SYN_A_ERROR;
		else //if(error == DIM_ID || error == F_ID)
			ret = SEM_TYPE_ERROR;
		
		DELETE_SEARCH(idData);
		return ret;
	}
	DELETE_SEARCH(idData);
	
	char *id_string = (char*)malloc(sizeof(char) * strlen(token.data));
	strcpy(id_string, token.data);
	
	if((error = Get_Token(&token)) != OK) {
		free(id_string);
		return error;	//gettoken
	}
	
	if(token.name != AS) {			//ID As
		free(id_string);
		return SYN_A_ERROR;
	}
	
	if((error = Get_Token(&token)) != OK) {
		free(id_string);
		return error;	//gettoken
	}
	
	if((error = p_type() != OK)) {	//ID As <p_type>
		free(id_string);
		return error;
	}
	
	//Vlozenie par do TS + clear_token
	INSERT_PAR(token.name, id_string, funcName, ptrht);
	free(id_string);
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_declare_nextparameter>
			
			if((error = Get_Token(&token)) != OK)
				return error;	//gettoken
			
			return p_declare_nextparameter(funcName);
		default:
			return SYN_A_ERROR;
	}
}

//<p_declare_nextparameter>	ID As <p_type>)
//<p_declare_nextparameter>	ID As <p_type>, <p_declare_nextparameter>
int p_declare_nextparameter(char* funcName) {
	
	tRetData *idData = NULL;
	if((error = id(&idData, &token, ptrht)) != UNEXIST) {	//ID
		int ret;
		
		if(error == NON_ID)
			ret = SYN_A_ERROR;
		else //if(error == DIM_ID || error == F_ID)
			ret = SEM_TYPE_ERROR;
		
		DELETE_SEARCH(idData);
		return ret;
	}
	DELETE_SEARCH(idData);
	
	char *id_string = (char*)malloc(sizeof(char) * strlen(token.data));
	strcpy(id_string, token.data);
	
	if((error = Get_Token(&token)) != OK) {
		free(id_string);
		return error;	//gettoken
	}
	
	if(token.name != AS) {			//ID As
		free(id_string);
		return SYN_A_ERROR;
	}
	
	if((error = Get_Token(&token)) != OK) {
		free(id_string);
		return error;	//gettoken
	}
	
	if((error = p_type() != OK)) {	//ID As <p_type>
		free(id_string);
		return error;
	}
	
	//Vlozenie par do TS + clear_token
	INSERT_PAR(token.name, id_string, funcName, ptrht);
	free(id_string);
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_declare_nextparameter>
			
			if((error = Get_Token(&token)) != OK)
				return error;	//gettoken
			
			return p_declare_nextparameter(funcName);
		default:
			return SYN_A_ERROR;
	}
}

//<p_vparameter>	ε)
//<p_vparameter>	ID)
//<p_vparameter>	ID, <p_vnextparameter>
int p_vparameter(tRetData *funcData, int *pocet_parametrov) {
	
	if(token.name == RIGHTPAREN)	//ε)
		return OK;
	
    if(p_type() == OK) {    //pri vstupovani presnych vyrazov, nie premennych
        
        if(token.name != funcData->typy[*pocet_parametrov])
            return SEM_TYPE_ERROR;
        
    } else {
        tRetData *idData = NULL;
        if((error = id(&idData, &token, ptrht)) != DIM_ID) {	//ID
            int ret;
		
            if(error == NON_ID)
                ret = SYN_A_ERROR;
            else //if(error == F_ID)
                ret = SEM_TYPE_ERROR;
        
            DELETE_SEARCH(idData);
            return ret;
        }
        
        //Semanticke overovanie vstupneho parametra == Data type
        if(idData->type != funcData->typy[*pocet_parametrov]) {
            DELETE_SEARCH(idData);
            return SEM_TYPE_ERROR;
        }
        
        DELETE_SEARCH(idData);
	
    }
    
	//inkrement poctu parametrov po korektnom prejdeni
	(*pocet_parametrov)++;
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID)
			return OK;
		case(COMMA):				//ID, <p_nextparameter>
			
			if((error = Get_Token(&token)) != OK)
				return error;	//gettoken
			
			return p_vnextparameter(funcData, pocet_parametrov);
		default:
			return SYN_A_ERROR;
	}
}

//<p_vnextparameter>	ID)
//<p_vnextparameter>	ID, <p_vnextparameter>
int p_vnextparameter(tRetData *funcData, int *pocet_parametrov) {
	
    if(p_type() == OK) {    //pri vstupovani presnych vyrazov, nie premennych
        
        //najhnusnejsia vec v mojom zivote, ktoru som urobil, aby sme nemuseli prerabat projekt kvoli roznym typom v tokene a TS
        if(!((token.name == INT_NUM && funcData->typy[*pocet_parametrov] == INTEGER) ||
           (token.name == DOUBLE_NUM && funcData->typy[*pocet_parametrov] == DOUBLE) ||
           (token.name == STR && funcData->typy[*pocet_parametrov] == STRING) ||
           (token.name == BL && funcData->typy[*pocet_parametrov] == BOOLEAN_)))
            return SEM_TYPE_ERROR;
        
    } else {
        tRetData *idData = NULL;
        if((error = id(&idData, &token, ptrht)) != DIM_ID) {    //ID
            int ret;
            
            if(error == NON_ID)
                ret = SYN_A_ERROR;
            else //if(error == F_ID)
                ret = SEM_TYPE_ERROR;
            
            DELETE_SEARCH(idData);
            return ret;
        }
        
        //Semanticke overovanie vstupneho parametra == Data type
        if(idData->type != funcData->typy[*pocet_parametrov]) {
            DELETE_SEARCH(idData);
            return SEM_TYPE_ERROR;
        }
        
        DELETE_SEARCH(idData);
        
    }
    
    //inkrement poctu parametrov po korektnom prejdeni
    (*pocet_parametrov)++;
    
    if((error = Get_Token(&token)) != OK)
        return error;    //gettoken
    
    switch(token.name) {
        case(RIGHTPAREN):            //ID)
            return OK;
        case(COMMA):                //ID, <p_nextparameter>
            
            if((error = Get_Token(&token)) != OK)
                return error;    //gettoken
            
            return p_vnextparameter(funcData, pocet_parametrov);
        default:
            return SYN_A_ERROR;
    }
}

//<p_prikaz>			ε
//<p_prikaz>			Dim ID As <p_type>
//<p_prikaz>			ID = <p_priradenie>
//<p_prikaz>			Input ID
//<p_prikaz>			Print <p_print>
//<p_prikaz>			If (<p_vyraz>) Then EOL <p_body> Else EOL <p_body> End If
//<p_prikaz>			Do While (<p_vyraz>) EOL <p_body> Loop
//<p_prikaz>			Return <vyraz>
int p_prikaz(int return_type) {
	
	/*
	 	Uprava navratovej hodnoty error v celej funkcii
	 	z dovodu korekcie uvolnenia pamate v *idData a
	 	prikazu switch
	 */
	tRetData *idData = NULL;
	error = OK;
	TOKEN idToken;
    
	switch(token.name) {
		case(DIM):							//Dim
			
			Init_Token(&idToken);
			if((error = Get_Token(&idToken)) != OK)	//ulozenie potencialneho id do idToken
				break;	//gettoken
			
			if((error = id(&idData, &idToken, ptrht)) != UNEXIST) {	//Dim ID
				//int ret;
				
				if(error == NON_ID)
					error = SYN_A_ERROR;
				else //if(error == DIM_ID || error == F_ID)
					error = SEM_ERROR;
				
				Clear_Token(&idToken);
				//DELETE_SEARCH(idData);
				break;
			}
			DELETE_SEARCH(idData);
			
			if((error = Get_Token(&token)) != OK) {
				Clear_Token(&idToken);
				break;	//gettoken
			}
			
			if(token.name != AS) {			//Dim ID As
				Clear_Token(&idToken);
				error = SYN_A_ERROR;
				break;
			}
				
			if((error = Get_Token(&token)) != OK) {
				Clear_Token(&idToken);
				break;	//gettoken
			}
			
			if((error = p_type()) != OK) {	//Dim ID As <p_type>
				Clear_Token(&idToken);
				break;
			}
			
			//Vlozenie ID do TS
			INSERT_DIM(token.name, idToken.data, ptrht);
			
			Clear_Token(&idToken);
			break;
		case(INPUT):					//Input
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if((error = id(&idData, &token, ptrht)) != DIM_ID) {	//Input ID
				//int ret;
				
				if(error == NON_ID)
					error = SYN_A_ERROR;
				else //if(error == UNEXIST || error == F_ID)
					error = SEM_ERROR;
				
				DELETE_SEARCH(idData);
				break;
			}
			
			error = OK;
			
			break;
		case(PRINT):					//Print
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			//ocakavame p_print
			error = p_print();					//Print <p_print>
			
			break;
		case(IF):							//If
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if((error = p_vyraz(BL)) != OK)	//If <p_vyraz>
				break;
			
			loaded_token = false;
			
			if(token.name != THEN) {		//If <p_vyraz> Then
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if(token.name != EOL_) {		//If <p_vyraz> Then EOL
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if((error = p_body(return_type)) != OK) {	//If <p_vyraz> Then EOL <p_body>
				break;
			}
			
			if(token.name != ELSE) {		//If <p_vyraz> Then EOL <p_body> Else
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if(token.name != EOL_) {		//If <p_vyraz> Then EOL <p_body> Else EOL
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if((error = p_body(return_type)) != OK) {	//If <p_vyraz> Then EOL <p_body> Else EOL <p_body>
				break;
			}
			
			if(token.name != END) {			//If <p_vyraz> Then EOL <p_body> Else EOL <p_body> End
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if(token.name != IF) {			//If <p_vyraz> Then EOL <p_body> Else EOL <p_body> End If
				error = SYN_A_ERROR;
				break;
			}
			
			break;
		case(DO):							//Do
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if(token.name != WHILE) {		//Do While
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if((error = p_vyraz(BL)) != OK)	//Do While <p_vyraz>
				break;
			
			loaded_token = false;
			
			if(token.name != EOL_) {		//Do While <p_vyraz> EOL
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if((error = p_body(return_type)) != OK) {	//Do While <p_vyraz> EOL <p_body>
				break;
			}
			
			if(token.name != LOOP) {
				error = SYN_A_ERROR;
				break;
			}
			
			break;
		case(RETURN):					//Return
			
            if(return_type == 0) {  //sme v SCOPE, ten nemoze mat return
                error = OTHER_SEM_ERROR;
                break;
            }
            
			if((error = Get_Token(&token)) != OK)
				break;	//gettoken
			
			if((error = p_vyraz(return_type)) != OK)	//Return <p_vyraz>
				break;
			
			break;
		default:
			
			if((error = id(&idData, &token, ptrht)) != DIM_ID) {
				//int ret;
				
				if(error == NON_ID)
					error = E_OK;				//ε
				else //if(error == F_ID)
					error = SEM_ERROR;
				
				//DELETE_SEARCH(idData);
				break;
			}
			
			if((error = Get_Token(&token)) != OK) {
				break;	//gettoken
			}
			
			if(token.name != EQUAL) {		//ID =
				error = SYN_A_ERROR;
				break;
			}
			
			if((error = Get_Token(&token)) != OK) {
				break;	//gettoken
			}
				
			if((error = p_priradenie(idData->type)) != OK) {	//ID = <p_priradenie>
				break;
			}
			
			break;
	}
	
	DELETE_SEARCH(idData);
	return error;
}

//<p_priradenie>		F_ID(<p_vparameter>
//<p_priradenie>		<p_vyraz>
int p_priradenie(int type) {
	
	tRetData *idData = NULL;
	if((error = id(&idData, &token, global_ptrht)) != F_ID) {
		
		if((error = p_vyraz(type)) != OK) {		//<p_vyraz>
			DELETE_SEARCH(idData);
			return error;
		}
		
		DELETE_SEARCH(idData);
		return OK;
	}						//F_ID
	//DELETE_SEARCH(idData);
	
	if((error = Get_Token(&token)) != OK) {
		DELETE_SEARCH(idData);
		return error;	//gettoken
	}
	
	if(token.name != LEFTPAREN) {			//F_ID(
		DELETE_SEARCH(idData);
		return SYN_A_ERROR;
	}
	
	if((error = Get_Token(&token)) != OK) {
		DELETE_SEARCH(idData);
		return error;	//gettoken
	}
	
	int pocet_parametrov = 0;
	if((error = p_vparameter(idData, &pocet_parametrov)) != OK) {	//F_ID(<p_vparameter>
		DELETE_SEARCH(idData);
		return error;
	}
	
	if(idData->pocet_parametru != pocet_parametrov) {
		DELETE_SEARCH(idData);
		return SEM_TYPE_ERROR;
	}
	
	DELETE_SEARCH(idData);
	return OK;
}

//<p_print>			<p_vyraz>; <p_nextprint>
//<p_print>			<p_string>; <p_nextprint>
int p_print(void) {
	
	if(token.name != STR) {			//String
		if((error = p_vyraz(STR)) != OK)	//<p_vyraz>
			return error;
	}
	
	if(!loaded_token) {		//vola sa, ak prikaz nebol vyrazom, teda nie je nacitany novy token
		if((error = Get_Token(&token)) != OK)
			return error;	//gettoken
	}
	
	loaded_token = false;
	
	if(token.name != SEMICOLON)
		return SYN_A_ERROR;
	
	return p_nextprint();				//String/<p_vyraz> <p_nextprint>
}

//<p_nextprint>		ε
//<p_nextprint>		<p_vyraz>; <p_nextprint>
//<p_nextprint>		<p_string>; <p_nextprint>
int p_nextprint(void) {
	
	if((error = Get_Token(&token)) != OK)
		return error;	//gettoken
	
	if(token.name == EOL_) {		//ε
		loaded_token = true;
		return OK;
	}
		
	if(token.name != STRING) {			//String
		if((error = p_vyraz(STR)) != OK)	//<p_vyraz>
			return error;
	}
	
	if(!loaded_token) {		//vola sa, ak prikaz nebol vyrazom, teda nie je nacitany novy token
		if((error = Get_Token(&token)) != OK)
			return error;	//gettoken
	}
	
	loaded_token = false;
	
	if(token.name != SEMICOLON)
		return SYN_A_ERROR;
	
	return p_nextprint();				//; String/<p_vyraz> <p_nextprint>
}


