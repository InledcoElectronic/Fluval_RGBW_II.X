#include "pwm.h"
#include <xc.h>

void PWM1_Initialize(void)
{
    // Set the PWM to the options selected in the MPLAB(c) Code Configurator

    // CCP1MODE PWM; CCP1EN enabled; CCP1FMT left_aligned; 
    CCP1CON = 0x9F;    

    // CCPR1H 0; 
    CCPR1H = 0x00;    

    // CCPR1L 0; 
    CCPR1L = 0x00;    

    // Selecting Timer 2
    CCPTMRSbits.C1TSEL = 0x1;
}

void PWM1_LoadDutyValue(unsigned int dutyValue)
{
    dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP1CONbits.CCP1FMT)
    {
        dutyValue <<= 6;
        CCPR1H = dutyValue >> 8;
        CCPR1L = dutyValue;
    }
    else
    {
        CCPR1H = dutyValue >> 8;
        CCPR1L = dutyValue;
    }
}

void PWM2_Initialize(void)
{
    // Set the PWM to the options selected in the MPLAB(c) Code Configurator

    // CCP2MODE PWM; CCP2EN enabled; CCP2FMT left_aligned; 
    CCP2CON = 0x9F;    

    // CCPR2H 0; 
    CCPR2H = 0x00;    

    // CCPR2L 0; 
    CCPR2L = 0x00;    

    // Selecting Timer 2
    CCPTMRSbits.C2TSEL = 0x1;
}

void PWM2_LoadDutyValue(unsigned int dutyValue)
{
    dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP2CONbits.CCP2FMT)
    {
        dutyValue <<= 6;
        CCPR2H = dutyValue >> 8;
        CCPR2L = dutyValue;
    }
    else
    {
        CCPR2H = dutyValue >> 8;
        CCPR2L = dutyValue;
    }
}

void PWM3_Initialize(void)
{
    // Set the PWM to the options selected in the MPLAB(c) Code Configurator

    // CCP3MODE PWM; CCP3EN enabled; CCP3FMT left_aligned; 
    CCP3CON = 0x9F;    

    // CCPR3H 0; 
    CCPR3H = 0x00;    

    // CCPR3L 0; 
    CCPR3L = 0x00;    

    // Selecting Timer 2
    CCPTMRSbits.C3TSEL = 0x1;
}

void PWM3_LoadDutyValue(unsigned int dutyValue)
{
    dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP3CONbits.CCP3FMT)
    {
        dutyValue <<= 6;
        CCPR3H = dutyValue >> 8;
        CCPR3L = dutyValue;
    }
    else
    {
        CCPR3H = dutyValue >> 8;
        CCPR3L = dutyValue;
    }
}

void PWM4_Initialize(void)
{
    // Set the PWM to the options selected in the MPLAB(c) Code Configurator

    // CCP4MODE PWM; CCP4OUT 0; CCP4EN enabled; CCP4FMT left_aligned; 
    CCP4CON = 0x9F;    

    // CCPR4H 0; 
    CCPR4H = 0x00;    

    // CCPR4L 0; 
    CCPR4L = 0x00;    

    // Selecting Timer 2
    CCPTMRSbits.C4TSEL = 0x1;
}

void PWM4_LoadDutyValue(unsigned int dutyValue)
{
    dutyValue &= 0x03FF;
    
    // Load duty cycle value
    if(CCP4CONbits.CCP4FMT)
    {
        dutyValue <<= 6;
        CCPR4H = dutyValue >> 8;
        CCPR4L = dutyValue;
    }
    else
    {
        CCPR4H = dutyValue >> 8;
        CCPR4L = dutyValue;
    }
}
