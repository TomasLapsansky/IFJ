/**
 * @Name IFJ17 Syntakticka a sematicka analyza
 * @author Tomas Lapsansky (xlapsa00)
 * @file parser.c
 * @date 15.11.2017
 */

#include "parser.h"

#include "scanner.h"
#include "parser.h"
#include "ts.h"
#include "tstack.h"
#include "structs.h"

extern FILE* f;
extern TOKEN token;
extern int error;			//error code
extern int line;			//line number

bool loaded_token = false;

extern tStack s;
extern tHTable *ptrht;
//extern tRetData retData;
int parameter_index = 0;

//spracovanie ID		TODO
int id(tRetData *retData) {
	if(token.name == ID) {
		if((retData = SEARCH(token.data, ptrht)) == NULL)
			return SEM_ERROR;
		
		if(retData->funkce)
			return F_OK;
		else
			return OK;
	}
	
	return SYN_A_ERROR;
}

//main
int parser(void) {
	line = 1;
	
	return p_start();
}

//<p_start>		<p_declare> <p_scope>
int p_start(void) {
	
	if((error = Get_Token(f, &token)) != OK) {
		return error;
	}
	
	if((error = p_declare()) != OK)
		return error;
	
	if((error = p_scope()) != OK)
		return error;
	
	return OK;
}//p_start

//<p_declare>		ε
//<p_declare>		Declare Function ID (<p_declareparameter> As <p_type> "EOL" <p_declare>
//<p_declare>		Function ID (<p_parameter> As <p_type> "EOL" <p_body> <p_declare>
int p_declare(void) {
	
	parameter_index = 0;
	
	switch(token.name) {
			
		case(DECLARE):						//Declare
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token.name != FUNCTION)		//Declare Function
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = id(NULL)) != SEM_ERROR)		//Declare Function ID
				return SEM_ERROR;
			
			INSERT_F(token.data, ptrht);
			
			TOKEN idToken;
			Init_Token(&idToken);
			idToken = token;
			
			if((error = Get_Token(f, &token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if(token.name != LEFTPAREN)	{	//Declare Function ID(
				Clear_Token(&idToken);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if((error = p_declareparameter(idToken.data)) != OK) {		//Declare Function ID(<p_declareparameter>)
				Clear_Token(&idToken);
				return error;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if(token.name != AS) {			//Declare Function ID(<p_parameter>) As
				Clear_Token(&idToken);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				Clear_Token(&idToken);
				return error;//gettoken
			}
			
			if((error = p_type()) != OK) {	//Declare Function ID(<p_parameter>) As <p_type>
				Clear_Token(&idToken);
				return error;
			}
			
			INSERT_F_TYPE(token.name, idToken.data, ptrht);
			Clear_Token(&idToken);
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token.name != EOL_)			//Declare Function ID(<p_parameter>) As <p_type> EOL
				return SYN_A_ERROR;
			
			//line++;	//pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			return p_declare();				//prechod do potencialneho dalsieho stavu
			
			break;
			
		case(FUNCTION):					//Function
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			tRetData *fIdData = NULL;
			
			if((error = id(fIdData)) != F_OK) {		//Function ID
				DELETE_SEARCH(fIdData);
				return error;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(fIdData);
				return error;//gettoken
			}
			
			if(token.name != LEFTPAREN) {	//Function ID(
				DELETE_SEARCH(fIdData);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(fIdData);
				return error;//gettoken
			}
			
			if((error = p_parameter(fIdData)) != OK) {		//Function ID(<p_parameter>)
				DELETE_SEARCH(fIdData);
				return error;
			}
			
			if(fIdData->pocet_parametru != (parameter_index + 1)) {
				DELETE_SEARCH(fIdData);
				return SEM_TYPE_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(fIdData);
				return error;//gettoken
			}
				
			if(token.name != AS) {			//Function ID(<p_parameter>) As
				DELETE_SEARCH(fIdData);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(fIdData);
				return error;//gettoken
			}
			
			if((error = p_type()) != OK) {	//Function ID(<p_parameter>) As <p_type>
				DELETE_SEARCH(fIdData);
				return error;
			}
			
			if(fIdData->type != token.name) {	//Chybny navratovy parameter Funkcie
				DELETE_SEARCH(fIdData);
				return SEM_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(fIdData);
				return error;//gettoken
			}
			
			if(token.name != EOL_) {			//Function ID(<p_parameter>) As <p_type> EOL
				DELETE_SEARCH(fIdData);
				return SYN_A_ERROR;
			}
			
			//line++;	//pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(fIdData);
				return error;//gettoken
			}
			
			
			//////////////////////PRIDAT STACK//////////////////
			//stackPush(&s, ptrht);
			//ptrht = fIdData.
			
			DELETE_SEARCH(fIdData);
			
			if((error = p_body()) != OK) {		//Function ID(<p_parameter>) As <p_type> EOL <p_body>
				return error;
			}
			
			if(token.name != END)			//Function ID(<p_parameter>) As <p_type> EOL <p_body> End
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token.name != FUNCTION)		//Function ID(<p_parameter>) As <p_type> EOL <p_body> End Function
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token.name != EOL_)		//Function ID(<p_parameter>) As <p_type> EOL <p_body> End Function EOL
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
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
int p_body(void) {
	
	if((error = p_prikaz()) == E_OK) {
		return OK;
	} else if(error != OK) {
		return error;
	}
	
	if(!loaded_token) {		//vola sa, ak prikaz nebol vyrazom, teda nie je nacitany novy token
		if((error = Get_Token(f, &token)) != OK)
			return error;	//gettoken
	}
	
	loaded_token = false;
	
	if(token.name != EOL_)
		return SYN_A_ERROR;
	
	//line++;	//pocitadlo riadku pre vypis pri chybe
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	return p_body();
	
}

//<p_type>		Integer
//<p_type>		Double
//<p_type>		String
int p_type(void) {
	switch(token.name) {
		case(INTEGER):
		case(DOUBLE):
		case(STRING):
			return OK;
		default:
			return SYN_A_ERROR;
	}
}

//<p_scope>		Scope EOL <p_body> End Scope EOF
int p_scope(void) {
	if(token.name != SCOPE)	//Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != EOL_)		//Scope <p_body> End
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_body()) != OK) {	//Scope <p_body>
		return error;
	}
	
	if(token.name != END)		//Scope <p_body> End
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != SCOPE)		//Scope <p_body> End Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != EOL_)		//Scope <p_body> End Scope EOF
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != EOF_)		//Scope <p_body> End Scope EOF
		return SYN_A_ERROR;
	
	return OK;
}

