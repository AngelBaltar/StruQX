/* StruQX - SQL XML DATABASE
 * tipos_basicos.h
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

#ifndef TIPOS_BASICOS_H
#define TIPOS_BASICOS_H

#define MAX_DAT 100000

#define CMP_LT	500
#define CMP_EQ	501
#define CMP_GT	502
#define	CMP_LEQ	503
#define CMP_GEQ	504
#define CMP_NEQ	505


#define CNN_AND		506
#define CNN_OR		507
#define CNN_NO		508
#define CNN_NONE	509

typedef struct
{
	char *val1;
	unsigned short cmp;
	char * val2;
	unsigned short connector;
}tipo_condicion;


#define FLAG_BYPAGE (1<<0)
#define FLAG_ERROR  (1<<1)
typedef struct
{
	unsigned char tam_wh;
	tipo_condicion *where;
	unsigned char tam_fr;	
	char **lista_from;
	unsigned char tam_sel;
	char ** lista_seleccion;
	unsigned int order;
	unsigned short flags;

}tipo_query;

#define T_FILA		510
#define T_ESQUEMA	511

typedef struct entrada
{
	unsigned short tipo;
	unsigned char tam_l;	
	char **lista;
	struct entrada *sig;
}tipo_entrada;

#endif
