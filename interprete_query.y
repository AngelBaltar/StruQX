/* StruQX - SQL XML DATABASE
 * interprete_query.y
 * Copyright (C)  Angel Baltar Diaz
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>

#include "interprete_query.tab.h"
#include "tipos_basicos.h"
#include "lib_utils.h"
#include "CommandLine/CommandLine.h"
#include "Debug/StruQXDebug.h"
#include "MessagePrinters/HelpPrinter.h"


tipo_query query;
tipo_entrada entrada;
unsigned int Busca(void);
unsigned int Source(void);
unsigned int Borra(void);
unsigned int sys_call(void);
unsigned int func_nop(void);
struct request_operation
{
	unsigned int (*funcion)(void);
};
static const struct request_operation funciones[]={{Busca},{Source},{Source},{Borra},{sys_call},{func_nop}};
static void (*func_error_help)(void)=general_help;
static char cad_error[MAX_DAT];
#define FUNC_NONE	6
#define FUNC_BUSC	0
#define FUNC_SOURCE	1
#define FUNC_EXIT_SRC	2
#define FUNC_DEL	3
#define FUNC_SYS	4
#define FUNC_NOP	5
unsigned char flag_func=FUNC_NONE;
char path_busqueda[MAX_DAT];

const char *prompt="StruQX>";

void (*operacion_registro)(tipo_entrada *ent);
void inserta_entrada(char *entr,tipo_entrada *e,unsigned short tipo);
void inserta_esquema(tipo_entrada *e);
void inserta_fila(tipo_entrada *e);


void yyerror (char const *s)
{
	unsigned int d=get_par_der(),i=get_par_izq();
	if(i>d)
		printf("Falta parentesis derecho ");
	if(d>i)
		printf("Falta parentesis izquierdo ");
	reset_par();
	printf("%s\n",s);
	func_error_help();
	func_error_help=general_help;
	query.flags|=FLAG_ERROR;
	return;
}

%}
%union {
	struct
	{
	int tipo_int;
	char * tipo_string;
	}tipo;
}


%token <tipo>TAG_XML
%token <tipo>TAG_GENERICO
%token <tipo>CIERRE_TAG_GENERICO

%token <tipo>SELECT
%token <tipo>ASIGN
%token <tipo>CREATE
%token <tipo>EXIT
%token <tipo>SOURCE
%token <tipo>DROP
%token <tipo>ORDER
%token <tipo>BY
%token <tipo>PAGE
%token <tipo>WHERE
%token <tipo>FROM
%token <tipo>ROOT
%token <tipo>NODE
%token <tipo>ATTRIBUTES
%token <tipo>INSERT
%token <tipo>DELETE
%token <tipo>SYSTEM
%token <tipo>PATH_XML
%token <tipo>ESPS
%token <tipo>VAL_TXT
%token <tipo>LITERAL
%token <tipo>ID
%token <tipo>PNT_COMA
%token <tipo>PNT
%token <tipo>COMA
%token <tipo>MAYOR
%token <tipo>MENOR
%token <tipo>MAYOR_EQ
%token <tipo>MENOR_EQ
%token <tipo>EQ
%token <tipo>NEQ
%token <tipo>PAR_DER
%token <tipo>PAR_IZQ
%token <tipo> NEGAR
%token <tipo> AND
%token <tipo> OR
%token 	<tipo> LEX_ERROR
%type	<tipo>	val
%type	<tipo>	val_gen
%type	<tipo>	general_error
%type	<tipo>	error
%start S
%%
S : lista_query {}
  |TAG_XML esp_opc TAG_GENERICO lista_filas esp_opc CIERRE_TAG_GENERICO esp_opc	{		if(!comprueba_esquema(path_busqueda,RAIZ,$3.tipo_string))
												{
													sprintf(cad_error,"tag raiz <%s> no coincide con lo esperado",$3.tipo_string);
													func_error_help=xml_help;
													yyerror(cad_error);
													return;
												}
												if(strcmp($3.tipo_string,$6.tipo_string)!=0)
												{
													sprintf(cad_error,"tag raiz no coinciden apertura <%s> y cierre </%s>",$3.tipo_string,$6.tipo_string);
													func_error_help=xml_help;
													yyerror(cad_error);
													return;
												}
									}
;
lista_filas:lista_filas esp_opc TAG_GENERICO lista_vars esp_opc CIERRE_TAG_GENERICO	{	if(!comprueba_esquema(path_busqueda,NODO,$3.tipo_string))
												{
													sprintf(cad_error,"tag nodo <%s> no coincide con lo esperado",$3.tipo_string);
													func_error_help=xml_help;
													yyerror(cad_error);
													return;
												}
										
												if(strcmp($3.tipo_string,$6.tipo_string)!=0)
												{
													sprintf(cad_error,"tag_nodo no coinciden apertura <%s> y cierre </%s>",$3.tipo_string,$6.tipo_string);
													func_error_help=xml_help;
													yyerror(cad_error);
													return;
												}
												operacion_registro(&entrada);
												inicializa_entrada(&entrada);}
	|/*vacio*/
	|general_error							{func_error_help=xml_help;yyerror(cad_error);return;}
