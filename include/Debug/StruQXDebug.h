/* StruQX - SQL XML DATABASE
 * StruQXDebug.h
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
 * File:   StruQXDebug.h
 * Author: angel
 *
 * Created on 22 de febrero de 2014, 20:14
 */

#ifndef STRUQXDEBUG_H
#define	STRUQXDEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    /*
 * enables de debug macro execution
 */
void enable_debug();

/*
 * disables de debug macro execution
 */
void disable_debug();

/**
 * gets if debug is enabled
 */
unsigned char is_debug_enabled();

#ifdef DEBUG_MODE
        #define DEBUG(statements) \
        do{\
            if(is_debug_enabled()){\
                    statements;\
            }\
        }while(0);

#else
        #define DEBUG(statements) \
        do{\
                ;\
        }while(0);
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* STRUQXDEBUG_H */

