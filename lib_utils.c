/* StruQX - SQL XML DATABASE
 * lib_utils.c
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos_basicos.h"
#include "lib_utils.h"
#include "MessagePrinters/TermPrintFormats.h"

/**
 * initializes a query
 * @param q the query
 */
void inicializa_query(tipo_query *q)
{
	int i;
	//if(q->where!=NULL)	
	//	free(q->where);
	if(q->lista_seleccion!=NULL)
	{
		for(i=0;i<q->tam_sel;i++)
		{
			if(q->lista_seleccion[i]!=NULL)
			{
				free(q->lista_seleccion[i]);
				q->lista_seleccion[i]=NULL;
			}
		}
		free(q->lista_seleccion);
		q->lista_seleccion=NULL;
	}
	if(q->lista_from!=NULL)
	{
		for(i=0;i<q->tam_fr;i++)
		{
			if(q->lista_from[i]!=NULL)
			{
				free(q->lista_from[i]);
				q->lista_from[i]=NULL;
			}
		}
		free(q->lista_from);
		q->lista_from=NULL;
	}
	q->tam_sel=0;
	q->tam_wh=0;
	q->tam_fr=0;
	q->order=255;
	q->flags=0;
}
void inicializa_entrada(tipo_entrada *e)
{
	int i;
	if(e->lista!=NULL)
	{
		for(i=0;i<e->tam_l;i++)
		{
			if(e->lista[i]!=NULL)
			{
				free(e->lista[i]);
				e->lista[i]=NULL;
			}
		}
		free(e->lista);
		e->lista=NULL;
	}
	e->tam_l=0;
	e->sig=NULL;
}

/**
 * inserts an entry into a linked list it can represent anything, 
 * a row for example
 * @param entr the entry to insert
 * @param e the entry where to insert entr
 * @param tipo the type of inserion T_FILE for example
 */
void inserta_entrada(char *entr,tipo_entrada *e,unsigned short tipo)
{
	int i;
	e->tipo=tipo;
	char** aux;
	aux=e->lista;
	e->tam_l++;
	//printf("insertando %s\n",entr);
	e->lista=malloc(sizeof(char *)*e->tam_l);
//#pragma omp parallel shared(e,aux) private(i)
//  {
//        #pragma omp for
        for(i=1;i<e->tam_l;i++)
	{
		e->lista[i]=aux[i-1];
	}
//  }
	char * entr_aux=malloc(sizeof(char)*(strlen(entr)+1));
	strcpy(entr_aux,entr);
	entr_aux[strlen(entr)]=0;
	e->lista[0]=entr_aux;
	if(aux!=NULL)
		free(aux);
}

/**
 * merges two entries
 * @param fusionada the merged entry
 * @param e1 one entry
 * @param e2 the other entry
 */
void fusiona_entradas(tipo_entrada *fusionada,tipo_entrada e1,tipo_entrada e2)
{
	int i;
	//printf("fusionando:\n");
	for(i=e1.tam_l-1;i>=0;i--)
	{
		inserta_entrada(e1.lista[i],fusionada,T_FILA);
	//	printf("%s\n",e1.lista[i]);
	}	
	//printf("----\n");
	for(i=e2.tam_l-1;i>=0;i--)
	{
		inserta_entrada(e2.lista[i],fusionada,T_FILA);
	//	printf("%s\n",e2.lista[i]);
	}
}

/**
 * prints a query
 * @param q the query to print
 */
void imprime_query(tipo_query *q)
{
	int i;
	printf("seleccionando:\n");fflush(stdout);
	for(i=0;i<q->tam_sel;i++)
		printf("%s\t",q->lista_seleccion[i]);
	printf("\ndesde:");	
	for(i=0;i<q->tam_fr;i++)
		printf("%s\t",q->lista_from[i]);
	printf("\n\na condicion de que:\n");	
	for(i=0;i<q->tam_wh;i++)
	{
		if(q->where[i].connector==CNN_NONE)
		{
			printf("%s",q->where[i].val1);
			printf("%s",CMP_TO_ASCII(q->where[i].cmp));
			printf("%s\n",q->where[i].val2);
		}
		else
			printf("%s\n",CNN_TO_ASCII(q->where[i].connector));
	}
	printf("ordenando por %i",q->order);
	printf("\n\n");
}