;
lista_vars: lista_vars esp_opc TAG_GENERICO val_gen CIERRE_TAG_GENERICO	{
										if(!comprueba_esquema(path_busqueda,ATRIB,$3.tipo_string))
										{
											sprintf(cad_error,"tag atributo <%s> no coincide con lo esperado",$3.tipo_string);
											func_error_help=xml_help;
											yyerror(cad_error);
											return;
										}
										if(strcmp($3.tipo_string,$5.tipo_string)!=0)
										{
											sprintf(cad_error,"tag atributo no coinciden apertura <%s> y cierre </%s>",$3.tipo_string,$5.tipo_string);
											func_error_help=xml_help;
											yyerror(cad_error);
											return;
										}
									inserta_entrada($4.tipo_string,&entrada,T_FILA);
									inserta_entrada($3.tipo_string,&entrada,T_FILA);}
	|/*vacio*/
	|general_error							{func_error_help=xml_help;yyerror(cad_error);return;}
;
val_gen:ID
	|VAL_TXT
	|ID ESPS val_gen	{$$.tipo_string=malloc(sizeof(char)*(strlen($1.tipo_string)+strlen($2.tipo_string)+strlen($3.tipo_string)+1));$$.tipo_string[0]=0;strcat($$.tipo_string,$1.tipo_string);strcat($$.tipo_string,$2.tipo_string);strcat($$.tipo_string,$3.tipo_string);}
	|VAL_TXT ESPS val_gen	{$$.tipo_string=malloc(sizeof(char)*(strlen($1.tipo_string)+strlen($2.tipo_string)+strlen($3.tipo_string)+1));$$.tipo_string[0]=0;strcat($$.tipo_string,$1.tipo_string);strcat($$.tipo_string,$2.tipo_string);strcat($$.tipo_string,$3.tipo_string);}
;
lista_query:lista_query esp_opc query           {printf("\n%s",prompt);}
	|/*vacio*/                      /*{printf("\n%s",prompt);}*/
