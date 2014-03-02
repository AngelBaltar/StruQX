/* StruQX - SQL XML DATABASE
 * HelpPrinter.c
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
#include <string.h>

#include "MessagePrinters/HelpPrinter.h"
#include "MessagePrinters/TermPrintFormats.h"
#include "CommandLine/CommandLine.h"
#include "StruQXVersion.h"

/*
 * prints a general help when a sintax error happens
 */
void general_help(void)
{
        return;
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("\nHA OCURRIDO UN ERROR DEL QUE NO HAY INFORMACIÓN ESPECÍFICA!\n");
        printf("%s",AMARILLO_NEGRO);
        printf("--------------------------\n");
        printf("|BASE DE DATOS XML       |\n");
        printf("|AUTOR: Angel Baltar Diaz|\n");
        printf("-------------------------");
        printf("%s",RESET_TERM);
        printf("\n");

}

/**
 * prints a help when a sintax error happens parsing a condition
 */
void cond_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA CONDICION\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LAS CONDICIONES----------------------------------\n");
        printf("|	   (literal o id) > (literal o id)						|\n");
        printf("|	   (literal o id) < (literal o id)						|\n");
        printf("|	   (literal o id) >= (literal o id)						|\n");
        printf("|	   (literal o id) <= (literal o id)						|\n");
        printf("|	   (literal o id) == (literal o id)						|\n");
        printf("|	   (literal o id) != (literal o id)						|\n");
        printf("|	   (condicion rodeada por parentesis)						|\n");
        printf("|	  	    !condicion								|\n");
        printf("|	   (condicion || condicion )   Los parentesis la expresion OR son obligatorios	|\n");				
        printf("|	   (condicion && condicion )   Los parentesis las expresion AND son obligatorios|\n");
        printf(" ---------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a from clause
 */
void from_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA CLAUSULA FROM\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA CLAUSULA FROM----------------------------------\n");
        printf("|	   FROM archivo_tabla1.xml,archivo_tabla2.xml,...,archivo_tablaN.xml		|\n");
        printf("|	   La palabra reservada from puede ir en minusculas, mayusculas o combinaciones	|\n");
        printf("|	   Los archivos de tablas deben estar en la misma carpeta donde se ejecuta	|\n");
        printf("|	   la base de datos XML o ser paths absolutos hasta ellos			|\n");
        printf(" ---------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");

}

/**
 * prints a help when a sintax error happens parsing a select clause
 */
void select_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA CLAUSULA SELECT\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA CLAUSULA SELECT----------------------------------\n");
        printf("|	   SELECT Id1,Id2,...,IdN (Para seleccionar los ids especificados)		 |\n");
        printf("|	   SELECT *		  (Para seleccionar todos los atributos de la tabla)	 |\n");
        printf("|	   La palabra reservada select puede ir en minusculas, mayusculas o combinaciones|\n");
        printf("|	   Los atributos deben tener su correspondencia en las tablas que se indiquen en |\n");
        printf("|	   la clausula from.								 |\n");
        printf("|	   Para los ids se recomienda usar nombres cortos en minusculas			 |\n");
        printf(" ---------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");

}

/**
 * prints a help when a sintax error happens parsing a create clause
 */
