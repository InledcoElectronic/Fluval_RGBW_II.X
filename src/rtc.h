/* 
 * File:   rtc.h
 * Author: liruya
 *
 * Created on 2016?11?21?, ??11:09
 */

#ifndef RTC_H
#define	RTC_H

#include "comman.h"


#ifdef	__cplusplus
extern "C" {
#endif

//current time YYMMdd D HHmmss
extern volatile DateTime_t gCurrentTime;

extern void initRTC();
extern void runRTC();

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