//<p_parameter>	ε)
//<p_parameter>	ID As <p_type>)
//<p_parameter>	ID As <p_type>, <p_nextparameter>
int p_parameter(tRetData *fIdData) {
	
	if(token.name == RIGHTPAREN)	//ε)
		return OK;
	
	if((error = id(fIdData)) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK))	//ID As <p_type>
		return error;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_nextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_nextparameter();
		default:
			return SYN_A_ERROR;
	}
}

//<p_nextparameter>	ID As <p_type>)
//<p_nextparameter>	ID As <p_type>, <p_nextparameter>
int p_nextparameter(void) {
	
	if((error = id(NULL)) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK))	//ID As <p_type>
		return error;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_nextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_nextparameter();
		default:
			return SYN_A_ERROR;
	}
}

//<p_declareparameter>	ε)
//<p_declareparameter>	ID As <p_type>)
//<p_declareparameter>	ID As <p_type>, <p_nextparameter>
int p_declareparameter(char *fID) {
	
	if(token.name == RIGHTPAREN)	//ε)
		return OK;
	
	if(token.name != ID) {			//ID
		return error;
	}
	
	TOKEN idToken;
	Init_Token(&idToken);
	idToken = token;
	
	if((error = Get_Token(f, &token)) != OK) {
		Clear_Token(&idToken);
		return error;	//gettoken
	}
	
	if(token.name != AS) {			//ID As
		Clear_Token(&idToken);
		return SYN_A_ERROR;
	}
	
	if((error = Get_Token(f, &token)) != OK) {
		Clear_Token(&idToken);
		return error;	//gettoken
	}
	
	if((error = p_type() != OK)) {	//ID As <p_type>
		Clear_Token(&idToken);
		return error;
	}
	
	INSERT_PAR(token.name, idToken.data, fID, ptrht);
	Clear_Token(&idToken);
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_decnextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_decnextparameter(fID);
		default:
			return SYN_A_ERROR;
	}
}

