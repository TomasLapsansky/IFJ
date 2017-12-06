/**
 * @Name IFJ17 Syntakticka a sematicka analyza
 * @author Tomas Lapsansky (xlapsa00)
 * @file parser.h
 * @date 15.11.2017
 */

#include "scanner.h"
#include "structs.h"
#include "symtable.h"
#include "psa.h" 
#include "tstack.h"
#include "string.h"

int declare(TOKEN idToken);
int declare_define(void);

void gener_fce(void);

//KA pre syntakticku analyzu
int parser(void);

int p_start(void);
int p_scope(void);
int p_define(void);
int p_body(tRetData *funcData);

int p_type(void);

int p_parameter(tRetData *funcData, int *pocet_parametrov);
int p_nextparameter(tRetData *funcData, int *pocet_parametrov);

int p_declare_parameter(char* funcName);
int p_declare_nextparameter(char* funcName);

int p_vparameter(tRetData *funcData, int *pocet_parametrov);
int p_vnextparameter(tRetData *funcData, int *pocet_parametrov);

int p_prikaz(tRetData *funcData);
int p_priradenie(int type, char *name);
int p_print(void);
int p_nextprint(void);
