/**
 * @Name IFJ17 Syntakticka a sematicka analyza
 * @author Tomas Lapsansky (xlapsa00)
 * @file parser.h
 * @date 15.11.2017
 */ 

#include "ts.h"

//KA pre syntakticku analyzu
int parser(void);

int p_start(void);
int p_scope(void);
int p_declare(void);
int p_body(void);

int p_type(void);

int p_parameter(tRetData fIdData);
int p_nextparameter(void);

int p_declareparameter(char *fID);
int p_decnextparameter(char *fID);

int p_vparameter(tRetData *fIdData);
int p_vnextparameter(tRetData *fIdData);

int p_prikaz(void);
int p_priradenie(int type);
int p_print(void);
int p_nextprint(void);

int id(tRetData *retData);

int p_vyraz(int type);		//TODO	->type = ENUM
