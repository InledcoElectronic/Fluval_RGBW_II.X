/*
 * File:   main.c
 * Author: liruya
 *
 * Created on 2016?11?19?, ??3:20
 */


#include "comman.h"
#include "eusart.h"
#include "eeprom.h"
#include "led.h"
#include "pin.h"
#include "pwm.h"
#include "tmr.h"
#include "rtc.h"
#include "ble.h"

void main() 
{
    SYSTEM_Initialize();
    //initialize BLE Module
    initBLE();
    
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    //init Led
    initLed();
    //init RTC
    initRTC();
    TMR0_StartTimer();
	//start TMR2n
	TMR2_StartTimer();
    
    while(1)
    {
        CLRWDT();
        
        if((BLE_INT == 0) && BLE_WKP)
        {
            nRcvIdx = 0;
            __delay_us(800);
            BLE_WKP	= 0;
        }
        if(BLE_INT && (BLE_WKP == 0))
        {
            __delay_us(100);
            BLE_WKP	= 1;
            DecodeDATA();
            nRcvIdx = 0;
        }
        //every second
        if (gLedRunPara.fSec) 
        {
            gLedRunPara.fSec = 0;
            //when find device
            if (gLedRunPara.find) 
            {
                findDeviceFlash();
            }
            else if (gLedPara.fAuto) 
            {
                //fast preview auto mode
                if (gLedRunPara.fPrev) 
                {
                    preview();
                }
                else
                {
                    autoRun();
                }
            }

            if (gLedRunPara.fSave) 
            {
                saveLedPara();
            }
        }
    }
}
