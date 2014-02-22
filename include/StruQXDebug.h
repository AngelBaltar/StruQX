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

static debug_enabled=0;

/*
 * enables de debug macro execution
 */
static inline void enable_debug()
{
    debug_enabled=1;
}

/*
 * disables de debug macro execution
 */
static inline void disable_debug()
{
    debug_enabled=0;
}

#define DEBUG(statements) \
        do{\
                if(debug_enabled){\
                        statements;\
                }\
        }while(0);


#ifdef	__cplusplus
}
#endif

#endif	/* STRUQXDEBUG_H */