/**
 * informs of an error and gets out of the program
 * @param e the error
 */
void exit_error(char* e)
{
	printf("%s\n",e);
	exit(-1);
}

/**
 * Comverts a comparison into ascii
 * @param cmp the comparison
 * @return the equivalent ascii
 */
char * CMP_TO_ASCII(unsigned short cmp)
{
	
	switch(cmp)
	{
		case CMP_LT:return "<";
		case CMP_EQ:return "==";
		case CMP_GT:return ">";
		case CMP_LEQ:return "<=";
		case CMP_GEQ:return ">=";
		case CMP_NEQ:return "!=";
		default:return "__";
	}
}

/**
 * converts a condition connector into ascci
 * @param cnn the connector
 * @return the equivalent ascii
 */
char * CNN_TO_ASCII(unsigned short cnn)
{
	
	switch(cnn)
	{
		case CNN_AND:return "&&";
		case CNN_OR:return "||";
		case CNN_NO:return "NOT";
		case CNN_NONE:return "__";
		default:return "__";
	}
}

/**
 * Inserts a condition into a query
 * @param q the query
 * @param val1 the left operand in the condition
 * @param val2 the right operand in the condition
 * @param cmp the comparision operator
 */
void inserta_condicion(tipo_query *q,char *val1,char* val2,unsigned short cmp)
{
	tipo_condicion *aux;
	int i;
	aux=q->where;
	q->tam_wh++;
	q->where=malloc(q->tam_wh*sizeof(tipo_condicion));
	for(i=0;i<q->tam_wh-1;i++)
		q->where[i]=aux[i];
	tipo_condicion cond;

	//char *val1_aux=malloc(sizeof(char)*strlen(val1));
	//strcpy(val1_aux,val1);
	
	//char *val2_aux=malloc(sizeof(char)*strlen(val2));
	//strcpy(val2_aux,val2);
	
	cond.val1=val1;
	cond.cmp=cmp;
	cond.val2=val2;
	cond.connector=CNN_NONE;
	q->where[q->tam_wh-1]=cond;
	/*printf("insertando condicion");
	if(q->where[q->tam_wh-1].connector==CNN_NONE)
		{
			if(q->where[q->tam_wh-1].negar) printf("not ");
			printf("%s",q->where[0].val1);
			printf("%s",CMP_TO_ASCII(q->where[q->tam_wh-1].cmp));
			printf("%s\n",q->where[q->tam_wh-1].val2);
		}
		else
			printf("%s\n",CNN_TO_ASCII(q->where[q->tam_wh-1].connector));*/
	if(aux!=NULL)
		free(aux);
}

/**
 * inserts a condition connector into the query where
 * @param q the query
 * @param cnn the connector
 */
void inserta_connector(tipo_query *q,unsigned short cnn)
{
	tipo_condicion *aux;
	int i;
	aux=q->where;
	q->tam_wh++;
	q->where=malloc(q->tam_wh*sizeof(tipo_condicion));
	for(i=0;i<q->tam_wh-1;i++)
		q->where[i]=aux[i];
	tipo_condicion cond;
	cond.connector=cnn;
	q->where[q->tam_wh-1]=cond;
	/*printf("insertando conector");
	if(q->where[q->tam_wh-1].connector==CNN_NONE)
		{
			if(q->where[q->tam_wh-1].negar) printf("not ");
			printf("%s",q->where[q->tam_wh-1].val1);
			printf("%s",CMP_TO_ASCII(q->where[q->tam_wh-1].cmp));
			printf("%s\n",q->where[q->tam_wh-1].val2);
		}
		else
			printf("%s\n",CNN_TO_ASCII(q->where[q->tam_wh-1].connector));*/
	if(aux!=NULL)
		free(aux);
}

