#include "comman.h"
#include "eusart.h"
#include "pin.h"
#include "pwm.h"
#include "tmr.h"
#include "rtc.h"
#include "ble.h"
#include "eeprom.h"
#include "led.h"

//// CONFIG1
//#pragma config FEXTOSC = OFF    // FEXTOSC External Oscillator mode Selection bits->Oscillator not enabled
//#pragma config RSTOSC = HFINT1    // Power-up default value for COSC bits->HFINTOSC
//#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled; I/O or oscillator function on OSC2
//#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
//#pragma config FCMEN = OFF    // Fail-Safe Clock Monitor Enable->Fail-Safe Clock Monitor is disabled
//
//// CONFIG2
//#pragma config MCLRE = ON    // Master Clear Enable bit->MCLR/VPP pin function is MCLR; Weak pull-up enabled
//#pragma config PWRTE = ON    // Power-up Timer Enable bit->PWRT enabled
//#pragma config WDTE = ON    // Watchdog Timer Enable bits->WDT enabled, SWDTEN is ignored
//#pragma config LPBOREN = OFF    // Low-power BOR enable bit->ULPBOR disabled
//#pragma config BOREN = OFF    // Brown-out Reset Enable bits->Brown-out Reset disabled
//#pragma config BORV = HIGH    // Brown-out Reset Voltage selection bit->Brown-out voltage (Vbor) set to 2.7V
//#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->The PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
//#pragma config STVREN = ON    // Stack Overflow/Underflow Reset Enable bit->Stack Overflow or Underflow will cause a Reset
//#pragma config DEBUG = OFF    // Debugger enable bit->Background debugger disabled
//
//// CONFIG3
//#pragma config WRT = OFF    // User NVM self-write protection bits->Write protection off
//#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low Voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored.
//
//// CONFIG4
//#pragma config CP = OFF    // User NVM Program Memory Code Protection bit->User NVM code protection disabled
//#pragma config CPD = OFF    // Data NVM Memory Code Protection bit->Data NVM code protection disabled

volatile LedPara_t gLedPara;
volatile LedRunPara_t gLedRunPara;
volatile LedDynamicPara_t gDynPara;

void OSCILLATOR_Initialize ( void )
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; SOSCBE crystal oscillator; 
    OSCCON3 = 0x00;
    // LFOEN disabled; ADOEN disabled; SOSCEN enabled; EXTOEN disabled; HFOEN enabled; 
    OSCEN = 0x48;
    // HFFRQ 16_MHz; 
    OSCFRQ = 0x06;
    // HFTUN 0; 
    OSCTUNE = 0x00;
    // Set the secondary oscillator

}

void SYSTEM_Initialize ( )
{
    PIN_MANAGER_Initialize();
    OSCILLATOR_Initialize();
    PWM1_Initialize();
    PWM2_Initialize();
    PWM4_Initialize();
    PWM3_Initialize();
    TMR2_Initialize();
    TMR0_Initialize();
    EUSART_Initialize();
}

void interrupt INTERRUPT_interruptManager ( )
{
    static unsigned char cnt = 0;
    // interrupt handler
    if ( PIR1bits.RCIF == 1 )
    {
        EUSART_RCV_ISR();
    }
    else if ( PIR0bits.TMR0IF == 1 )
    {
        PIR0bits.TMR0IF = 0;
        runRTC();
    }
    else if ( PIR1bits.TMR2IF == 1 )
    {
        PIR1bits.TMR2IF = 0;
        cnt++;
        if ( ( cnt & 0x03 ) == 0x00 )
        {
            if ( gLedRunPara.find || gLedRunPara.fPrev || (gLedPara.fAuto && gLedRunPara.fDynamic == 0) )
            {
                return;
            }
            if ( gLedPara.mPara.manualPara.fDyn == DYNAMIC_SUNRS )
            {
                ledSunrs();
                return;
            }
//            if ( gLedPara.mPara.manualPara.fDyn == 0 || !gLedPara.mPara.manualPara.fOn )
//            {
//                updateLed();
//                return;
//            }
            if( gLedRunPara.fDynamic > 0 )
            {
                ledDynamic();
                return;
            }
            if ( gLedPara.mPara.manualPara.fDyn == 0 || !gLedPara.mPara.manualPara.fOn )
            {
                updateLed();
                return;
            }
        }
    }
}