;
query : seleccion ESPS origen clausulas_opc PNT_COMA  {unsigned int i=comprueba_seleccion(&query);
							if(i!=query.tam_sel)
							{
								char cad[MAX_DAT];
								snprintf(cad,MAX_DAT,"el atributo %s no es parte de los ficheros especificados",query.lista_seleccion[i]);
								yyerror(cad);
								return;
							}
							flag_func=FUNC_BUSC;
                                                        return;}
	|CREATE ESPS PATH_XML esp_opc PAR_IZQ esp_opc
		ROOT esp_opc ID esp_opc COMA esp_opc NODE esp_opc ID esp_opc COMA esp_opc ATTRIBUTES esp_opc ID lista_atrs PAR_DER PNT_COMA	{printf("aki");
												inserta_entrada($21.tipo_string,&entrada,T_ESQUEMA);
												inserta_entrada($15.tipo_string,&entrada,T_ESQUEMA);
												inserta_entrada($9.tipo_string,&entrada,T_ESQUEMA);
												inserta_entrada($3.tipo_string,&entrada,T_ESQUEMA);												
																							
												inserta_esquema(&entrada);
												inicializa_entrada(&entrada);}
	|CREATE general_error							{func_error_help=create_help;yyerror(cad_error);return;}

	|SYSTEM ESPS LITERAL PNT_COMA			{inserta_entrada($3.tipo_string,&entrada,T_ESQUEMA);flag_func=FUNC_SYS;return;}

	|SYSTEM general_error				{func_error_help=system_help;yyerror(cad_error);return;}

	|INSERT esp_opc PATH_XML esp_opc PAR_IZQ esp_opc ID ASIGN val lista_asign PAR_DER PNT_COMA
												{
													inserta_entrada($7.tipo_string,&entrada,T_FILA);
													inserta_entrada($9.tipo_string,&entrada,T_FILA);
													inserta_entrada($3.tipo_string,&entrada,T_FILA);
													imprime_entrada(&entrada);	
													inserta_fila(&entrada);
													inicializa_entrada(&entrada);
												}

	|INSERT general_error							{func_error_help=insert_help;yyerror(cad_error);return;}

	|DELETE ESPS origen condicion PNT_COMA							{flag_func=FUNC_DEL;return;}

	|DELETE general_error							{func_error_help=delete_help;yyerror(cad_error);return;}

	|DROP ESPS PATH_XML PNT_COMA						{printf("%i\n",elimina_esquema($3.tipo_string));}
	
	|DROP general_error							{func_error_help=drop_help;yyerror(cad_error);return;}

	|SOURCE ESPS val_gen PNT_COMA								{inserta_entrada($3.tipo_string,&entrada,T_FILA);
												flag_func=FUNC_SOURCE;return;}

	|SOURCE general_error							{func_error_help=source_help;yyerror(cad_error);return;}

	|EXIT ESPS SOURCE PNT_COMA						{flag_func=FUNC_EXIT_SRC;return;}
	|EXIT PNT_COMA								{exit(0);}
;
lista_atrs:lista_atrs esp_opc COMA esp_opc ID	{inserta_entrada($5.tipo_string,&entrada,T_ESQUEMA);}
	|/*vacio*/
;
lista_asign:lista_asign esp_opc COMA esp_opc ID ASIGN val	{inserta_entrada($5.tipo_string,&entrada,T_ESQUEMA);
							inserta_entrada($7.tipo_string,&entrada,T_ESQUEMA);
							}
	|/*vacio*/
;
seleccion:SELECT ESPS ID lista_sel 	{/*printf("%s\n",$3.tipo_string);*/inserta_seleccion(&query,$3.tipo_string);}
	|general_error			{func_error_help=select_help;yyerror(cad_error);return;}
;		
lista_sel:lista_sel COMA ID		{inserta_seleccion(&query,$3.tipo_string);}
	|/*vacio*/
		
;
origen: FROM ESPS PATH_XML lista_origen	{inserta_origen(&query,$3.tipo_string);/*printf("origen completado %s\n",$3.tipo_string);*/}

	|general_error			{func_error_help=from_help;yyerror(cad_error);return;}
;
lista_origen:lista_origen COMA PATH_XML {inserta_origen(&query,$3.tipo_string);}
	|/*vacio*/
;
clausulas_opc:condicion		
		|order
		|bypage		
		|condicion order
		|condicion bypage
		|order bypage
		|condicion order bypage
		|/*vacio*/	
;
condicion:ESPS WHERE ESPS  cond{/*printf("condicion completada\n");*/}
	|general_error		{func_error_help=cond_help;yyerror(cad_error);return;}
;
cond:val MAYOR val					{inserta_condicion(&query,$1.tipo_string,$3.tipo_string,$2.tipo_int);}
	| val MENOR val					{inserta_condicion(&query,$1.tipo_string,$3.tipo_string,$2.tipo_int);}
	| val MAYOR_EQ val				{inserta_condicion(&query,$1.tipo_string,$3.tipo_string,$2.tipo_int);}
	| val MENOR_EQ val				{inserta_condicion(&query,$1.tipo_string,$3.tipo_string,$2.tipo_int);}
	| val EQ val					{inserta_condicion(&query,$1.tipo_string,$3.tipo_string,$2.tipo_int);}
	| val NEQ val					{inserta_condicion(&query,$1.tipo_string,$3.tipo_string,$2.tipo_int);}
	|PAR_IZQ cond PAR_DER
	|NEGAR cond					{inserta_connector(&query,$1.tipo_int);}
	|PAR_IZQ cond AND cond PAR_DER			{inserta_connector(&query,$3.tipo_int);}
	|PAR_IZQ cond OR cond PAR_DER			{inserta_connector(&query,$3.tipo_int);}
	|general_error					{func_error_help=cond_help;yyerror(cad_error);return;}
