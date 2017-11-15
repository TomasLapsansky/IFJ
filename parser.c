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
	
	switch(token->data) {
		
		case(DECLARE):						//Declare
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->data != FUNCTION)		//Declare Function
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if((error = id()) != OK)		//Declare Function ID
				return error;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->data != LEFTPAREN)	//Declare Function ID(
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			p_parameter();					//Declare Function ID(<p_parameter>)
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->data != AS)			//Declare Function ID(<p_parameter>) As
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			p_type();						//Declare Function ID(<p_parameter>) As <p_type>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->data != EOL)			//Declare Function ID(<p_parameter>) As <p_type> EOL
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
			
			if(token->data != LEFTPAREN)	//Function ID(
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			p_parameter();					//Function ID(<p_parameter>)
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->data != AS)			//Function ID(<p_parameter>) As
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			p_type();						//Function ID(<p_parameter>) As <p_type>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->data != EOL)			//Function ID(<p_parameter>) As <p_type> EOL
				return SYN_A_ERROR;
			
			line++;	//pocitadlo riadku pre vypis pri chybe
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			p_body();						//Function ID(<p_parameter>) As <p_type> EOL <p_body>
			
			if(token->data != END)			//Function ID(<p_parameter>) As <p_type> EOL <p_body> End
				return SYN_A_ERROR;
			
			if((error = Get_Token(f, &token)) != OK)
				return error;//gettoken
			
			if(token->data != FUNCTION)		//Function ID(<p_parameter>) As <p_type> EOL <p_body> End Function
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
	
	if(token->data != EOL)
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
	switch(token->data) {
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
	if(token->data != SCOPE)	//Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	p_body();					//Scope <p_body>
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->data != END)		//Scope <p_body> End
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->data != SCOPE)		//Scope <p_body> End Scope
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->data != EOF)		//Scope <p_body> End Scope EOF
		return SYN_A_ERROR;
	
	return OK;
}

//<p_parameter>	ε)
//<p_parameter>	ID As <p_type>)
//<p_parameter>	ID As <p_type>, <p_parameter>
int p_parameter(void) {
	
	if(token->data == RIGHTPAREN)	//ε)
		return OK;
	
	if((error = id()) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->data != AS)			//ID As
		return SYN_A_ERROR;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if((error = p_type() != OK)		//ID As <p_type>
		return error;
	   
	if((error = Get_Token(f, &token)) != OK)
	   return error;	//gettoken
	   
	switch(token->data) {
		case(RIGHTPAREN):			//ID As <p_type>)
			return OK;
		case(COMMA):				//ID As <p_type>, <p_parameter>
			
			if((error = Get_Token(f, &token)) != OK)
				return error;	//gettoken
			
			return p_parameter();
		default:
			return SYN_A_ERROR;
			
	}
}

//<p_vparameter>	ε)
//<p_vparameter>	ID)
//<p_vparameter>	ID, <p_parameter>
int p_vparameter(void) {
	
	if(token->data == RIGHTPAREN)	//ε)
		return OK;
	
	if((error = id()) != OK) {		//ID
		return error;
	}
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->data == RIGHTPAREN)	//ID)
		return OK;
	
	if((error = Get_Token(f, &token)) != OK)
		return error;	//gettoken
	
	if(token->data != COMMA)
	
}