void create_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA CLAUSULA CREATE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA CLAUSULA CREATE-------------------------------------------\n");
        printf("|	  CREATE archivo.xml(root=IdtagRaiz,node=IdtagNodo,attributes=IdAttr1,IdAttr2,...,IdAttrN); |\n");
        printf("|	  Las palabras reservadas CREATE root, node y attributes pueden ir en mayusculas,	    |\n");
        printf("|	  minusculas o combinaciones, pero root, node y attributes deben ir seguidos del = sin      |\n");
        printf("|	  sin espacio alguno, se recomienda que los ID (IdtagRaiz, IdtagNodo, y los id de atributos)|\n");
        printf("|	  sean palabras cortas en minusculas. archivo.xml será la ruta completa al archivo a crear  |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a insert clause
 */
void insert_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA SENTENCIA INSERT\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA SENTENCIA INSERT-------------------------------------------\n");
        printf("|	  INSERT archivo.xml (IdAttr1=\"literal1\",IdAttr2=\"literal2\",...,IdAttrN=\"literalN\",); |\n");
        printf("|	  La palabra reservada INSERT puede ir en mayusculas, minusculas o combinaciones	    |\n");
        printf("|	  archivo.xml será la ruta completa a la localización del archivo de la tabla		    |\n");
        printf("|	  se recomienda que los ID sean palabras cortas en minusculas				    |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a delete clause
 */
void delete_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA SENTENCIA DELETE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA SENTENCIA DELETE-------------------------------------------\n");
        printf("|	  DELETE FROM archivo.xml WHERE condicion;					   	    |\n");
        printf("|	  La palabra reservada DELETE puede ir en mayusculas, minusculas o combinaciones	    |\n");
        printf("|	  archivo.xml será la ruta completa a la localización del archivo de la tabla		    |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a drop clause
 */
void drop_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA SENTENCIA DROP\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA SENTENCIA DROP---------------------------------------------\n");
        printf("|	  DROP archivo.xml;					   	  			    |\n");
        printf("|	  La palabra reservada DROP puede ir en mayusculas, minusculas o combinaciones	   	    |\n");
        printf("|	  archivo.xml será la ruta completa a la localización del archivo de la tabla		    |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a source clause
 */
void source_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA SENTENCIA SOURCE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA SENTENCIA SOURCE-------------------------------------------\n");
        printf("|	  SOURCE archivo_texto;					   	  			    |\n");
        printf("|	  La palabra reservada SOURCE puede ir en mayusculas, minusculas o combinaciones	    |\n");
        printf("|	  archivo_texto será la ruta completa a la localización del archivo de script sql	    |\n");
        printf("|	  El archivo de texto deberá contener sentencias sql interpretables por este programa	    |\n");
        printf("|	  Una vez ejecutadas dichas sentencias debe usarse el comando exit source;	    	    |\n");
        printf("|	  Para salir del modo source (ejecución desde archivo de script)	 		    |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a system clause
 */
void system_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA SENTENCIA SYSTEM\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA SENTENCIA SYSTEM-------------------------------------------\n");
        printf("|	  SYSTEM \"comando al sistema\";					   	  	    |\n");
        printf("|	  La palabra reservada SYSTEM puede ir en mayusculas, minusculas o combinaciones	    |\n");
        printf("|	  comando al sistema debe ir entrecomillado ya que para el programa es un literal,	    |\n");
        printf("|	  una simple cadena de texto que se pasará al sistema, debe por tanto ser un comando	    |\n");
        printf("|	  válido en el sistema								    	    |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}
/**
 * prints a help when a sintax error happens parsing a order clause
 */
void order_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA CLAUSULA ORDER\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA CLAUSULA ORDER-------------------------------------------\n");
        printf("|	  ORDER BY id					   	  	    |\n");
        printf("|	  Las palabras reservadas ORDER y BY pueden ir en mayusculas, minusculas o combinaciones    |\n");
        printf("|	  id deberá ser uno de los identificadores seleccionados en la consultao o en caso de	    |\n");
        printf("|	  seleccionar *, deberá ser uno de los identificadores disponibles			    |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a bypage clause
 */
void bypage_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UNA CLAUSULA BY PAGE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SINTAXIS DE LA CLAUSULA BY PAGE-------------------------------------------\n");
        printf("|	  BY PAGE;					   	  	    |\n");
        printf("|	  Las palabras reservadas BY y PAGE pueden ir en mayusculas, minusculas o combinaciones	    |\n");
        printf("|	  Está cláusula debe indicarse al final de la consulta.				    	    |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a xml file
 */
void xml_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("PARECE QUE HA HABIDO UN ERROR PARSEANDO UN ARCHIVO XML\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------ERROR ARCHIVO XML-------------------------------------------------\n");
        printf("|	 Este error es debido a que el archivo xml está mal formado, o está en un formato    |\n");
        printf("|	 que no coincide con lo que el programa esperaba según fue definida la tabla   	     |\n");
        printf("|	 soportada por dicho archivo, compruebe el archivo xml buscando el error del que se  |\n");
        printf("|	 ha informado y corrijalo si es posible						     |\n");
        printf(" ---------------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints the command line help
 */
void print_command_line_help(void)
{
    int i,j;
    struct option* all_opts=getCommandLineOptions();
    char** descs=getCommandLineDescriptions();
    char opt[100];
    char fixed_spaces[100];
    i=0;
    printf("Usage: StruQX [options]");
    printf("Options:\n");
    while(all_opts[i].name!=NULL){
        opt[0]='-';
        opt[1]='-';
        opt[2]=0;
        strcat(opt,all_opts[i].name);
        fixed_spaces[0]=0;
        j=0;
        while(j<20-strlen(opt)){
            fixed_spaces[j]=' ';
            j++;
        }
        fixed_spaces[j]=0;
        printf("  %s %s %s Short:-%c\n",opt,fixed_spaces,descs[all_opts[i].val],all_opts[i].val);
        i++;
    }
}

/**
 * prints the version of the programm
 */
void print_version(void)
{
    printf("StruQX XML database\n\t V:%s\n",VERSION_NUMBER);
}