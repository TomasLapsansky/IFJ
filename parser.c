/**
 * @Name IFJ17 Syntakticka a sematicka analyza
 * @author Tomas Lapsansky (xlapsa00)
 * @file parser.c
 * @date 15.11.2017
 */

#include "scanner.h"
#include "structs.h"
#include "parser.h"

TOKEN token;
int error;			//error code
int line = 1;		//line number

//spracovanie ID		TODO
int id(void) {
	
}

//main
int parse(void) {
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
//<p_declare>		Declare Function ID (<p_parameter> As <p_type> EOL <p_declare>
//<p_declare>		Function ID (<p_parameter> As <p_type> EOL <p_body> <p_declare>
int p_declare(void) {
	
	switch(token->name) {
		
		case(DECLARE):						//Declare
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != FUNCTION)		//Declare Function
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = id()) != OK)		//Declare Function ID
				return error;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != LEFTPAREN)	//Declare Function ID(
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = p_parameter()) != OK) {		//Declare Function ID(<p_parameter>)
				return error;
			}
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != AS)			//Declare Function ID(<p_parameter>) As
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = p_type()) != OK) {	//Declare Function ID(<p_parameter>) As <p_type>
				return error;
			}
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != EOL)			//Declare Function ID(<p_parameter>) As <p_type> EOL
				return SYN_A_ERROR;
			
			line++;	//pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			return p_declare();				//prechod do potencialneho dalsieho stavu
			
			break;
			
		case(FUNCTION):					//Function
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = id()) != OK)		//Function ID
				return error;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != LEFTPAREN)	//Function ID(
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = p_parameter()) != OK) {		//Function ID(<p_parameter>)
				return error;
			}
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != AS)			//Function ID(<p_parameter>) As
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = p_type()) != OK) {	//Function ID(<p_parameter>) As <p_type>
				return error;
			}
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != EOL)			//Function ID(<p_parameter>) As <p_type> EOL
				return SYN_A_ERROR;
			
			line++;	//pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = p_body()) != OK) {		//Function ID(<p_parameter>) As <p_type> EOL <p_body>
				return error;
			}
			
			if(token->name != END)			//Function ID(<p_parameter>) As <p_type> EOL <p_body> End
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->name != FUNCTION)		//Function ID(<p_parameter>) As <p_type> EOL <p_body> End Function
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
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != EOL)
		return SYN_A_ERROR;
	
	line++;	//pocitadlo riadku pre vypis pri chybe
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	return p_body();
	
}

//<p_type>		Integer
//<p_type>		Double
//<p_type>		String
int p_type(void) {
	switch(token->name) {
		case(INTEGER):
		case(DOUBLE):
		case(STRING):
			return OK;
		default:
			return SYN_A_ERROR;
	}
}

//<p_scope>		Scope <p_body> End Scope EOF
int p_scope(void) {
	if(token->name != SCOPE)	//Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_body()) != OK) {	//Scope <p_body>
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != END)		//Scope <p_body> End
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != SCOPE)		//Scope <p_body> End Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != EOF)		//Scope <p_body> End Scope EOF
		return SYN_A_ERROR;
	
	return OK;
}

