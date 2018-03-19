/* 
 * File:   led.h
 * Author: liruya
 *
 * Created on 2016?11?21?, ??11:38
 */

#ifndef LED_H
#define	LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "comman.h"
    
#define FIND_FLASH_COUNT    3
#define PREVIEW_COUNT       3
#define MIN_LED_BRIGHT      10
#define MAX_LED_BRIGHT      1000
#define DELTA_LED_BRIGHT    200
#define LED_STEP_TOUCH      2
#define LED_DELTA_TOUCH     10    
#define STEP_NORMAL_BRIGHT  4
#define STEP_SLOW_BRIGHT    1
    
#define LED_STATUS_OFF      0
#define LED_STATUS_DAY      1
#define LED_STATUS_NIGHT    2
#define LED_STATUS_BLE      3
    
#define DYNAMIC_NONE        0
#define DYNAMIC_THUNDER1    1
#define DYNAMIC_THUNDER2    2
#define DYNAMIC_THUNDER3    3
#define DYNAMIC_ALLCOLOR    4
#define DYNAMIC_CLOUD1      5
#define DYNAMIC_CLOUD2      6
#define DYNAMIC_CLOUD3      7
#define DYNAMIC_CLOUD4      8
#define DYNAMIC_MOON1       9
#define DYNAMIC_MOON2       10
#define DYNAMIC_MOON3       11
#define DYNAMIC_SUNRS       12
#define DYNAMIC_PAUSE       13

extern void updatePWM();
extern void updateLed();
extern void autoRun();
extern void turnOnLedRamp();
extern void turnOffLedRamp();
extern void initLed();
extern void findDeviceFlash();
extern void preview();
extern void initDynamic();
extern void ledSunrs();
extern void ledDynamic();

#ifdef	__cplusplus
}
#endif

#endif	/* LED_H */