;
order:ESPS ORDER ESPS BY ESPS ID			{
								if(!inserta_order(&query,$6.tipo_string))
								{func_error_help=order_help;yyerror(cad_error);return;}
							}
	| ESPS ORDER general_error					{func_error_help=order_help;yyerror(cad_error);return;}
;
bypage:ESPS BY ESPS PAGE				{query.flags|=FLAG_BYPAGE;}
	| ESPS BY general_error					{func_error_help=bypage_help;yyerror(cad_error);return;}
;

val: ID	{	}
	|LITERAL
;
esp_opc:ESPS
	|/*vacio*/
;
general_error:error	{snprintf(cad_error,MAX_DAT,"no se reconoce %s en este punto",$1.tipo_string);}
		|LEX_ERROR	{snprintf(cad_error,MAX_DAT,"no se reconoce %s en este punto",$1.tipo_string);}
;
%%


/*
 *inserts one row into the file, all its specified in the entry e
 */
void inserta_fila(tipo_entrada *e)
{
	int i;
	DEBUG(
                printf("inserting row into %s\n",e->lista[0]);fflush(stdout);
                );
	FILE *f_xml=fopen(e->lista[0],"r+b");
        if(!f_xml){
            printf("can not insert into %s no such file\n",e->lista[0]);
            return;
        }
	tipo_entrada t;
	t.lista=NULL;
	inicializa_entrada(&t);
	t.tam_l=0;	
	if(lee_esquema(e->lista[0],&t)==0){printf("no existe %s\n",e->lista[0]);return;}
	DEBUG(
                imprime_entrada(&t);
        );
        //SEEK TO THE END OF THE FILE SUBSTRACTING THE LAST CLOSE TAG
	i=fseek(f_xml,(long)(strlen(t.lista[t.tam_l-2])+3)*(-1),SEEK_END);
	//printf("posicionando final + %i %s\n",(long)(strlen(t.lista[t.tam_l-2])+3)*(-1),t.lista[t.tam_l-2]);
	
        fprintf(f_xml,"\n\t<%s>\n",t.lista[t.tam_l-1-2]);	
	for(i=1;i<e->tam_l-1;i+=2)
		fprintf(f_xml,"\t\t<%s>%s</%s>\n",e->lista[i+1],e->lista[i],e->lista[i+1]);
	fprintf(f_xml,"\t</%s>\n</%s>",t.lista[t.tam_l-1-2],t.lista[t.tam_l-1-1]);	
	fclose(f_xml);
}

