#include "psa.h"

extern TOKEN token;
extern tHTable* ptrht;
extern bool loaded_token;

// tabulka precedencni tabulky
static char prec_tab[14][14] = {
/*|        | * | / | + | - | < | > |<= |>= | = | <>| ( | ) |id | $ |      */
/*| * |*/  {'>','>','>','>','>','>','>','>',' ','>','<','>','<','>'},
/*| / |*/  {'>','<','>','>','>','>','>','>',' ','>','<','>','<','>'},
/*| + |*/  {'<','<','>','>','>','>','>','>',' ','>','<','>','<','>'},
/*| - |*/  {'<','<','>','>','>','>','>','>',' ','>','<','>','<','>'},
/*| < |*/  {'<','<','<','<','>','>','>','>',' ','>','<','>','<','>'},
/*| > |*/  {'<','<','<','<','>','>','>','>',' ','>','<','>','<','>'},
/*| <= |*/ {'<','<','<','<','>','>','>','>',' ','>','<','>','<','>'},
/*| >= |*/ {'<','<','<','<','>','>','>','>',' ','>','<','>','<','>'},
/*|  = |*/ {'<','<','<','<','<','<','<','<',' ','<','<','>','<','>'},
/*| <> |*/ {'<','<','<','<','>','>','>','>',' ','>','<','>','<','>'},
/*| (  |*/ {'<','<','<','<','<','<','<','<','<','<','<','<','<','>'},
/*| )  |*/ {'>','>','>','>','>','>','>','>',' ','>',' ','>',' ','>'},
/*| id |*/ {'>','>','>','>','>','>','>','>','>','>',' ','>',' ','>'},
/*| $  |*/ {'<','<','<','<','<','<','<','<','<','<','<',' ','<','-'},
};

// na zaklade token name, se urci cislo sloupce pro vyhledani, zda se ma provadet operace REDUCE/SEDUCE
int num_of_prec_table(TOKEN t){
	switch(t.name){
		case TIMES: return 0;break;
		case DIVISION: return 1;break;
		case DIVISION_INT: return 1;break;
		case PLUS: return 2;break;
		case MINUS: return 3;break;
		case LESSER: return 4;break;
		case GREATER: return 5;break;
		case LESSEREQUAL: return 6;break;
		case GREATEREQUAL: return 7;break;
		case EQUAL: return 8;break;
		case NOTEQUAL: return 9;break;
		case LEFTPAREN: return 10;break;
		case RIGHTPAREN: return 11;break;
		case ID: return 12;break;
		case INT_NUM: return 12;break;
		case DOUBLE_NUM: return 12;break;
		case STR: return 12;break;
		case BL: return 12;break;
		case THEN:
		case EOL_:
		case SEMICOLON:
		case ELSE: return 13;break;
		// chyba SA, nic jineho nemuze byt ve vyrazu
		default: return -1; break;

	}
}

