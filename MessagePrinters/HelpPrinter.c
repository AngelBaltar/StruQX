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
        printf("\nTHIS IS AN ERROR WITH NO SPECIFIC INFORMATION, SORRY!\n");
        printf("%s",AMARILLO_NEGRO);
        printf("--------------------------\n");
        printf("|StruQX       |\n");
        printf("|AUTHOR: Angel Baltar Diaz|\n");
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
        printf("IT SEMS TO BE A PROBLEM PARSING A CONDITION\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------CONDITION SINTAX----------------------------------                   \n");
        printf("|	   (literal or id) > (literal or id)                                                    |\n");
        printf("|	   (literal or id) < (literal or id)                                                    |\n");
        printf("|	   (literal or id) >= (literal or id)                                                   |\n");
        printf("|	   (literal or id) <= (literal or id)                                                   |\n");
        printf("|	   (literal or id) == (literal or id)                                                   |\n");
        printf("|	   (literal or id) != (literal or id)                                                   |\n");
        printf("|	   (condition between parenthesis)                                                      |\n");
        printf("|	  	    !condition                                                                  |\n");
        printf("|	   (condition || condition )   The parenthesis in the OR expression are mandatory 	|\n");				
        printf("|	   (condition && condition )   The parenthesis in the AND expression are mandatory      |\n");
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
        printf("IT SEMS TO BE A PROBLEM PARSING A FROM CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------FROM CLAUSE SINTAX-------------------------------------------\n");
        printf("|	   FROM file_table1.xml,file_table2.xml,...,file_tableN.xml                     |\n");
        printf("|	   The reserved word FROM is not case sensitive                                 |\n");
        printf("|	   The files for the tables need to be in the actual execution directory        |\n");
        printf("|	   it will work too if they are absolute paths                  		|\n");
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
        printf("IT SEMS TO BE A PROBLEM PARSING A SELECT CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SELECT CLAUSE SINTAX------------------------------------------\n");
        printf("|	   SELECT Id1,Id2,...,IdN (To Select the specified ids)         		 |\n");
        printf("|	   SELECT *		  (To Select all the ids from the table)                 |\n");
        printf("|	   The reserved word SELECT is not case sensitive                                |\n");
        printf("|	   The ids need to exist in the from clause specified tables                     |\n");
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
        printf("IT SEMS TO BE A PROBLEM PARSING A CREATE CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------CREATE CLAUSE SINTAX-----------------------------------------------------\n");
        printf("|	  CREATE file.xml(root=IdRootTag,node=IdNodeTag,attributes=IdAttr1,IdAttr2,...,IdAttrN);    |\n");
        printf("|	  The reserved words CREATE root, node and attributes are not case sensitive,               |\n");
        printf("|	  but root, node and attributes should be followed by = without any space between them      |\n");
        printf("|	  it's recommended  the IDs (IdtagRaiz, IdtagNodo, and the attribute IDs)                   |\n");
        printf("|	  to be short words. file.xml is the path to the file that will contain the table           |\n");
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
        printf("IT SEMS TO BE A PROBLEM PARSING A INSERT CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------INSERT SINTAX CLAUSE-----------------------------------------------------\n");
        printf("|	  INSERT file.xml (IdAttr1=\"literal1\",IdAttr2=\"literal2\",...,IdAttrN=\"literalN\",);    |\n");
        printf("|	  The reserved workd INSERT is not case sensitive                                           |\n");
        printf("|	  file.xml is the full path to the table file location                          	    |\n");
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
        printf("IT SEMS TO BE A PROBLEM PARSING A DELETE CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------DELETE CLAUSE SINTAX------------------\n");
        printf("|	  DELETE FROM file.xml WHERE condition;                  |\n");
        printf("|	  The reserved word DELETE is not case sensitive         |\n");
        printf("|	  file.xml is the full path to the table file location   |\n");
        printf(" ----------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a drop clause
 */
void drop_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("IT SEMS TO BE A PROBLEM PARSING A DROP CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------DROP CLAUSE SINTAX-----------------------\n");
        printf("|	  DROP file.xml;                                            |\n");
        printf("|	  The reserved word DROP is not case sensitive	   	    |\n");
        printf("|	  file.xml is the full path to the table file location      |\n");
        printf(" -------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a source clause
 */
void source_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("IT SEMS TO BE A PROBLEM PARSING A SOURCE CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SOURCE CLAUSE SINTAX---------------------------------------------\n");
        printf("|	  SOURCE file;					   	  			    |\n");
        printf("|	  The reserved word SOURCE is not case sensitive                                    |\n");
        printf("|	  file is the full path to a file containing valid StruQX SQL querys                |\n");
        printf("|	  If you want to exit StruQX after the execution of the file just put an exit;      |\n");
        printf("|	  at the end of the file. If you want only to exit source mode just put exit source |\n");
        printf(" -------------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a system clause
 */
void system_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("IT SEMS TO BE A PROBLEM PARSING A SYSTEM CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------SYSTEM CLAUSE SYNTAX--------------------------------------\n");
        printf("|	  SYSTEM \"command to the system\";                                          |\n");
        printf("|	  The reserved word SYSTEM is not case sensitive                             |\n");
        printf("|	  the command to the system should appear between \" because it is a literal |\n");
        printf("|	  the command to the system should be a valid command in the system	     |\n");
        printf(" -------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}
/**
 * prints a help when a sintax error happens parsing a order clause
 */
void order_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("IT SEMS TO BE A PROBLEM PARSING A ORDER CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------ORDER CLAUSE SYNTAX----------------------------------\n");
        printf("|	  ORDER BY id                                                           |\n");
        printf("|	  The words ORDER and BY are not case sensitive                         |\n");
        printf("|	  id should be one of the available attributes (a selected attribute)	|\n");
        printf(" -------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a bypage clause
 */
void bypage_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("IT SEMS TO BE A PROBLEM PARSING A BY PAGE CLAUSE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------BY PAGE CLAUSE SYNTAX----------------------------------------\n");
        printf("|	  BY PAGE;                                                                      |\n");
        printf("|	  The reserved words BY and PAGE are not case sensitive                         |\n");
        printf("|	  The clause should appear at the end of the query or do not appear at all.     |\n");
        printf(" ---------------------------------------------------------------------------------------");
        printf("%s",RESET_TERM);
        printf("\n");
}

/**
 * prints a help when a sintax error happens parsing a xml file
 */
void xml_help(void)
{
        printf("%s%s",ROJO_NEGRO,NEGRITA);
        printf("IT SEMS TO BE A PROBLEM PARSING A XML FILE\n");
        printf("%s",AMARILLO_NEGRO);
        printf(" --------------------------XML FILE ERROR---------------------------------------------\n");
        printf("|	 This error is because the xml file is not well formed, is in a unexpected    |\n");
        printf("|	 format, or the format doesn't match with the table format                    |\n");
        printf("|	 check the xml file and fix the error, please                                 |\n");
        printf(" -------------------------------------------------------------------------------------");
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