unsigned char evalua_condicion_simple(tipo_condicion *cond,tipo_entrada *ent)
{
	char  cond_id1[MAX_DAT];
	char  cond_id2[MAX_DAT];
	snprintf(cond_id1,MAX_DAT,"%s",cond->val1);
	snprintf(cond_id2,MAX_DAT,"%s",cond->val2);
	//printf("comparando1 %s con %s\n",cond_id1,cond_id2);
	int i,d1=0,d2=0;	
	for(i=0;i<ent->tam_l-1;i+=2)
	{
		if((!d1)&&(strcmp(cond_id1,ent->lista[i])==0))
		{
			snprintf(cond_id1,MAX_DAT,"%s",ent->lista[i+1]);
			d1=1;
		}

		if((!d2)&&(strcmp(cond_id2,ent->lista[i])==0))
		{
			snprintf(cond_id2,MAX_DAT,"%s",ent->lista[i+1]);
			d2=1;
		}
		if((d1) && (d2))
			break;
	}
	/*if(!d1)
	{
		cond_id1[strlen(cond_id1)-1]=0;
		cond_id1++;
	}
	if(!d2)
	{
		cond_id2[strlen(cond_id2)-1]=0;
		cond_id2++;
	}*/
	//printf("comparando %s con %s\n",cond_id1,cond_id2);
	//int dev=1;	
	switch(cond->cmp)
	{
		 case CMP_LT:{return(cad_comp(cond_id1,cond_id2)<0);}
		 case CMP_EQ:{return(cad_comp(cond_id1,cond_id2)==0);}
		 case CMP_GT:{return(cad_comp(cond_id1,cond_id2)>0);}
		 case CMP_LEQ:{return(cad_comp(cond_id1,cond_id2)<=0);}
		 case CMP_GEQ:{return(cad_comp(cond_id1,cond_id2)>=0);}
		 case CMP_NEQ:{return(cad_comp(cond_id1,cond_id2)!=0);}
	}
	//printf("devolviendo %i\n",dev);
	//free(cond_id1);free(cond_id2);		
	return 1;
}
unsigned char evalua_condicion_completa(tipo_query *q__,tipo_entrada *ent)
{
	//printf("evaluando condicion\n");fflush(stdout);
	if(q__->tam_wh==0)
		return 1;
	int j=0,i=0,k;
	unsigned int dev=1;
	unsigned char error;
	//printf("aqui\n");fflush(stdout);
	tipo_query *q=malloc(sizeof(tipo_query));
	copy_query(q,*q__);
	//printf("aqui2\n");fflush(stdout);
	//imprime_query(q);
	if(q->tam_wh==1)
	{
		dev=evalua_condicion_simple(&q->where[0],ent);
		free(q);
		return dev;
	}
	tipo_condicion verdadero;
	verdadero.cmp=CMP_EQ;
	verdadero.val1="a";
	verdadero.val2="a";
	verdadero.connector=CNN_NONE;
	
	tipo_condicion falso;
	falso.cmp=CMP_EQ;
	falso.val1="a";
	falso.val2="ba";
	falso.connector=CNN_NONE;
	//printf("aqui3\n");fflush(stdout);
	while(q->tam_wh>0)
	{
		while((q->where[j].connector==CNN_NONE)&&(j<q->tam_wh))j++;
		//printf("J %i\n",j);		
		if(j>=q->tam_wh)
		{//printf("2dev %i\n",dev);
			free(q);
			return dev;
		}
		switch(q->where[j].connector)
		{
			case CNN_AND:{
					//printf("AND %i\n",j);fflush(stdout);	
					//printf("aqui4\n");fflush(stdout);
					dev=1;		
					i=j-2;
					for(k=j-2;k<j;k++)
					{
						if(dev)
						{
							error=evalua_condicion_simple(&q->where[i],ent);
							//printf("aqui4.2\n");fflush(stdout);
							if(error==50)
							{
								free(q);
								return error;
							}
							dev=((dev)&&(error));
						}
						borra_where(q,i);
						//printf("aqui4.5\n");fflush(stdout);
						//imprime_query(q);
					}
					//printf("aqui5\n");fflush(stdout);
					borra_where(q,i);
					if(dev)
						inserta_where(q,verdadero,i);
					else
						inserta_where(q,falso,i);
					//i=j+1;
					j=0;
					//imprime_query(q);
					//printf("evaluando and %i\n",i);	
					//printf("aqui6\n");fflush(stdout);				
					break;}
			case CNN_OR:{
					//printf("OR %i\n",j);fflush(stdout);	
					dev=0;	
					i=j-2;		
					for(k=j-2;k<j;k++)
					{
						if(!dev)
						{
							error=evalua_condicion_simple(&q->where[i],ent);
							if(error==50)
							{
								free(q);
								return error;
							}
							dev=((dev)||(error));
						}
						borra_where(q,i);
					}
					borra_where(q,i);
					if(dev)
						inserta_where(q,verdadero,i);
					else
						inserta_where(q,falso,i);
					//i=j+1;
					j=0;
					//imprime_query(q);
					//printf("evaluando and %i\n",i);					
					break;}
			case CNN_NO:{
					error=evalua_condicion_simple(&q->where[j-1],ent);
					if(error==50)
					{
						free(q);
						return error;
					}
					//if(i==j-1)
					//	dev=(evalua_condicion_simple(&q->where[i],emp)==0);					
					//else
					borra_where(q,j-1);
					borra_where(q,j-1);
					//imprime_query(q);
					dev=(error==0);
					//printf("evaluando not %i\n",dev);
					j=0;
					break;}	
			default:{free(q);return dev;}
		}
	}
	free(q);
	return dev;
}
static tipo_entrada resultados;
static tipo_entrada res_cartesianos[MAX_DAT];
/*
 * Extracts the selected atributs for the entry ent into the results for the actual query
 */
