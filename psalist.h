#ifndef PSAlist
#define PSAlist

enum oper{
	OP_MUL,     	// *	0
	OP_DIV,     	// /	1
	OP_ADD,     	// +	2
	OP_MINUS,    	// -	3
	OP_LESSER,     	// <	4
	OP_GREATER,    	// >	5
	OP_LESSEREQUAL, // <=	6
	OP_GREATEREQUAL,// >=	7
	OP_EQUAL,    	// =	8
	OP_NOTEQUAL,    // <>	9
	OP_LPARENT,     // (	10
	OP_RPARENT,     // )	11
	OP_ID,    		// i    12
	OP_END,     	// $    13
	OP_E,  			// E    14
	OP_EXP,   	 	// < znak 15
	OP_DIV_INT, 	// celo ciselne deleni 16
};

typedef struct psa_item{
	char name[50];
	int data_type; //11-INT 12-DOUBLE 13-STRING 14-BL
	union{
		int i;
		double d;
		char *string;
		void *ptr;
	}value;

	int oper;
	struct psa_item *lptr;
	struct psa_item *rptr;
}psa_item;

typedef struct{
	psa_item *top;
}psa_list;

int give_me_int(char *data);
double give_me_double(char *data);
int double_to_int(double d);
double int_to_double(int i);
psa_list *psa_list_init();
void psa_list_pop(psa_list *list);
void psa_list_delete(psa_list *list);
int psa_list_push(psa_list *list,psa_item *item);
int psa_list_push_after_item(psa_list *list,psa_item *item,psa_item *newitem);
psa_item *psa_list_top(psa_list *list);
psa_item *psa_create_item();
psa_item *psa_search_term(psa_list *list);
void psa_list_show(psa_list *list);
#endif