/**
 * inserts a selection into the query
 * @param q the query
 * @param sel the selection
 */
void inserta_seleccion(tipo_query *q,char *sel)
{
	char **aux;
	int i;
	char *sel_aux=malloc(sizeof(char)*(strlen(sel)+1));
	strcpy(sel_aux,sel);
	sel_aux[strlen(sel)]=0;
	aux=q->lista_seleccion;
	q->tam_sel++;
	q->lista_seleccion=malloc(q->tam_sel*sizeof(char*));
	for(i=1;i<q->tam_sel;i++)
		q->lista_seleccion[i]=aux[i-1];
	q->lista_seleccion[0]=sel_aux;
	if(aux!=NULL)
		free(aux);
}

/**
 * inserts the from in a query
 * @param q the query
 * @param or the from
 */
void inserta_origen(tipo_query*q,char *or)
{
	char **aux;
	int i;
	char *or_aux=malloc(sizeof(char)*strlen(or));
	strcpy(or_aux,or);
	aux=q->lista_from;
	q->tam_fr++;
	q->lista_from=malloc(q->tam_fr*sizeof(char*));
	for(i=1;i<q->tam_fr;i++)
		q->lista_from[i]=aux[i-1];
	q->lista_from[0]=or_aux;
	if(aux!=NULL)
		free(aux);
}

/**
 * inserts the order by in a condition
 * @param q the query
 * @param order the sort criteria
 * @return true if evrerythinf ok else false
 */
unsigned char inserta_order(tipo_query *q,char* order)
{
	unsigned int i=comprueba_seleccion(q);
	int j;
	for(j=0;j<q->tam_sel;j++)
	{
		printf("comp %s,%s\n",q->lista_seleccion[j],order);
		if(strcmp(q->lista_seleccion[j],order)==0)
		{
			q->order=q->tam_sel-j-1;
			return 1;
		}
	}
	return 0;
}

/**
 * copies a condition into another
 * @param dest the destination
 * @param or the origin
 */
void copy_where(tipo_condicion *dest,tipo_condicion or)
{
	dest->cmp=or.cmp;
	if(or.val1!=NULL)
	{
		dest->val1=malloc(sizeof(char)*(strlen(or.val1)+1));
		memcpy(dest->val1,or.val1,strlen(or.val1));
		dest->val1[strlen(or.val1)]=0;
	}
	else
		dest->val1=NULL;
	if(or.val2!=NULL)
	{
		dest->val2=malloc(sizeof(char)*(strlen(or.val2)+1));
		memcpy(dest->val2,or.val2,strlen(or.val2));
		dest->val2[strlen(or.val2)]=0;
	}
	else
		dest->val2=NULL;
	dest->connector=or.connector;
}

/**
 * copies a query into another
 * @param dest the destination
 * @param or the origin
 */
void copy_query(tipo_query *dest,tipo_query or)
{
	int i;
	dest->tam_wh=or.tam_wh;
	dest->where=malloc(sizeof(tipo_condicion)*or.tam_wh);
	//#pragma omp for
	for(i=0;i<or.tam_wh;i++)
		copy_where(&dest->where[i],or.where[i]);
	if((or.lista_from!=NULL)&&(or.tam_fr>0))
	{
		dest->tam_fr=or.tam_fr;
		dest->lista_from=malloc(sizeof(char*)*dest->tam_fr);
		//#pragma omp for
		for(i=0;i<or.tam_fr;i++)
		{
			dest->lista_from[i]=malloc(sizeof(char)*(strlen(or.lista_from[i])+1));
			memcpy(dest->lista_from[i],or.lista_from[i],strlen(or.lista_from[i]));
			dest->lista_from[i][strlen(or.lista_from[i])]=0;
		}
	}
	else
	{
		dest->lista_from=NULL;
		dest->tam_fr=0;
	}
	
	dest->tam_sel=or.tam_sel;
	dest->lista_seleccion=malloc(sizeof(char*)*or.tam_sel);
	//#pragma omp for
	for(i=0;i<or.tam_sel;i++)
	{
		dest->lista_seleccion[i]=malloc(sizeof(char)*(strlen(or.lista_seleccion[i])+1));
		memcpy(dest->lista_seleccion[i],or.lista_seleccion[i],strlen(or.lista_seleccion[i]));
		dest->lista_seleccion[i][strlen(or.lista_seleccion[i])]=0;
	}
	dest->order=or.order;
	dest->flags=or.flags;
}

