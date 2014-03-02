/* StruQX - SQL XML DATABASE
 * HelpPrinter.h
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
/* 
 * File:   HelpPrinter.h
 * Author: angel
 *
 * Created on 2 de marzo de 2014, 12:36
 */

#ifndef HELPPRINTER_H
#define	HELPPRINTER_H

#ifdef	__cplusplus
extern "C" {
#endif    

//SINTAX ERRORS HELP BEGIN
void general_help(void);
void cond_help(void);
void from_help(void);
void select_help(void);
void create_help(void);
void insert_help(void);
void delete_help(void);
void drop_help(void);
void source_help(void);
void system_help(void);
void order_help(void);
void bypage_help(void);
void xml_help(void);
//SINTAX ERRORS HELP END

//COMMAND LINE BEGIN
void print_command_line_help(void);
void print_version();
//COMMAND LINE END



#ifdef	__cplusplus
}
#endif

#endif	/* HELPPRINTER_H */

