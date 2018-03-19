/* 
 * File:   tmr.h
 * Author: liruya
 *
 * Created on 2016?11?21?, ??3:34
 */

#ifndef TMR_H
#define	TMR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "comman.h"
    
extern void TMR0_Initialize();
extern void TMR0_StartTimer();

extern void TMR2_Initialize();
extern void TMR2_StartTimer();

#ifdef	__cplusplus
}
#endif

#endif	/* TMR_H */