/**
 * deletes the where condition in the position index
 * @param q the query
 * @param index the index position
 */
void borra_where(tipo_query *q,unsigned int index)
{
	tipo_condicion *aux;
	int i,j=0;
	if(q->tam_wh<=0)
		return;
	aux=q->where;
	q->tam_wh--;
	//q->where=malloc(q->tam_wh*sizeof(tipo_condicion));
	//#pragma omp for
	for(i=index;i<q->tam_wh;i++)
	{
		//if(i!=index)
		//{
			q->where[i]=aux[i+1];
			//copy_where(&q->where[j],aux[i]);
		//	j++;
		//}
	}
	//if(aux!=NULL)
	//	free(aux);
}
/**
 * inserts a where condition in a certain position
 * @param q the query
 * @param c the condition
 * @param index the position
 */
void inserta_where(tipo_query *q,tipo_condicion c,unsigned int index)
{
	tipo_condicion *aux;
	int i,j=0;
	aux=q->where;
	q->tam_wh++;
	q->where=malloc(q->tam_wh*sizeof(tipo_condicion));
	for(i=0;i<q->tam_wh;i++)
	{
		if(i!=index)
		{
			//q->where[i]=aux[j];
			copy_where(&q->where[i],aux[j]);
			j++;
		}
		else
			//q->where[i]=c;
			copy_where(&q->where[i],c);
	}
	if(aux!=NULL)
		free(aux);
}

/**
 * prints an entry
 * @param ent the entry
 */
void imprime_entrada(tipo_entrada *ent)
{
	printf("IMPRIMIENDO ENTRADA\n");fflush(stdout);
	int i;
	for(i=0;i<ent->tam_l;i++)
		printf("%s\n",ent->lista[i]);
}