void extrae_atributos(tipo_entrada *ent,tipo_entrada *resultado_act)
{
	//printf("resultado act :%x\n",resultado_act);fflush(stdout);
	resultado_act->tam_l=0;
	resultado_act->lista=NULL;	
	inicializa_entrada(resultado_act);
	int i,j;
        for(i=0;i<query.tam_sel;i++)
        {
                //snprintf(cad,MAX_DAT,"%s",query.lista_seleccion[i]);
                //#pragma omp for
                for(j=0;j<ent->tam_l-1;j+=2)
                {
                        if(strcmp(query.lista_seleccion[i],ent->lista[j])==0)
                                inserta_entrada(ent->lista[j+1],resultado_act,T_FILA);	
                }
        }
}

/*
 * Processes join file
 */
void procesa_fila_cartesiano(tipo_entrada *ent)
{
        //RES CARTESIANOS CONTAINS RESULTS FOR FROM N IN POSITION N OF THE ARRAY
        //THE N POSITION CONTAINS DE JOIN WITH 0 TO N position, SO THE LAST
        //POSITION CONTAINS THE TOTAL JOIN, AND AT THAT TIME WE CAN EVALUATE THE
        //CONDITION FOR THE QUERY
	//printf("PROCESANDO FILA\n");fflush(stdout);imprime_entrada(ent);//imprime_query(&query);
	
        static unsigned char list_act=0;
	static char ultimo_path[MAX_DAT];
	if(strcmp(path_busqueda,query.lista_from[0])==0)
		list_act=0;
	
	if((!list_act)&&(strcmp(ultimo_path,path_busqueda)&&(res_cartesianos[0].sig!=NULL)))
		list_act++;

	//if(strcmp(ent->lista[ent->tam_l-1],"600")==0)
	//	{printf("siiiiiiiiii OSTIA\n");}
	snprintf(ultimo_path,MAX_DAT,"%s",path_busqueda);
	tipo_entrada *resultado_act;
	resultado_act=malloc(sizeof(tipo_entrada));
	resultado_act->tam_l=0;
	resultado_act->lista=NULL;
	int i;
	for(i=ent->tam_l-1;i>=0;i--)
		inserta_entrada(ent->lista[i],resultado_act,T_FILA);	
	
	if(list_act)
	{
		tipo_entrada *act;
		act=res_cartesianos[list_act-1].sig;
		tipo_entrada *fusionada;
		
		while(act!=NULL)//no se puede hacer asi, hay que cojer la de la lista,
				//fusionarla con la actual surjiendo otra nueva,
				//eliminar la vieja de la lista y meter la nueva
		{
			fusionada=malloc(sizeof(tipo_entrada));
			fusionada->tam_l=0;
			fusionada->lista=NULL;	
			inicializa_entrada(fusionada);
			//imprime_entrada(act);
			//if(strcmp(act->lista[act->tam_l-1],"600")==0)
			//		{printf("SI\n");}			
			fusiona_entradas(fusionada,*act,*ent);
			act=act->sig;
			//printf("akii\n");
			if(list_act==query.tam_fr-1)
			{
				//imprime_query(&query);
				if(evalua_condicion_completa(&query,fusionada))
				{
					resultado_act=malloc(sizeof(tipo_entrada));
					resultado_act->tam_l=0;
					resultado_act->lista=NULL;;
					extrae_atributos(fusionada,resultado_act);
					//imprime_entrada(resultado_act);
					//printf("%i\n",list_act);
					inserta_lista_entradas(resultado_act,&res_cartesianos[list_act],query.order);//printf("entra\n");
					//if(strcmp(resultado_act->lista[resultado_act->tam_l-1],"600")==0)
					//{printf("si\n");}
				}
				//else
				//	printf("no entra\n");
			}
			else
			{
				inserta_lista_entradas(fusionada,&res_cartesianos[list_act],query.order);
			}
		}
	}
	else
	{
		inserta_lista_entradas(resultado_act,&res_cartesianos[list_act],255);
		//if(strcmp(resultado_act->lista[resultado_act->tam_l-1],"600")==0)
		//{printf("siiiiiiiiii\n");}		
	}
}

/**
 *Searching process for one row, insert it if condition matches
 */