//<p_decnextparameter>	ID As <p_type>)
//<p_decnextparameter>	ID As <p_type>, <p_decnextparameter>
int p_decnextparameter(char *fID) {
	
	if((error = id(NULL)) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK))	//ID As <p_type>
		return error;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_decnextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_decnextparameter(fID);
		default:
			return SYN_A_ERROR;
	}
}

//<p_vparameter>	ε)
//<p_vparameter>	ID)
//<p_vparameter>	ID, <p_vnextparameter>
int p_vparameter(tRetData *fIdData) {
	
	if(token.name == RIGHTPAREN)	//ε)
		return OK;
	
	//Semantika na overenie parametrov
	tRetData *vpar;
	
	if((vpar = SEARCH(token.data, ptrht)) == NULL) {
		DELETE_SEARCH(vpar);
		return SEM_ERROR;
	}
	
	if(vpar->type != fIdData->typy[parameter_index]) {
		DELETE_SEARCH(vpar);
		return SEM_TYPE_ERROR;
	}
	
	parameter_index++;
	
	DELETE_SEARCH(vpar);
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID)
			return OK;
		case(COMMA):				//ID, <p_nextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_vnextparameter(fIdData);
		default:
			return SYN_A_ERROR;
	}
}

//<p_vnextparameter>	ID)
//<p_vnextparameter>	ID, <p_vnextparameter>
int p_vnextparameter(tRetData *fIdData) {
	
	//Sematika na overenie parametrov
	tRetData *vpar = NULL;
	
	if((vpar = SEARCH(token.data, ptrht)) == NULL) {
		DELETE_SEARCH(vpar);
		return SEM_ERROR;
	}
	
	if(vpar->type != fIdData->typy[parameter_index]) {
		DELETE_SEARCH(vpar);
		return SEM_TYPE_ERROR;
	}
	
	parameter_index++;
	
	DELETE_SEARCH(vpar);
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token.name) {
		case(RIGHTPAREN):			//ID)
			return OK;
		case(COMMA):				//ID, <p_nextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_vnextparameter(fIdData);
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
int p_prikaz(void) {
	
	switch(token.name) {
		case(DIM):							//Dim
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = id(NULL)) != SEM_ERROR)	//Dim ID
				return SEM_ERROR;
			
			TOKEN idToken;
			if((error = Init_Token(&idToken)) != OK)
				return error;
			
			idToken = token;
			
			if((error = Get_Token(f, &token)) != OK) {
				Clear_Token(&idToken);
				return error;	//gettoken
			}
			
			if(token.name != AS) {			//Dim ID As
				Clear_Token(&idToken);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				Clear_Token(&idToken);
				return error;	//gettoken
			}
			
			if((error = p_type()) != OK) {	//Dim ID As <p_type>
				Clear_Token(&idToken);
				return error;
			}
			
			INSERT_DIM(token.name, idToken.data, ptrht);	//DIMINSERT
			Clear_Token(&idToken);
			
			return OK;
			break;
		case(INPUT):					//Input
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = id(NULL)) != OK)
				return error;
			
			return OK;
			break;
		case(PRINT):					//Print
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			//ocakavame p_print
			return p_print();					//Print <p_print>
			
			break;
		case(IF):							//If
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_vyraz(BL)) != OK)	//If <p_vyraz>
				return error;
			
			loaded_token = false;
			
			if(token.name != THEN)			//If <p_vyraz> Then
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token.name != EOL_)			//If <p_vyraz> Then EOL
				return SYN_A_ERROR;
			
			//line++; //pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_body()) != OK) {	//If <p_vyraz> Then EOL <p_body>
				return error;
			}
			
			if(token.name != ELSE)			//If <p_vyraz> Then EOL <p_body> Else
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token.name != EOL_)			//If <p_vyraz> Then EOL <p_body> Else EOL
				return SYN_A_ERROR;
			
			//line++; //pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_body()) != OK) {	//If <p_vyraz> Then EOL <p_body> Else EOL <p_body>
				return error;
			}
			
			if(token.name != END)			//If <p_vyraz> Then EOL <p_body> Else EOL <p_body> End
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token.name != IF)			//If <p_vyraz> Then EOL <p_body> Else EOL <p_body> End If
				return SYN_A_ERROR;
			
			return OK;
			
			break;
		case(DO):							//Do
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token.name != WHILE)		//Do While
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_vyraz(BL)) != OK)	//Do While <p_vyraz>
				return error;
			
			loaded_token = false;
			
			if(token.name != EOL_)			//Do While <p_vyraz> EOL
				return SYN_A_ERROR;
			
			//line++; //pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_body()) != OK) {	//Do While <p_vyraz> EOL <p_body>
				return error;
			}
			
			if(token.name != LOOP)
				return SYN_A_ERROR;
			
			return OK;
			
			break;
		case(RETURN):					//Return
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_vyraz(INT_NUM)) != OK)	//Return <p_vyraz> <-----------------------------potrebna oprava
				return error;
			
			return OK;
			
			break;
	}
			tRetData *idData = NULL;
			
			if((error = id(idData)) != OK) {	//ak nie je id, vracia ε
				DELETE_SEARCH(idData);
				return E_OK;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(idData);
				return error;	//gettoken
			}
			
			if(token.name != EQUAL) {			//ID =
				DELETE_SEARCH(idData);
				return SYN_A_ERROR;
			}
			
			if((error = Get_Token(f, &token)) != OK) {
				DELETE_SEARCH(idData);
				return error;
			}//gettoken
			
			if((error = p_priradenie(idData->type)) != OK) {	//ID = <p_priradenie>
				DELETE_SEARCH(idData);
				return error;
			}
			
			DELETE_SEARCH(idData);
			
			return OK;
}