/*DEFINIMOS UNA CACHE PARA LOS ESQUEMAS*/
static tipo_entrada entradas_esquema[MAX_DAT];
static unsigned int esquemas_en_cache=0;	
/*FIN DEFINICION DE CACHE PARA LOS ESQUEMAS*/
unsigned int lee_esquema(char* path,tipo_entrada *t)
{
	int i=0,j,err=1,count=0;
	int encontrado=0;
	char aux[MAX_DAT];
	if(!esquemas_en_cache)
	{
		FILE *f_esq=fopen("./schema.txt","r");
		if(f_esq==NULL)
			return 0;
		while((err!=EOF)&&(err))
		{
		 	err=fscanf(f_esq,"%d\n",&j);
			inicializa_entrada(&entradas_esquema[i]);
			entradas_esquema[i].tam_l=j;	
			entradas_esquema[i].lista=malloc(sizeof(char*)*entradas_esquema[i].tam_l);
			for(j=0;j<entradas_esquema[i].tam_l;j++)
			{
				
				err=fscanf(f_esq,"%s\n",aux);
				entradas_esquema[i].lista[j]=malloc(sizeof(char)*(strlen(aux)+1));
				snprintf(entradas_esquema[i].lista[j],strlen(aux)+1,"%s",aux);
			}
			i++;
		}
		esquemas_en_cache=i-1;
	}
	
	for(i=0;i<esquemas_en_cache;i++)
	{
		if(strcmp(entradas_esquema[i].lista[0],path)==0)
		{
			encontrado=1;
			for(j=0;j<entradas_esquema[i].tam_l;j++)
			{
				//printf("\nleyendo %s",entradas_esquema[i].lista[j]);
				inserta_entrada(entradas_esquema[i].lista[j],t,T_ESQUEMA);
			}
			t->tam_l=entradas_esquema[i].tam_l;
			return 1;
		}
	}
	return 0;
}
void inserta_esquema(tipo_entrada *e)
{
	printf("insertando esquema\n");
	imprime_entrada(e);
	if(e->tipo!=T_ESQUEMA)
		return;
	FILE *f_esq=fopen("./schema.txt","a+");
	if(f_esq==NULL)
		return;
	unsigned int i,t=fprintf(f_esq,"\n%i\n",e->tam_l);
	for(i=0;i<e->tam_l;i++)
	{
		//if(i)
		//	t=fprintf(f_esq,"<%s>\n",e->lista[i]);
		//else
			t=fprintf(f_esq,"%s\n",e->lista[i]);
	}
	printf("devuelto:%i",t);
	fclose(f_esq);
	FILE *f_xml=fopen(e->lista[0],"w");
	fprintf(f_xml,"<?xml version=\"1.0\"?>\n");
	fprintf(f_xml,"<%s>\n</%s>",e->lista[1],e->lista[1]);
	fclose(f_xml);
	esquemas_en_cache=0;
	//lee_esquema("adsas");
}
unsigned int comprueba_esquema(char * path,unsigned short tipo,char * texto)
{
	//printf("comprobando en %s si %s es %i\n",path,texto,tipo);
	tipo_entrada t;
	t.lista=NULL;
	inicializa_entrada(&t);
	if(!lee_esquema(path,&t))return 0;
	int i;
	for(i=0;i<t.tam_l;i++)
	{
	//	printf("comparando %s %s\n",t->lista[i],texto);
		if(strcmp(t.lista[i],texto)==0)
		{
			if(tipo!=ATRIB)
				return((t.tam_l-i)==tipo);
			else
				return((t.tam_l-i)>=tipo);
		}
	}
	return 0;
	
}
/*
Comprueba si los atributos de la query select existen en las tablas
devuelve el número de atributos total de la select si todo va bien, si alguno
no existe en las tablas devuelve el indice del mismo
*/
unsigned int comprueba_seleccion(tipo_query *q)
{
	int dev=0,i,j;
	if((q->tam_sel==1)&&(strncmp(q->lista_seleccion[0],"*",1)==0))
	{
		tipo_entrada *entr=malloc(sizeof(tipo_entrada));
		entr->tam_l=0;
		entr->lista=NULL;
		inicializa_entrada(entr);
		q->tam_sel=0;
		for(i=q->tam_fr-1;i>=0;i--)
		{
			lee_esquema(q->lista_from[i],entr);
			for(j=0;j<entr->tam_l-3;j++)
				inserta_seleccion(q,entr->lista[j]);
			inicializa_entrada(entr);
		}
	}
	for(i=0;i<q->tam_sel;i++)
	{
		for(j=0;(!dev)&&(j<q->tam_fr);j++)
		{
			dev=dev||comprueba_esquema(q->lista_from[j],ATRIB,q->lista_seleccion[i]);
		}
		if(!dev)
			return i;
		dev=0;
	}
	return q->tam_sel;
}

/**
 * Drops the schema and a file xml thats a table drop
 * @param path_xml
 * @return 1 if everything ok else 0
 */
unsigned int elimina_esquema(char * path_xml)
{
	int i=0,j,err=1,count=0;

	tipo_entrada *t=malloc(sizeof(tipo_entrada));
	t->lista=NULL;
	inicializa_entrada(t);
	if(!lee_esquema(path_xml,t))return 0;
	
	FILE *f_esq;

	if((remove(path_xml)!=0)||(remove("./schema.txt")!=0))return 0;
		
	f_esq=fopen("./schema.txt","w");
	
	count=i-1;
	printf("count %i\n",esquemas_en_cache);
	for(i=0;i<esquemas_en_cache;i++)
	{
		if((t->tam_l!=entradas_esquema[i].tam_l)||(strcmp(t->lista[t->tam_l-1],entradas_esquema[i].lista[0])!=0))
		{
			fprintf(f_esq,"%d",entradas_esquema[i].tam_l);
			for(j=0;j<entradas_esquema[i].tam_l;j++)
				fprintf(f_esq,"\n%s",entradas_esquema[i].lista[j]);
		}
	}
	fclose(f_esq);
	esquemas_en_cache=0;
	return 1;
}