void procesa_fila_busqueda(tipo_entrada *ent)
{

	//printf("PROCESANDO FILA\n");fflush(stdout);imprime_entrada(ent);//imprime_query(&query);
	if(!evalua_condicion_completa(&query,ent))
		{/*printf("NO CUMPLE\n");*/return;}
	
	tipo_entrada *resultado_act=malloc(sizeof(tipo_entrada));
	//printf("resultado act :%x\n",resultado_act);fflush(stdout);
	resultado_act->tam_l=0;
	resultado_act->lista=NULL;	
	inicializa_entrada(resultado_act);	
	//imprime_entrada(ent);
	extrae_atributos(ent,resultado_act);
	//printf("INSERTANDO ENTRADA1\n");fflush(stdout);
	inserta_lista_entradas(resultado_act,&resultados,query.order);
	//printf("INSERTANDO ENTRADA2\n");fflush(stdout);
	//imprime_entrada(resultado_act);
}

/*
 * process a row deleting files, insert new file if the condition does not mach
 * if the condition machs, will not insert so row will be deleted
 */
void procesa_fila_borrado(tipo_entrada *ent)
{
	if(evalua_condicion_completa(&query,ent))
		{/*printf("NO CUMPLE\n");*/return;}
	tipo_entrada ent_brr;
	ent_brr.tam_l=0;
	ent_brr.lista=NULL;
	inicializa_entrada(&ent_brr);
	int i;
	for(i=0;i<ent->tam_l;i++)
		inserta_entrada(ent->lista[i],&ent_brr,T_FILA);
	inserta_entrada(path_busqueda,&ent_brr,T_FILA);			
	
	inserta_fila(&ent_brr);
	DEBUG(
                imprime_entrada(&ent_brr);
                printf("no borrado\n");
        );
}

/*
 * Searching function for joins
 */
unsigned int Busca_cartesiano(void)
{
	//printf("busqueda sobre varios documentos no implementada\n");
	FILE * xml_fich;
	int i;
	if(query.tam_fr==1)
		operacion_registro=procesa_fila_busqueda;
	else
		operacion_registro=procesa_fila_cartesiano;
	inicializa_entrada(&resultados);
	#pragma omp for
	for(i=0;i<MAX_DAT;i++)
		inicializa_entrada(&res_cartesianos[i]);
	for(i=0;i<query.tam_fr;i++)
	{	//printf("for\n");
		xml_fich=fopen(query.lista_from[i],"r");

		snprintf(path_busqueda,MAX_DAT,"%s",query.lista_from[i]);
		
		yyrestart(xml_fich);
	
		inicializa_entrada(&entrada);
		yyparse();
	//	printf("buscando11 %i %s\n",query.tam_fr,path_busqueda);fflush(stdout);
		fclose(xml_fich);
		//printf("aki");fflush(stdout);
	}
	//resultados=res_cartesianos[query.tam_fr-1];
	yyrestart(stdin);
	if((query.flags&FLAG_ERROR)==0)	
		imprime_resultado_query(&res_cartesianos[query.tam_fr-1],&query);
	
	
	for(i=0;i<query.tam_fr;i++)
		elimina_lista_entradas(&res_cartesianos[i]);
}

/**
 * 
 * Main function for Deleting
 */
unsigned int Borra(void)
{
	DEBUG(
                printf("borrando\n");
        );
	imprime_query(&query);
	int renameFile=rename(query.lista_from[0],"auxiliar.xml");
	if(renameFile)
		{printf("error renaming %s \n",query.lista_from[0]);return;}
	FILE  *xml_fich=fopen("auxiliar.xml","r");
	if(xml_fich==NULL)
		{printf("error opening the file auxiliar.xml\n");return;}
	operacion_registro=procesa_fila_borrado;
	snprintf(path_busqueda,MAX_DAT,"%s",query.lista_from[0]);
	
        //IT NECESARY TO INSERT NEW SCHEMA FOR THE TABLE
        //BECAUSE DELETE IS IMPLEMENTED AS RENAME AND REINSERT NON DELETEDS
	tipo_entrada entr_sch;
	entr_sch.tam_l=0;entr_sch.lista=NULL;
	inicializa_entrada(&entr_sch);
	lee_esquema(query.lista_from[0],&entr_sch);

	DEBUG(
                imprime_entrada(&entr_sch);
        );
        
        //LETS CREATE NEW XML FILE REMEBER WE RENAMED THE OLDER
        DEBUG(printf("creating file %s\n",entr_sch.lista[entr_sch.tam_l-1]));
        FILE *new_xml=fopen(entr_sch.lista[entr_sch.tam_l-1],"w");
	fprintf(new_xml,"<?xml version=\"1.0\"?>\n");
	fprintf(new_xml,"<%s>\n</%s>",entr_sch.lista[entr_sch.tam_l-2],entr_sch.lista[entr_sch.tam_l-2]);
	fclose(new_xml);
	
 //       return;
	yyrestart(xml_fich);
	inicializa_entrada(&entrada);
	yyparse();
	yyrestart(stdin);
	fclose(xml_fich);
	remove("auxiliar.xml");

	//elimina_lista_entradas(&resultados);
}

