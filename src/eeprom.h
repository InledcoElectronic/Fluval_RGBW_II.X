/* 
 * File:   eeprom.h
 * Author: liruya
 *
 * Created on 2016?11?21?, ??2:50
 */

#ifndef EEPROM_H
#define	EEPROM_H

#include "comman.h"


#ifdef	__cplusplus
extern "C" {
#endif

extern void writeLedPara( unsigned char addr, LedPara_t para );
extern LedPara_t readLedPara( unsigned char addr );
extern void saveLedPara();

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