/**
 * compares two strings as if they are numbers
 * @param c1 string 1
 * @param c2 string 2
 * @return 1 if c1>c2, 0 if c1==c2, -1 if c1<c2
 */
int cad_comp(const char *c1,const char *c2)
{
	//printf("comparando %s %s\n",c1,c2);
	unsigned int len1=strlen(c1),len2=strlen(c2);
	if(len1>len2)return 1;
	if(len2>len1)return -1;
	int i=0;	
	//while((c1[i])&&(c1[i]==c2[i]))i++;
	//#pragma omp for	
	for(i=0;((i<len1)&&(c1[i]==c2[i]));i++){;}
	
	if(c1[i]<c2[i])
		return -1;
	if(c1[i]>c2[i])
		return 1;
	return 0;
}

/*DECLARACION DE ESTRUCTURAS PARA MANEJO DE LISTAS*/
struct cache_head
{
	tipo_entrada * head;
	tipo_entrada *cola;
};
#define CACHE_SIZE 3
static struct cache_head cache[CACHE_SIZE]={{NULL,NULL},{NULL,NULL},{NULL,NULL}};
/*FIN DECLARACIÓN DE ESTRUCTURAS PARA MANEJO DE LISTAS*/

/**
 * Inserts into the resultset head the entry ent in order
 * @param ent the entry
 * @param head the result set
 * @param order the order field number
 */
void inserta_lista_entradas_orden(tipo_entrada *ent, tipo_entrada *head,unsigned int order)
{
	if(order>=ent->tam_l)
		return;
	//printf("%i\n",ent->tam_l);
	tipo_entrada *act=head->sig;
	if(act==NULL)
	{
		head->sig=ent;
		ent->sig=NULL;
		//printf("gg");
		return;
	}
	tipo_entrada *sig;
	tipo_entrada *ant=head;
	if(cad_comp(act->lista[order],ent->lista[order])>=0)
	{
		ant->sig=ent;
		ent->sig=act;
		return;
	}
	while(act->sig!=NULL)
	{
		sig=act->sig;
		//printf("sig %i act %i\n",act->tam_l,sig->tam_l);
		//if((act->tam_l<=order)||(sig->tam_l<=order))
		//	{act=sig;continue;}
		//printf("Comparando %s %s %s %s\n",act->lista[order],ent->lista[order],sig->lista[order],ent->lista[order]);
		if((cad_comp(act->lista[order],ent->lista[order])<=0)&&(cad_comp(sig->lista[order],ent->lista[order])>=0))
		{
			act->sig=ent;
			ent->sig=sig;	
			return;
		}
		ant=act;
		act=sig;
	}
	if(cad_comp(act->lista[order],ent->lista[order])<=0)
	{	
		act->sig=ent;
		ent->sig=NULL;
	}
	else
	{
		ant->sig=ent;
		act->sig=NULL;
		ent->sig=act;
	}
}

/**
 * Inserts into the resultset head the entry ent
 * @param ent the entry to insert
 * @param head the result set
 * @param order the number of the field wich is ordered by
 */