//<p_parameter>	ε)
//<p_parameter>	ID As <p_type>)
//<p_parameter>	ID As <p_type>, <p_nextparameter>
int p_parameter(void) {
	
	if(token->name == RIGHTPAREN)	//ε)
		return OK;
	
	if((error = id()) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK)		//ID As <p_type>
		return error;
	   
	if((error = Get_Token(f, &token)) != OK)
	   return error;	//gettoken
	   
	switch(token->name) {
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
	
	if((error = id()) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK)		//ID As <p_type>
	   return error;
	   
	   if((error = Get_Token(f, &token)) != OK)
	   return error;	//gettoken
	   
	switch(token->name) {
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

//<p_vparameter>	ε)
//<p_vparameter>	ID)
//<p_vparameter>	ID, <p_vnextparameter>
int p_vparameter(void) {
	
	if(token->name == RIGHTPAREN)	//ε)
		return OK;
	
	if((error = id()) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token->name) {
		case(RIGHTPAREN):			//ID)
			return OK;
		case(COMMA):				//ID, <p_nextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_vnextparameter();
		default:
			return SYN_A_ERROR;
	}
}

//<p_vnextparameter>	ID)
//<p_vnextparameter>	ID, <p_vnextparameter>
int p_vnextparameter(void) {
	
	if((error = id()) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	switch(token->name) {
		case(RIGHTPAREN):			//ID)
			return OK;
		case(COMMA):				//ID, <p_nextparameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_vnextparameter();
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
	
	switch(token->name) {
		case(DIM):							//Dim
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = id()) != OK)		//Dim ID
				return error;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != AS)			//Dim ID As
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_type()) != OK)	//Dim ID As <p_type>
				return error;
			
			return OK;
			break;
		case(INPUT):					//Input
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = id()) != OK)
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
			
			if(token->name != LEFTPAREN)	//If (
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_vyraz()) != OK)	//If (<p_vyraz>
				return error;
			
			if(token->name != RIGHTPAREN)	//If (<p_vyraz>)
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != THEN)			//If (<p_vyraz>) Then
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != EOL)			//If (<p_vyraz>) Then EOL
				return SYN_A_ERROR;
			
			line++; //pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_body()) != OK) {	//If (<p_vyraz>) Then EOL <p_body>
				return error;
			}
				
			if(token->name != ELSE)			//If (<p_vyraz>) Then EOL <p_body> Else
				return SYN_A_ERROR;
				
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != EOL)			//If (<p_vyraz>) Then EOL <p_body> Else EOL
				return SYN_A_ERROR;
			
			line++; //pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_body()) != OK) {	//If (<p_vyraz>) Then EOL <p_body> Else EOL <p_body>
				return error;
			}
			
			if(token->name != END)			//If (<p_vyraz>) Then EOL <p_body> Else EOL <p_body> End
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != IF)			//If (<p_vyraz>) Then EOL <p_body> Else EOL <p_body> End If
				return SYN_A_ERROR;
			
			return OK;
			
			break;
		case(DO):							//Do
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != WHILE)		//Do While
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != LEFTPAREN)	//Do While (
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_vyraz()) != OK)	//Do While (<p_vyraz>
				return error;
			
			if(token->name != RIGHTPAREN)	//Do While (<p_vyraz>)
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != EOL)			//Do While (<p_vyraz>) EOL
				return SYN_A_ERROR;
			
			line++; //pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_body()) != OK) {	//Do While (<p_vyraz>) EOL <p_body>
				return error;
			}
				
			if(token->name != Loop)
				return SYN_A_ERROR;
			
			return OK;
				
			break;
		case(RETURN):					//Return
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_vyraz()) != OK)	//Do While (<p_vyraz>
				return error;
			
			return OK;
			
			break;
		default:
			
			if((error = id()) != OK)			//ak nie je id, vracia ε
				return E_OK;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if(token->name != EQUAL)			//ID =
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			if((error = p_priradenie()) != OK)	//ID = <p_priradenie>
				return error;
			
			return OK;
			
			break;
	}
}

//<p_priradenie>		F_ID(<p_vparameter>
//<p_priradenie>		<p_vyraz>
int p_priradenie(void) {
	
	if((error = id()) != OK) {				//F_ID
		if((error = p_vyraz()) != OK) {		//<p_vyraz>
			return error;
		}
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != LEFTPAREN)			//F_ID(
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	return p_vparameter();					//F_ID(<p_vparameter>
	
}

//<p_print>			<p_vyraz> <p_nextprint>
//<p_print>			<p_string> <p_nextprint>
int p_print(void) {
	
	if(token->name != STRING) {			//String
		if((error = p_vyraz()) != OK)	//<p_vyraz>
			return error;
		
	}
	
	return p_nextprint();				//String/<p_vyraz> <p_nextprint>
}

//<p_nextprint>		ε
//<p_nextprint>		; <p_vyraz> <p_nextprint>
//<p_nextprint>		; <p_string> <p_nextprint>
int p_nextprint(void) {
	
	if(token->name != SEMICOLON)		//ε
		return E_OK;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->name != STRING) {			//; String
		if((error = p_vyraz()) != OK)	//; <p_vyraz>
			return error;
	}
	
	return p_nextprint();				//; String/<p_vyraz> <p_nextprint>
}

//
//------------------------------TODO------------------------------
//
//<p_vyraz>
int p_vyraz(void) {
	
	//pre testovanie vyrazov, bude nasledovat uprava
	while((error = p_type()) == OK) {
		if((error = Get_Token(f, &token)) != OK)
			return error;	//gettoken
	}
	
}