int p_vyraz(int type){
	psa_list *list = psa_list_init();
	psa_item *newitem,*item,aitem[3];
	char sign;
	int column,error,start = 1;
	loaded_token = true;
	printf("\n*****START_PSA*****\n\n");
	tRetData *var;
//qprintf("##########################\n");
	newitem = psa_create_item();
	newitem->oper = OP_END;
	// vlozeni OP_END = & na zasobnik
	psa_list_push(list,newitem);
//qprintf("ZASOBNIK INICIALIZACE: $\n");
	//pre testovanie vyrazov, bude nasledovat uprava
	while(1){
		if(((token.name != THEN && token.name != EOL_ && token.name != SEMICOLON)&&(start == 0))&&(sign == '<')){
			if((error = Get_Token(&token)) != OK){
				psa_list_delete(list);
				return error;
			}

			if(token.name == EOF_){
				psa_list_delete(list);
				return SYN_A_ERROR;
			}
		}
		start = 0;
		// z tokenu dostanu hodnotu, ktera nam 
		// urci z jakeho sloupce se bude porovnavat v precedencni tabulce
		column = num_of_prec_table(token);

	 	// ve vstupnim vyrazu je spatny token, ktery nevyhovuje
		if(column == -1){
			psa_list_delete(list);
			return SYN_A_ERROR;
		}

		// kdyz narazim na promenou, zkontroluji zda je deklaravona
		if(token.name == ID){
			if((var = SEARCH(token.data,ptrht)) == NULL){
				// promena neni deklarovana
printf("Var %s not declared\n",token.data);
				psa_list_delete(list);
				return SYN_A_ERROR;
			}

			// kontrola zda je to funkce -> ERROR
			if(var->funkce == true){
				psa_list_delete(list);
				return SYN_A_ERROR;
			}
		}

//qprintf("__________________\n\n");
//qpsa_list_show(list);
		 // urceni operace, na zaklade precedencni tabulky
		item = psa_search_term(list);

//qprintf("VSTUP: %d\n\n",column);
		sign = prec_tab[item->oper][column];	
//qprintf("VYHODNOCENI PREC_TAB\n");
//qprintf("==========\n");
//qprintf("::::| %d|\n",column);
//qprintf(" %d | %c |\n",item->oper,sign);
//qprintf("==========\n\n");

		// $ == $ OK konec whilu
		if(sign == '-'){
			psa_item *final = psa_list_top(list);
			// ocekavany datovy typ
			switch(type){
				case INTEGER: type = INT_NUM; break;
				case DOUBLE: type = DOUBLE_NUM; break;
				case STRING: type = STR; break;
				case BOOLEAN_: type = BL; break;
				case BL: type = BL; break;
			}	
printf("final_data_type: %d type: %d\n",final->data_type,type);
			if(final->data_type == type){
				printf("*****PSA_COMPLETE******\n\n");
				psa_list_delete(list);
				return OK;
			}
			else{
				printf("*****VYSLEDEK NEMA STEJNY DATOVY TYP******\n\n");
				psa_list_delete(list);
				return SYN_A_ERROR;
			}
			break;
		}
		// $ != $ ERROR
		else if(sign == ' '){
			psa_list_delete(list);
			return SYN_A_ERROR;
			break;
printf("PSA_ERROR SIGN ' '\n");	
		}

		switch(sign){
/*        ---------  OPERACE < PSA ----------			*/
		 	case '<': {
//qprintf("PSA_OPERACE <:\n");
		 				// vrchol seznamu je TERM
		 				// pripad | &  |<|  i |   ===> &<i
		 				psa_item *topitem = psa_list_top(list);
		 				if((topitem->oper != OP_E)&&(topitem->oper != OP_EXP)){
		 					if(token.name != RIGHTPAREN){
			 					newitem = psa_create_item();
								newitem->oper = OP_EXP;
								// vlozeni OP_EXP = <
			 					psa_list_push(list,newitem);
		 					}

		 					// vytvoreni itemu pro nacteny token
		 					newitem = psa_create_item();

							if(token.name == DIVISION_INT){
								newitem->oper = OP_DIV;
							}else newitem->oper = column;

							// urceni hodnoty
							if(token.name == INT_NUM){
								newitem->data_type = token.name;
							 	newitem->value.i = give_me_int(token.data);
							}
							else if(token.name == DOUBLE_NUM){
								newitem->data_type = token.name;
							 	newitem->value.d = give_me_double(token.data);
							}
							else if(token.name == STR){
								newitem->data_type = token.name;
								int len = strlen(token.data);

								if((newitem->value.string = malloc(len+1)) == NULL){
									return ALLOC_ERROR;
								}
								memcpy(newitem->value.string,token.data,len +1);
							}
							else if(token.name == BL){
								newitem->data_type = token.name;
							 	newitem->value.i = give_me_int(token.data);
							}
							else if(token.name == ID){
									//TODO
								switch(var->type){
										case INTEGER: newitem->data_type = INT_NUM; break;
										case DOUBLE: newitem->data_type = DOUBLE_NUM; break;
										case STRING: newitem->data_type = STR; break;
										case BOOLEAN_: newitem->data_type = BL; break;
									}	
							}							

							// vlozeni TERMU
		 					psa_list_push(list,newitem);
//qpsa_list_show(list);
		 				}
		 				else{
		 					// pripad | &E  |<|  + |   ===> &<E+
		 							if(token.name != RIGHTPAREN){
					 					newitem = psa_create_item();
										newitem->oper = OP_EXP;
										// vlozeni OP_EXP za TERM
					 					psa_list_push_after_item(list,item,newitem);
				 					}
				 					// vytvoreni itemu pro nacteny token
				 					newitem = psa_create_item();
				
									// OPER
									if(token.name == DIVISION_INT){
										// ma stejne precedencni hodnoty jako DIV, 
										// zajisteni spravne operace pri volani instrukce
										newitem->oper = OP_DIV;
									}
									else{
										newitem->oper = column;
									}

									// DATA_TYPE
									// urceni hodnoty vytvareneho noveho itemu, ktery vlozime na seznam
									if(token.name == INT_NUM){
										newitem->data_type = token.name;
									 	newitem->value.i = give_me_int(token.data);
									}
									else if(token.name == DOUBLE_NUM){
										newitem->data_type = token.name;
									 	newitem->value.d = give_me_double(token.data);
									}
									else if(token.name == STR){
									 	newitem->data_type = token.name;
										int len = strlen(token.data);

										if((newitem->value.string = malloc(len+1)) == NULL){
											return ALLOC_ERROR;
										}
										memcpy(newitem->value.string,token.data,len +1);
									}
									else if(token.name == ID){
									//TODO
										switch(var->type){
											case INTEGER: newitem->data_type = INT_NUM; break;
											case DOUBLE: newitem->data_type = DOUBLE_NUM; break;
											case STRING: newitem->data_type = STR; break;
											case BOOLEAN_: newitem->data_type = BL; break;
										}
									}

									// vlozeni TERMU
				 					psa_list_push(list,newitem);
//qpsa_list_show(list);
		 					}
		 			  }break;

/*        ---------  OPERACE > PSA ----------			*/

		 	case '>': {
//qprintf("PSA_OPERACE >:\n");	 			 
		 			 int i = 0;
		 			 // vytvorim si misto v pameti na ulozeni 3 itemu, ktere budu porovnavat s pravidly
		 			 aitem[0].oper = OP_EXP;
		 			 aitem[1].oper = OP_EXP;
		 			 aitem[2].oper = OP_EXP;
	
		 			 // POZOR usporadani aitemů: <|2|1|0|
					 item = psa_list_top(list);

		 			 // nacita z vrcholu dokud nenarazi na OP_EXP nebo OP_END
		 			 while((item->oper != OP_EXP)&&(item->oper != OP_END)){
		 			 	// nacetli jsme vice jak 3 TERMY
		 			 	if(i == 3){
		 			 		psa_list_delete(list);
		 			 		return SYN_A_ERROR;
		 			 	} 
		 			 	// ulozim si
		 			 	aitem[i].oper = item->oper;
		 			 	aitem[i].data_type = item->data_type;
		 			 	aitem[i].value = item->value;

		 			 	item = item->lptr;

//qprintf("POP %d\n",list->top->oper);
		 			 	psa_list_pop(list);
		 			 	i++;
		 			 }
		 			 if(item->oper == OP_END){
		 			 	// nenasel OP_EXP
		 			 	psa_list_delete(list);
		 			 	return SYN_A_ERROR;
		 			 }
		 			 else{
		 			 	// nasel se OP_EXP
		 			 	// vymazani OP_EXP
//qprintf("POP %d\n",list->top->oper);
		 			 	psa_list_pop(list);
		 			 }

//qprintf("NACTENE HODNOTY: |$|%d|%d|%d|\n",aitem[2].oper,aitem[1].oper,aitem[0].oper);

/*        ---------  VYHODNOCENI PRAVIDEL ----------			*/
					 
/*        ---------  i nebo (E) ----------			*/ 
		 			 if(((aitem[0].oper == OP_ID)&&(aitem[1].oper == OP_EXP)&&(aitem[2].oper == OP_EXP))||((aitem[0].oper == OP_RPARENT)&&(aitem[1].oper == OP_E)&&(aitem[2].oper == OP_LPARENT))){
//qprintf("VYHODNOCENI PRAVIDLA i->E | E->(E)\n");
		 			 	item = psa_create_item();
		 			 	if(aitem[0].oper == OP_ID){
		 			 		item->data_type = aitem[0].data_type;
		 			 	}
		 			 	else{
		 			 		item->data_type = aitem[1].data_type;
		 			 	}
						
						// vytvoreni OP_E
					    item->oper = OP_E;
					    // vlozeni OP_E do seznamu
			 		    psa_list_push(list,item);
//qpsa_list_show(list);
		 			 }
		 			 
/*        --------- E operator E ----------			*/ 
		 			 else if((aitem[0].oper == OP_E)&&((aitem[1].oper < 11)||(aitem[1].oper == 16))&&(aitem[2].oper == OP_E)){
//qprintf("VYHODNOCENI PRAVIDLA E->E operator E\n");	
						item = psa_create_item();
		 			 	// URCENI VYSLEDNEHO DATOVEHO TYPU
		 			 	// pokud je operator porovnavaci vraci BOOL
		 			 	if(aitem[1].oper > 3 && aitem[1].oper < 10){
		 			 		item->data_type = BL;
		 			 	}
		 			 	else{
		 			 		//pokud je asopn jeden operand double, bude vysledek v doublu
		 			 		if((aitem[0].data_type == DOUBLE_NUM)||(aitem[2].data_type == DOUBLE_NUM)){
		 			 			item->data_type = DOUBLE_NUM;
		 			 		}
		 			 		else{
		 			 			item->data_type = aitem[2].data_type;
		 			 		}
		 			 	}

		 			 	// pokud nejsou stejne datove typy operandu, prevedeme
		 			 	if(aitem[0].data_type != aitem[2].data_type){
		 			 		if(aitem[0].data_type == INT_NUM){
		 			 			aitem[0].data_type = DOUBLE_NUM;
		 			 			//aitem[0].value.d = int_to_double(aitem[0].value.i);
		 			 			//GENERATE CONVERT TODO
		 			 		}
		 			 		else if(aitem[2].data_type == INT_NUM){
		 			 			aitem[2].data_type = DOUBLE_NUM;
		 			 			//aitem[2].value.d = int_to_double(aitem[2].value.i);
		 			 			//GENERATE CONVERT TODO
		 			 		}
		 			 		// jeden z operandu je string, int ani double nejde prevest na string -> ERROR
		 			 		else{
		 			 			psa_list_delete(list);
		 			 			return SYN_A_ERROR;
		 			 		}
		 			 	}
		 			 	// datove typy jsou stejne
		 			 	else{
		 			 		// GENERATE INSTR
		 			 		// OPERACE
		 			 	}
		 			 	// vytvoreni OP_E
					    item->oper = OP_E;
					    // vlozeni OP_E do seznamu
			 		    psa_list_push(list,item);
		 			 }
/*        ---------  ZADNE ZE ZADANYCH PRAVIDEL NEBYLO NALEZENO  ----------			*/ 		 			 
		 			 else{
//printf("VYHODNOCENI PRAVIDLA - NEBYLO NALEZENO PRAVIDLO\n");	
		 			 	// ZADNE PRAVIDLO NEBYLO SPLNENO
		 			 	psa_list_delete(list);
printf("*****PSA ERROR*****\n");
		 			 	return SYN_A_ERROR;
		 			 }
	 			 
		 			  }break;
/*        ---------  SIGN " " ----------			*/ 		
		 	default:{
		 			psa_list_delete(list);
printf("*****PSA ERROR SIGN DOESNT EXIST*****\n");
		 			return SYN_A_ERROR;
		 			}break;
		 }
	}
}