//<p_priradenie>		F_ID(<p_vparameter>
//<p_priradenie>		<p_vyraz>
int p_priradenie(int type) {
	
	tRetData *idData = NULL;
	
	if((error = id(idData)) != F_OK) {			//je potreba rozhodnut, ci sa jedna o F_ID alebo nie
		if((error = p_vyraz(type)) != OK) {		//<p_vyraz>
			DELETE_SEARCH(idData);
			return error;
		}
		
		DELETE_SEARCH(idData);
		return OK;
	}										//F_ID
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token.name != LEFTPAREN)			//F_ID(
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	parameter_index = 0;
	if((error = p_vparameter(idData)) != OK)		//F_ID(<p_vparameter>
		return error;
	
	if(parameter_index != (idData->pocet_parametru - 1))
	   return SEM_TYPE_ERROR;
	
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
		if((error = Get_Token(f, &token)) != OK)
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
	
	if((error = Get_Token(f, &token)) != OK)
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
		if((error = Get_Token(f, &token)) != OK)
			return error;	//gettoken
	}
	
	loaded_token = false;
	
	if(token.name != SEMICOLON)
		return SYN_A_ERROR;
	
	return p_nextprint();				//; String/<p_vyraz> <p_nextprint>
}

//
//------------------------------TODO------------------------------
//
//<p_vyraz>
int p_vyraz(int type) {
	
	//pre testovanie vyrazov, bude nasledovat uprava
	while(token.name != THEN && token.name != EOL_ && token.name != SEMICOLON) {
		if((error = Get_Token(f, &token)) != OK)
			return error;
	}
	
	loaded_token = true;
	
	return OK;
}