/*
 * Main function for executing searching Querys
 */
unsigned int Busca(void)
{
	int i;
//imprime_query(&query);
	printf("Buscando:\n");
	imprime_query(&query);
	//yyrestart(stdin);
	//return;
	FILE * xml_fich;
	if (query.tam_fr>1)
	{
		Busca_cartesiano();
		return;
	}
	else
	{
		xml_fich=fopen(query.lista_from[0],"r");
		operacion_registro=procesa_fila_busqueda;
		snprintf(path_busqueda,MAX_DAT,"%s",query.lista_from[0]);
	}
	if(xml_fich==NULL)
		{printf("error abriendo el fichero\n");return;}
	//printf("buscando\n");fflush(stdout);
	yyrestart(xml_fich);
	//int d=yylex();	
	//while(d){printf("%i\n",d);d=yylex();}
	inicializa_entrada(&entrada);
	inicializa_entrada(&resultados);
	yyparse();
	//printf("buscando11\n");fflush(stdout);
	yyrestart(stdin);
	fclose(xml_fich);
	//printf("aki");fflush(stdout);
	
	if((query.flags&FLAG_ERROR)==0)
	{
		imprime_resultado_query(&resultados,&query);
		//printf("flags %i",query.flags&FLAG_ERROR);
	}
	elimina_lista_entradas(&resultados);
}

/*
 * function for parsing a source file containing StruQX-SQL
 */
unsigned int Source(void)
{
	static FILE * src_fich;
	switch(flag_func)
	{
		case FUNC_SOURCE:{
					src_fich=fopen(entrada.lista[0],"r");
					if(src_fich==NULL){printf("fichero source %s no encontrado\n",entrada.lista[0]);return;}
					yyrestart(src_fich);
					return;
				}
		case FUNC_EXIT_SRC:{fclose(src_fich);yyrestart(stdin);return;}
		default:{return;}
	}
}

/**
 * function for system call
 */
unsigned int sys_call(void)
{
	int a;
	if(entrada.tam_l==1)
		a=system(entrada.lista[0]);
}

/*
 * function for no operation
 */
unsigned int func_nop(void)
{
	return 1;
}
int main(int argc,char **argv) {
	
	int i;
	struct timeval t0, t1, t; 
	inicializa_query(&query);
	inicializa_entrada(&entrada);
	inicializa_entrada(&resultados);
        
        parse_arguments(argc,argv);
        
	printf("%s",prompt);
	for(;;)
	{	
		//printf("aki1");fflush(stdout);
		//yyrestart();
		yyparse();
		if(flag_func>=FUNC_NONE)
		{
			//printf("error sintáctico\n");
			yyrestart(stdin);
		}
		else
		{		
			printf("Query reconocida %i\n",flag_func);fflush(stdout);
			assert (gettimeofday (&t0, NULL) == 0);		
			funciones[flag_func].funcion();
			assert (gettimeofday (&t1, NULL) == 0);
			timersub(&t1, &t0, &t);
			printf ("\nEn %ld:%ld(seg:mseg)\n", t.tv_sec, t.tv_usec/1000);
		}
		flag_func=FUNC_NONE;	
		inicializa_query(&query);
		inicializa_query(&query);
		inicializa_entrada(&entrada);
		inicializa_entrada(&resultados);
		printf("%s",prompt);
	}
}