void inserta_lista_entradas(tipo_entrada *ent, tipo_entrada *head,unsigned int order)
{
	//printf("INSERTANDO ENTRADA1\n");fflush(stdout);
	if(order<ent->tam_l)
	{
		inserta_lista_entradas_orden(ent,head,order);
		return;
	}
	int i;
	for(i=0;i<CACHE_SIZE;i++)
	{
		if(cache[i].head==head)
		{
			//printf("INSERTANDO ENTRADA2\n");fflush(stdout);
			cache[i].cola->sig=ent;
			ent->sig=NULL;
			cache[i].cola=ent;
			return;
		}
	}
	//printf("EN AÑADIR1\n");
	tipo_entrada *act=head;
	while(act->sig!=NULL){/*printf("act %i\n",act->tam_l);*/act=act->sig;}
	act->sig=ent;
	ent->sig=NULL;
	i=0;
	while(cache[i].head!=NULL)i++;
	if(i>=CACHE_SIZE)return;
	else
	{
		printf("metiendo en cache\n");
		cache[i].head=head;
		cache[i].cola=ent;
	}
	//printf("EN AÑADIR\n");
	/*tipo_entrada *ent_act=head;
	while(ent_act!=NULL)
	{
		for(i=0;i<ent_act->tam_l;i++)
			printf("%s\t",ent_act->lista[i]);
		printf("\n");
		ent_act=ent_act->sig;
	}*/
		
}

/*
 * Frees a resultset
 *  
*/
void elimina_lista_entradas(tipo_entrada *head)
{
	int i;
	for(i=0;i<CACHE_SIZE;i++)
	{
		if(cache[i].head==head)
		{
			cache[i].head=NULL;
			break;
		}
	}
	tipo_entrada *act=head->sig;
	tipo_entrada *liberar;
	while(act!=NULL)
	{
		liberar=act;
		act=act->sig;
		free(liberar);
	}
}

/**
 * Prints the query result
 * @param head the result set
 * @param q the query
 */
void imprime_resultado_query(tipo_entrada *head,tipo_query *q)
{
	
	//printf("\n----RESULTADO----\n");
	int i,j,k=0;
	unsigned int array_esps[q->tam_sel],ancho_tabla=0;
	printf("\033[2J");
	printf("\033[0;0f");
	printf("%s%s\n",AMARILLO,NEGRITA);
	//#pragma omp for
	for(i=0;i<q->tam_sel;i++)
		ancho_tabla+=(strlen(q->lista_seleccion[i])*1.6)+strlen(q->lista_seleccion[i])+2;
	for(i=0;i<ancho_tabla;i++)
		printf("-");
	printf("\n");
//	printf("ancho_tabla:%i\n",ancho_tabla);	
	//#pragma omp for
	for(i=0;i<q->tam_sel;i++)
	{
		printf("|");
		array_esps[i]=strlen(q->lista_seleccion[i])*1.6;
		for(j=0;j<(array_esps[i]>>1);j++)
			printf(" ");
		printf("%s",q->lista_seleccion[i]);
		for(j=j;j<array_esps[i];j++)
			printf(" ");
		array_esps[i]+=strlen(q->lista_seleccion[i]);
		printf("|");
		
	}
	printf("\n");
	for(i=0;i<ancho_tabla;i++)
		printf("-");
	printf("%s",RESET_TERM);	
	tipo_entrada *ent_act=head;
	unsigned int count=0,pp;
	char more[50];
	while(ent_act!=NULL)
	{
		for(i=ent_act->tam_l-1;i>=0;i--)
		{
			printf("|");
			j=array_esps[ent_act->tam_l-i-1]-strlen(ent_act->lista[i]);
			for(k=0;k<(j>>1);k++)
				printf(" ");
			printf("%s",ent_act->lista[i]);
			for(k=k;k<j;k++)
				printf(" ");
			printf("|");
		}
		printf("\n");
		ent_act=ent_act->sig;
		count++;
		if((q->flags&FLAG_BYPAGE)&&(!(count%35)))
		{
			printf("pulse para seguir mostrando");
			pp=getc(stdin);
			printf("\033[39;0f");
			
			printf("%s%s",AMARILLO,NEGRITA);
			snprintf(more,50,"PAG %i",count/35);
			
			pp=(ancho_tabla-strlen(more))>>1;		
			for(i=0;i<pp;i++)
				printf("-");
			printf("%s",more);
			for(i=0;i<pp;i++)
				printf("-");
			printf("\n%s",RESET_TERM);
		}
	}
	for(i=0;i<ancho_tabla;i++)
		printf("-");
	printf("\n%i Filas obtenidas\n",count-1);
	//printf("\n-----------------\n");
}
