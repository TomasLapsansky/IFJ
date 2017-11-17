/**
 * @Name IFJ17 Syntakticka a sematicka analyza
 * @author Tomas Lapsansky (xlapsa00)
 * @file parser.h
 * @date 15.11.2017
 */

//KA pre syntakticku analyzu
int parser(void);

int p_start(void);
int p_scope(void);
int p_declare(void);
int p_body(void);

int p_type(void);

int p_parameter(void);
int p_nextparameter(void);
int p_vparameter(void);
int p_vnextparameter(void);

int p_prikaz(void);
int p_priradenie(void);
int p_print(void);
int p_nextprint(void);

int p_vyraz(void);		//TODO
