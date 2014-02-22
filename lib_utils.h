/* StruQX - SQL XML DATABASE
 * tipos_basicos.h
 * Copyright (C) Angel Baltar Diaz
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
#ifndef LIB_UTILS_H
#define LIB_UTILS_H

extern int cad_comp(const char *c1,const char *c2);

//----------------------FUNCIONES PARA MOSTRAR ESTRUCTURAS DE DATOS------------------
extern char * CMP_TO_ASCII(unsigned short cmp);
extern char * CNN_TO_ASCII(unsigned short cnn);
extern void imprime_query(tipo_query *q);
extern void imprime_entrada(tipo_entrada *ent);
//-----------------------------------------------------------------------------------


//---------------------FUNCIONES DE MANEJO DE ESTRUCTURAS INTERNAS-------------------
extern void inicializa_query(tipo_query *q);
extern void inicializa_entrada(tipo_entrada *e);
extern void inserta_entrada(char *entr,tipo_entrada *e,unsigned short tipo);
extern void inserta_condicion(tipo_query *q,char *val1,char* val2,unsigned short cmp);
extern void inserta_connector(tipo_query *q,unsigned short cnn);
extern void inserta_seleccion(tipo_query *q,char *sel);
extern void inserta_origen(tipo_query*q,char *or);
extern void copy_query(tipo_query *dest,tipo_query or);
extern void borra_where(tipo_query *q,unsigned int index);
extern void inserta_where(tipo_query *q,tipo_condicion c,unsigned int index);
extern unsigned char inserta_order(tipo_query *q,char* order);
extern void fusiona_entradas(tipo_entrada *fusionada,tipo_entrada e1,tipo_entrada e2);
//----------------------------------------------------------------------------------

//----------------FUNCIONES DE MANEJO E IMPRESION DE LISTAS DE RESULTADOS------------
extern void inserta_lista_entradas(tipo_entrada *ent, tipo_entrada *head,unsigned int order);
extern void elimina_lista_entradas(tipo_entrada *head);
extern void imprime_resultado_query(tipo_entrada *head,tipo_query *q);
//-----------------------------------------------------------------------------------

//----------------FUNCIONES DE MANEJO DE METADATOS SOBRE TABLAS----------------------
extern unsigned int elimina_esquema(char * path_xml);
extern unsigned int lee_esquema(char* path,tipo_entrada *t);
extern void inserta_esquema(tipo_entrada *e);
//----------------------------------------------------------------------------------

//-------------------------FUNCIONES DE CONTROL DE ERRORES Y AYUDA------------------
extern void exit_error(char* e);

#define RAIZ	2
#define NODO	3
#define ATRIB	4
extern unsigned int comprueba_esquema(char * path,unsigned short tipo,char * texto);
extern unsigned int comprueba_seleccion(tipo_query *q);
extern void general_help(void);
extern void cond_help(void);
extern void from_help(void);
extern void select_help(void);
extern void create_help(void);
extern void insert_help(void);
extern void delete_help(void);
extern void drop_help(void);
extern void source_help(void);
extern void system_help(void);
extern void order_help(void);
extern void bypage_help(void);
extern void xml_help(void);
//----------------------------------------------------------------------------------

//-----------------DEFINICIONES PARA IMPRIMIR CON COLORES ETC-----------------------
#define RESET_TERM "\033[0m"
#define	ROJO_NEGRO "\033[40;31m"
#define NEGRITA	"\033[1m"
#define AMARILLO_NEGRO "\033[40;33m"
#define AMARILLO	"\033[33m"
#define SUBRAYADO	"\033[4m"
#define PARPADEO	"\033[5m"
//----------------------------------------------------------------------------------

#endif
