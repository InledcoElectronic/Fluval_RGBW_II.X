#include "led.h"
#include "pwm.h"
#include "rtc.h"
#include "eeprom.h"
#include "eusart.h"
#include <math.h>

void updatePWM ( )
{
    PWM1_LoadDutyValue(gLedRunPara.nCurrentBrt[0]);
    PWM2_LoadDutyValue(gLedRunPara.nCurrentBrt[1]);
    PWM3_LoadDutyValue(gLedRunPara.nCurrentBrt[2]);
    PWM4_LoadDutyValue(gLedRunPara.nCurrentBrt[3]);
}

void updateLed ( )
{
    unsigned char step;
    if ( gLedRunPara.fStep )
    {
        step = STEP_SLOW_BRIGHT;
    }
    else
    {
        step = STEP_NORMAL_BRIGHT;
    }
    for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
    {
        if ( gLedRunPara.nCurrentBrt[i] == gLedRunPara.nTargetBrt[i] )
        {
            continue;
        }
        else
        {
            if ( gLedRunPara.nCurrentBrt[i] + step < gLedRunPara.nTargetBrt[i] )
            {
                gLedRunPara.nCurrentBrt[i] += step;
            }
            else if ( gLedRunPara.nTargetBrt[i] + step < gLedRunPara.nCurrentBrt[i] )
            {
                gLedRunPara.nCurrentBrt[i] -= step;
            }
            else
            {
                gLedRunPara.nCurrentBrt[i] = gLedRunPara.nTargetBrt[i];
            }
        }
    }
    updatePWM();
}

void autoRun ( )
{
    unsigned char i, j;
    unsigned int ct = gCurrentTime.datetime.hour * 60u + gCurrentTime.datetime.minute;
    //开启了自动模式下动态效果
    if( gLedPara.aPara.autoPara.autoDynamic.enable_week > 0x80 )
    {
        //今天对应周x开启了自动模式下动态效果
        if( (gLedPara.aPara.autoPara.autoDynamic.enable_week & (1<<gCurrentTime.datetime.wk)) != 0x00 )
        {
//            if( gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.hour == gCurrentTime.datetime.hour
//               && gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.minute == gCurrentTime.datetime.minute )
//            {
//                gLedRunPara.fDynamic = gLedPara.aPara.autoPara.autoDynamic.dynamicMode;
//                initDynamic();
//            }
//            if( gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.hour == gCurrentTime.datetime.hour
//               && gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.minute == gCurrentTime.datetime.minute )
//            {
//                gLedRunPara.fDynamic = 0;
//            }
            unsigned int auto_dyn_start = gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.hour * 60u + gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.minute;
            unsigned int auto_dyn_end = gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.hour * 60u + gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.minute;
            if( auto_dyn_end >= auto_dyn_start )
            {
                if( ct >= auto_dyn_start && ct < auto_dyn_end )
                {
                    if( gLedRunPara.fDynamic != gLedPara.aPara.autoPara.autoDynamic.dynamicMode )
                    {
                        gLedRunPara.fDynamic = gLedPara.aPara.autoPara.autoDynamic.dynamicMode;
                        initDynamic();
                    }
                    return;
                }
            }
            else
            {
                if( ct >= auto_dyn_start || ct < auto_dyn_end )
                {
                    if( gLedRunPara.fDynamic != gLedPara.aPara.autoPara.autoDynamic.dynamicMode )
                    {
                        gLedRunPara.fDynamic = gLedPara.aPara.autoPara.autoDynamic.dynamicMode;
                        initDynamic();
                    }
                    return;
                }
            }
        }
    }
    gLedRunPara.fDynamic = 0;
    unsigned char sec = gCurrentTime.datetime.second;
    unsigned int tr[4];
    tr[0] = gLedPara.aPara.autoPara.sunrise.start.hour * 60u + gLedPara.aPara.autoPara.sunrise.start.minute;
    tr[1] = gLedPara.aPara.autoPara.sunrise.end.hour * 60u + gLedPara.aPara.autoPara.sunrise.end.minute;
    tr[2] = gLedPara.aPara.autoPara.sunset.start.hour * 60u + gLedPara.aPara.autoPara.sunset.start.minute;
    tr[3] = gLedPara.aPara.autoPara.sunset.end.hour * 60u + gLedPara.aPara.autoPara.sunset.end.minute;
    unsigned char val[4][CHANNEL_COUNT];
    for ( i = 0; i < CHANNEL_COUNT; i++ )
    {
        val[0][i] = gLedPara.aPara.autoPara.moonlight[i];
        val[1][i] = gLedPara.aPara.autoPara.daylight[i];
        val[2][i] = gLedPara.aPara.autoPara.daylight[i];
        val[3][i] = gLedPara.aPara.autoPara.moonlight[i];
    }
    for ( i = 0; i < 4; i++ )
    {
        j = ( i + 1 ) % 4;
        unsigned int st = tr[i];
        unsigned int et = tr[j];
        unsigned int duration;
        unsigned long dt;
        unsigned char dbrt;
        if ( et >= st )
        {
            if ( ct >= st && ct < et )
            {
                duration = et - st;
                dt = ( ct - st ) * 60ul + sec;
            }
            else
            {
                continue;
            }
        }
        else
        {
            if ( ct >= st || ct < et )
            {
                duration = 1440u - st + et;
                if ( ct >= st )
                {
                    dt = ( ct - st ) * 60ul + sec;
                }
                else
                {
                    dt = ( 1440u - st + ct ) * 60ul + sec;
                }
            }
            else
            {
                continue;
            }
        }
        for ( unsigned char k = 0; k < CHANNEL_COUNT; k++ )
        {
            if ( val[j][k] >= val[i][k] )
            {
                dbrt = val[j][k] - val[i][k];
                gLedRunPara.nCurrentBrt[k] = val[i][k] * 10u + dbrt * dt / ( duration * 6u );
            }
            else
            {
                dbrt = val[i][k] - val[j][k];
                gLedRunPara.nCurrentBrt[k] = val[i][k] * 10u - dbrt * dt / ( duration * 6u );
            }
        }
    }
    updatePWM();
}

/**
 * turn on led
 */
void turnOnLedRamp ( )
{
    for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
    {
        gLedRunPara.nTargetBrt[i] = gLedPara.mPara.manualPara.nBrt[i];
    }
}

/**
 * turn off led ramp
 */
void turnOffLedRamp ( )
{
    for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
    {
        gLedRunPara.nTargetBrt[i] = 0;
    }
}

void turnMaxLed ( )
{
    PWM1_LoadDutyValue(MAX_LED_BRIGHT);
    PWM2_LoadDutyValue(MAX_LED_BRIGHT);
    PWM3_LoadDutyValue(MAX_LED_BRIGHT);
    PWM4_LoadDutyValue(MAX_LED_BRIGHT);
}

/**
 * turn off led
 */
void turnOffLed ( )
{
    PWM1_LoadDutyValue(0);
    PWM2_LoadDutyValue(0);
    PWM3_LoadDutyValue(0);
    PWM4_LoadDutyValue(0);
}

/**
 * when find device led flashes
 */
void findDeviceFlash ( )
{
    static unsigned char tog = 0;
    if ( tog )
    {
        tog = 0;
        turnOffLed();
        if ( gLedRunPara.nFlashCount > 0 )
        {
            gLedRunPara.nFlashCount--;
        }
        if ( gLedRunPara.nFlashCount == 0 )
        {
            gLedRunPara.find = 0;
        }
    }
    else
    {
        tog = 1;
        turnMaxLed();
    }
}

void preview ( )
{
    if ( gLedRunPara.nPrevCount > 0 )
    {
        gLedRunPara.nPrevCount--;
    }
    if ( gLedRunPara.nPrevCount == 0 )
    {
        gLedRunPara.fPrev = 0;
    }
}

void updateDynamic ( )
{
    for ( unsigned char i = 0; i < 4; i++ )
    {
        if ( gDynPara.fDyn & ( 1 << i ) )
        {
            if ( gDynPara.fBrt & ( 1 << i ) )
            {
                gLedRunPara.nCurrentBrt[i] = gDynPara.min[i];
            }
            else
            {
                gLedRunPara.nCurrentBrt[i] = gDynPara.max[i];
            }
        }
    }
}

void initDynamic ( )
{
    gDynPara.state = 0;
    gDynPara.num = 0;
    gLedRunPara.fPause = 0;
//    switch ( gLedPara.mPara.manualPara.fDyn )
    switch ( gLedRunPara.fDynamic )
    {
        case DYNAMIC_THUNDER1:
            gDynPara.fDyn = 0;
            gLedRunPara.nCurrentBrt[0] = 0; //0%
            gLedRunPara.nCurrentBrt[1] = 0; //0%
            gLedRunPara.nCurrentBrt[2] = 250; //25%
            gLedRunPara.nCurrentBrt[3] = 200; //20%
            gDynPara.cnt = 500; //500*4ms=2s
            break;

        case DYNAMIC_THUNDER2:
            gDynPara.fDyn = 0x0C; //wb
            gDynPara.fBrt = 0x04; //b
            gDynPara.min[2] = 100;
            gDynPara.max[2] = 212;
            gDynPara.min[3] = 10;
            gDynPara.max[3] = 100;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gDynPara.delta[2] = 1.4; //(212-100)/80
            gDynPara.delta[3] = 1.125; //(100-10)/80
            gDynPara.cnt = 80; //80*4ms=320ms
            break;

        case DYNAMIC_THUNDER3:
            gDynPara.fDyn = 0x0F; //wbgr
            gDynPara.fBrt = 0x06;
            gDynPara.min[0] = 0; //0-100%
            gDynPara.max[0] = 1000;
            gDynPara.min[1] = 0; //0-50%
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 0; //0-100%
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 700; //75-100%
            gDynPara.max[3] = 1000;
            gDynPara.delta[0] = 1; //(1000-0)/1000
            gDynPara.delta[1] = 0.5; //(500-0)/1000
            gDynPara.delta[2] = 1; //(1000-0)/1000
            gDynPara.delta[3] = 0.3; //(1000-750)/1000
            gDynPara.cnt = 1000; //1000*4ms=4s
            break;

        case DYNAMIC_ALLCOLOR:
            gDynPara.fDyn = 0x01;
            gDynPara.fBrt = 0x00;
            gDynPara.min[0] = 300;
            gDynPara.max[0] = 700;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 1000;
            gLedRunPara.nCurrentBrt[3] = 100;
            gDynPara.delta[0] = 0.2; //(700-300)/2000=0.2
            gDynPara.cnt = 2000; //2000*4ms=8s
            break;

        case DYNAMIC_CLOUD1:
            gDynPara.fDyn = 0x0D;
            gDynPara.fBrt = 0x09;
            gDynPara.min[0] = 0; //0-100%
            gDynPara.max[0] = 1000;
            gDynPara.min[2] = 0; //0-100%
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 500; //50-100%
            gDynPara.max[3] = 1000;
            gLedRunPara.nCurrentBrt[1] = 250; //25%
            gDynPara.delta[0] = 0.5; //(1000-0)/2000=0.5
            gDynPara.delta[2] = 0.5; //(1000-0)/2000=0.5
            gDynPara.delta[3] = 0.25; //(1000-5000)/2000=0.25
            gDynPara.cnt = 2000;
            break;

        case DYNAMIC_CLOUD2:
            gDynPara.fDyn = 0x0E;
            gDynPara.fBrt = 0x08;
            gDynPara.min[1] = 0; //0-50%
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 0; //0-1000%
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 500; //50-100%
            gDynPara.max[3] = 1000;
            gLedRunPara.nCurrentBrt[0] = 0;
            gDynPara.delta[1] = 0.25; //(500-0)/2000
            gDynPara.delta[2] = 0.5; //(1000-0)/2000
            gDynPara.delta[3] = 0.25; //(1000-500)/2000
            gDynPara.cnt = 2000;
            break;

        case DYNAMIC_CLOUD3:
            gDynPara.fDyn = 0x07;
            gDynPara.fBrt = 0x01;
            gDynPara.min[0] = 0; //0-100%
            gDynPara.max[0] = 1000;
            gDynPara.min[1] = 0; //0-50%
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 0; //0-100%
            gDynPara.max[2] = 1000;
            gLedRunPara.nCurrentBrt[3] = 1000;
            gDynPara.delta[0] = 0.5;
            gDynPara.delta[0] = 0.25;
            gDynPara.delta[0] = 0.5;
            gDynPara.cnt = 2000;
            break;

        case DYNAMIC_CLOUD4:
            gDynPara.fDyn = 0x09;
            gDynPara.fBrt = 0x00;
            gDynPara.min[0] = 400; //40-64%
            gDynPara.max[0] = 640;
            gDynPara.min[3] = 500; //50-100%
            gDynPara.max[3] = 1000;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 0;
            gDynPara.delta[0] = 0.12; //(640-400)/2000
            gDynPara.delta[3] = 0.25; //(1000-500)/2000
            gDynPara.cnt = 2000;
            break;

        case DYNAMIC_MOON1:
            gDynPara.fDyn = 0x04;
            gDynPara.fBrt = 0x00;
            gDynPara.min[2] = 300; //30-100%
            gDynPara.max[2] = 1000;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.delta[2] = 0.35; //(1000-300)/2000
            gDynPara.cnt = 2000;
            break;

        case DYNAMIC_MOON2:
            gDynPara.fDyn = 0x04;
            gDynPara.fBrt = 0x00;
            gDynPara.min[2] = 100; //10-40%
            gDynPara.max[2] = 400;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.delta[2] = 0.15; //(400-100)/2000
            gDynPara.cnt = 2000;
            break;

        case DYNAMIC_MOON3:
            gDynPara.fDyn = 0x04;
            gDynPara.fBrt = 0x00;
            gDynPara.min[2] = 400; //40-100%
            gDynPara.max[2] = 1000;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 100;
            gDynPara.delta[2] = 0.3; //(1000-400)/2000
            gDynPara.cnt = 2000;
            break;

        case DYNAMIC_SUNRS:
            if ( gLedPara.mPara.manualPara.fOn &&
                 ( ( gLedRunPara.nCurrentBrt[0] > 0 ) || ( gLedRunPara.nCurrentBrt[1] > 0 ) ) ||
                 ( gLedRunPara.nCurrentBrt[2] > 0 ) || ( gLedRunPara.nCurrentBrt[3] > 0 ) )
            {
                for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
                {
                    gLedPara.mPara.manualPara.fOn = 0;
                    gLedRunPara.nTargetBrt[i] = 0;
                    gDynPara.min[i] = 0;
                    if ( gLedRunPara.nCurrentBrt[i] > 0 )
                    {
                        gDynPara.max[i] = gLedRunPara.nCurrentBrt[i];
                        gDynPara.delta[i] = 0.000032 * gLedRunPara.nCurrentBrt[i];
                    }
                    else
                    {
                        gDynPara.max[i] = 0;
                        gDynPara.delta[i] = 0;
                    }
                }
            }
            else
            {
                for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
                {
                    gLedPara.mPara.manualPara.fOn = 1;
                    gLedPara.mPara.manualPara.nBrt[i] = MAX_LED_BRIGHT;
                    gLedRunPara.nTargetBrt[i] = MAX_LED_BRIGHT;
                    gDynPara.min[i] = 0;
                    gDynPara.max[i] = MAX_LED_BRIGHT;
                    gDynPara.delta[i] = 0.000032 * MAX_LED_BRIGHT;
                }
            }
            gDynPara.fDyn = 0;
            gDynPara.cnt = 31250;
            gLedRunPara.fSave = 1;
            gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
            break;
        default:
            break;
    }
    updateDynamic();
    //    updatePWM();
}

void ledThunder_1 ( )
{
    gDynPara.fDyn = 0x00;
    gLedRunPara.nCurrentBrt[2] = 250;
    switch ( gDynPara.state )
    {
        case 0:
            gLedRunPara.nCurrentBrt[0] = 0; //0%
            gLedRunPara.nCurrentBrt[1] = 0; //0%
            gLedRunPara.nCurrentBrt[3] = 200; //20%
            gDynPara.cnt = 500; //500*4ms=2s
            break;
        case 1:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 200;
            gDynPara.cnt = 35;
            break;
        case 2:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 300;
            gDynPara.cnt = 30;
            break;
        case 3:
            gLedRunPara.nCurrentBrt[0] = 450;
            gLedRunPara.nCurrentBrt[1] = 450;
            gLedRunPara.nCurrentBrt[3] = 500;
            gDynPara.cnt = 30;
            break;
        case 4:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 250;
            gDynPara.cnt = 30;
            break;
        case 5:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.cnt = 250;
            break;
        case 6:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 300;
            gDynPara.cnt = 35;
            break;
        case 7:
            gLedRunPara.nCurrentBrt[0] = 450;
            gLedRunPara.nCurrentBrt[1] = 450;
            gLedRunPara.nCurrentBrt[3] = 400;
            gDynPara.cnt = 20;
            break;
        case 8:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 250;
            gDynPara.cnt = 20;
            break;
        case 9:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 200;
            gDynPara.cnt = 20;
            break;
        case 10:
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.cnt = 2500;
            break;
        default:
            break;
    }
}

void ledThunder_2 ( )
{
    gLedRunPara.nCurrentBrt[0] = 0;
    gLedRunPara.nCurrentBrt[1] = 0;
    switch ( gDynPara.state )
    {
        case 0:
        case 15:
        case 30:
        case 45:
        case 60:
            gDynPara.fDyn = 0x0C;
            gDynPara.fBrt = 0x04;
            gDynPara.min[2] = 100;
            gDynPara.max[2] = 212;
            gDynPara.min[3] = 10;
            gDynPara.max[3] = 100;
            gDynPara.delta[2] = 1.4;
            gDynPara.delta[3] = 1.125;
            gDynPara.cnt = 80;
            break;
        case 1:
        case 16:
        case 31:
        case 46:
        case 61:
            gDynPara.fDyn = 0x04;
            gDynPara.fBrt = 0x04;
            gDynPara.min[2] = 212;
            gDynPara.max[2] = 240;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.delta[2] = 1.4;
            gDynPara.cnt = 20;
            break;
        case 2:
        case 17:
        case 32:
        case 47:
        case 62:
            gDynPara.fDyn = 0x04;
            gDynPara.fBrt = 0x04;
            gDynPara.min[2] = 240;
            gDynPara.max[2] = 296;
            gLedRunPara.nCurrentBrt[3] = 16;
            gDynPara.delta[2] = 1.4;
            gDynPara.cnt = 40;
            break;
        case 3:
        case 18:
        case 33:
        case 48:
        case 63:
            gDynPara.fDyn = 0x04;
            gDynPara.fBrt = 0x04;
            gDynPara.min[2] = 296;
            gDynPara.max[2] = 492;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.delta[2] = 1.4;
            gDynPara.cnt = 140;
            break;
        case 4:
        case 19:
        case 34:
        case 49:
        case 64:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[2] = 492;
            gLedRunPara.nCurrentBrt[3] = 250;
            gDynPara.cnt = 10;
            break;
        case 5:
        case 20:
        case 35:
        case 50:
        case 65:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[2] = 200;
            gLedRunPara.nCurrentBrt[3] = 100;
            gDynPara.cnt = 10;
            break;
        case 6:
        case 21:
        case 36:
        case 51:
        case 66:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[2] = 100;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.cnt = 10;
            break;
        case 7:
        case 22:
        case 37:
        case 52:
        case 67:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[2] = 50;
            gLedRunPara.nCurrentBrt[3] = 76;
            gDynPara.cnt = 20;
            break;
        case 8:
        case 23:
        case 38:
        case 53:
        case 68:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[2] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.cnt = 10;
            break;
        case 9:
        case 24:
        case 39:
        case 54:
        case 69:
            gDynPara.fDyn = 0x0C;
            gDynPara.fBrt = 0x00;
            gDynPara.min[2] = 100;
            gDynPara.max[2] = 300;
            gDynPara.min[3] = 0;
            gDynPara.max[3] = 100;
            gDynPara.delta[2] = 2.5;
            gDynPara.delta[3] = 1.25;
            gDynPara.cnt = 80;
            break;
        case 10:
        case 25:
            gDynPara.fDyn = 0x00;
            gDynPara.cnt = 500;
            break;
        case 55:
        case 70:
            gDynPara.fDyn = 0x00;
            gDynPara.cnt = 1500;
            break;
        case 40:
            gDynPara.fDyn = 0x00;
            gDynPara.cnt = 2750;
            break;
        case 11:
        case 26:
        case 41:
        case 56:
        case 71:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[2] = 180;
            gLedRunPara.nCurrentBrt[3] = 150;
            gDynPara.cnt = 30;
            break;
        case 12:
        case 27:
        case 42:
        case 57:
        case 72:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[2] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.cnt = 10;
            break;
        case 13:
        case 28:
        case 43:
        case 58:
        case 73:
            gDynPara.fDyn = 0x0C;
            gDynPara.fBrt = 0x00;
            gDynPara.min[2] = 100;
            gDynPara.max[2] = 180;
            gDynPara.min[3] = 0;
            gDynPara.max[3] = 150;
            gDynPara.delta[2] = 0.8;
            gDynPara.delta[3] = 1.5;
            gDynPara.cnt = 100;
            break;
        case 14:
        case 44:
        case 59:
            gDynPara.fDyn = 0x00;
            gDynPara.cnt = 600;
            break;
        case 29:
            gDynPara.fDyn = 0x00;
            gDynPara.cnt = 1000;
            break;
        case 74:
            gDynPara.fDyn = 0x00;
            gDynPara.cnt = 500;
            break;
        default:
            break;
    }
    updateDynamic();
}

void ledThunder_3 ( )
{
    switch ( gDynPara.state )
    {
        case 0:
        case 2:
            gDynPara.fDyn = 0x0F;
            gDynPara.fBrt = 0x06;
            gDynPara.min[0] = 0;
            gDynPara.max[0] = 1000;
            gDynPara.min[1] = 0;
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 0;
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 700;
            gDynPara.max[3] = 1000;
            gDynPara.delta[0] = 1; //(250-0)/1000
            gDynPara.delta[1] = 0.5; //(125-0)/1000
            gDynPara.delta[2] = 1; //(250-0)/1000
            gDynPara.delta[3] = 0.3; //(250-175)/1000
            gDynPara.cnt = 1000; //1000*4ms=4s
            break;
        case 1:
        case 3:
            gDynPara.fDyn = 0x0F;
            gDynPara.fBrt = 0x09;
            gDynPara.min[0] = 0;
            gDynPara.max[0] = 1000;
            gDynPara.min[1] = 0;
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 0;
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 700;
            gDynPara.max[3] = 1000;
            gDynPara.delta[0] = 1; //(250-0)/1000
            gDynPara.delta[1] = 0.5; //(125-0)/1000
            gDynPara.delta[2] = 1; //(250-0)/1000
            gDynPara.delta[3] = 0.3; //(250-175)/1000
            gDynPara.cnt = 1000; //1000*4ms=4s
            break;
        case 4:
            gDynPara.fDyn = 0x0F;
            gDynPara.fBrt = 0x06;
            gDynPara.min[0] = 0;
            gDynPara.max[0] = 1000;
            gDynPara.min[1] = 0;
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 0;
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 500;
            gDynPara.max[3] = 1000;
            gDynPara.delta[0] = 1; //(250-0)/1000
            gDynPara.delta[1] = 0.5; //(125-0)/1000
            gDynPara.delta[2] = 1; //(250-0)/1000
            gDynPara.delta[3] = 0.5; //(250-125)/1000
            gDynPara.cnt = 1000; //1000*4ms=4s
            break;
        case 5:
            gDynPara.fDyn = 0x0A;
            gDynPara.fBrt = 0x00;
            gDynPara.min[1] = 0;
            gDynPara.max[1] = 500;
            gDynPara.min[3] = 0;
            gDynPara.max[3] = 500;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[2] = 1000;
            gDynPara.delta[1] = 0.5; //(125-0)/1000
            gDynPara.delta[3] = 0.5; //(125-0)/1000
            gDynPara.cnt = 1000; //1000*4ms=4s
            break;
        case 6:
            gDynPara.fDyn = 0x04;
            gDynPara.fBrt = 0x00;
            gDynPara.min[2] = 250;
            gDynPara.max[2] = 1000;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.delta[2] = 0.75; //(250-62)/1000
            gDynPara.cnt = 1000; //1000*4ms=4s
            break;
        case 7:
            gDynPara.fDyn = 0x08;
            gDynPara.fBrt = 0x08;
            gDynPara.min[3] = 0;
            gDynPara.max[3] = 450;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 250;
            gDynPara.delta[3] = 3; //(114-0)/150
            gDynPara.cnt = 150; //150*4ms=600ms
            break;
        case 8:
            gDynPara.fDyn = 0x07;
            gDynPara.fBrt = 0x07;
            gDynPara.min[0] = 440;
            gDynPara.max[0] = 500;
            gDynPara.min[1] = 440;
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 440;
            gDynPara.max[2] = 500;
            gLedRunPara.nCurrentBrt[3] = 250;
            gDynPara.delta[0] = 4; //(125-110)/15
            gDynPara.delta[1] = 4; //(125-110)/15
            gDynPara.delta[2] = 4; //(125-110)/15
            gDynPara.cnt = 15; //15*4m=60ms
            break;
        case 9:
            gDynPara.fDyn = 0x07;
            gDynPara.fBrt = 0x00;
            gDynPara.min[0] = 440;
            gDynPara.max[0] = 500;
            gDynPara.min[1] = 440;
            gDynPara.max[1] = 500;
            gDynPara.min[2] = 440;
            gDynPara.max[2] = 500;
            gLedRunPara.nCurrentBrt[3] = 250;
            gDynPara.delta[0] = 4; //(125-110)/15
            gDynPara.delta[1] = 4; //(125-110)/15
            gDynPara.delta[2] = 4; //(125-110)/15
            gDynPara.cnt = 15; //15*4m=60ms
            break;
        case 10:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 0;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.cnt = 30; //30*4=120ms
            break;
        case 11:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 0;
            gLedRunPara.nCurrentBrt[3] = 300;
            gDynPara.cnt = 30; //30*4=120ms
            break;
        case 12:
            gDynPara.fDyn = 0x07;
            gDynPara.fBrt = 0x07;
            gDynPara.min[0] = 300;
            gDynPara.max[0] = 360;
            gDynPara.min[1] = 300;
            gDynPara.max[1] = 360;
            gDynPara.min[2] = 300;
            gDynPara.max[2] = 360;
            gLedRunPara.nCurrentBrt[3] = 250;
            gDynPara.delta[0] = 2; //(90-75)/30
            gDynPara.delta[1] = 2; //(90-75)/30
            gDynPara.delta[2] = 2; //(90-75)/30
            gDynPara.cnt = 30; //30*4=120ms
            break;
        case 13:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 250;
            gLedRunPara.nCurrentBrt[3] = 100;
            gDynPara.cnt = 15; //15*4=60ms
            break;
        case 14:
            gDynPara.fDyn = 0x00;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 250;
            gLedRunPara.nCurrentBrt[3] = 0;
            gDynPara.cnt = 3000; //3000*4=12s
            break;
        case 15:
            gDynPara.fDyn = 0x0D;
            gDynPara.fBrt = 0x0D;
            gDynPara.min[0] = 0;
            gDynPara.max[0] = 1000;
            gDynPara.min[2] = 250;
            gDynPara.max[2] = 500;
            gDynPara.min[3] = 0;
            gDynPara.max[3] = 250;
            gLedRunPara.nCurrentBrt[1] = 0;
            gDynPara.delta[0] = 1; //(250-0)/1000
            gDynPara.delta[2] = 0.25; //(125-62)/1000
            gDynPara.delta[3] = 0.25; //(62-0)/1000
            gDynPara.cnt = 1000; //1000*4=4s
            break;
        case 16:
            gDynPara.fDyn = 0x0C;
            gDynPara.fBrt = 0x08;
            gDynPara.min[2] = 0;
            gDynPara.max[2] = 500;
            gDynPara.min[3] = 250;
            gDynPara.max[3] = 1000;
            gLedRunPara.nCurrentBrt[0] = 1000;
            gLedRunPara.nCurrentBrt[1] = 0;
            gDynPara.delta[2] = 0.5; //(125-0)/1000
            gDynPara.delta[3] = 0.75; //(250-62)/1000
            gDynPara.cnt = 1000; //1000*4=4s
            break;
        default:
            break;
    }
    updateDynamic();
}

void ledAllCOlor ( )
{
    switch ( gDynPara.state )
    {
        case 0:
            gDynPara.fDyn = 0x01; //0001
            gDynPara.fBrt = 0x00; //0000
            gDynPara.min[0] = 300;
            gDynPara.max[0] = 700;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 1000;
            gLedRunPara.nCurrentBrt[3] = 100;
            gDynPara.delta[0] = 0.2; //(175-75)/2000	
            break;
        case 1:
            gDynPara.fDyn = 0x03; //0011
            gDynPara.fBrt = 0x03; //0000
            gDynPara.min[0] = 300;
            gDynPara.max[0] = 700;
            gDynPara.min[1] = 0;
            gDynPara.max[1] = 700;
            gLedRunPara.nCurrentBrt[2] = 1000;
            gLedRunPara.nCurrentBrt[3] = 100;
            gDynPara.delta[0] = 0.2; //(175-75)/2000
            gDynPara.delta[1] = 0.35; //(175-0)/2000
            break;
        case 2:
            gDynPara.fDyn = 0x0F; //1111
            gDynPara.fBrt = 0x08; //0000
            gDynPara.min[0] = 0;
            gDynPara.max[0] = 700;
            gDynPara.min[1] = 0;
            gDynPara.max[1] = 700;
            gDynPara.min[2] = 0;
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 100;
            gDynPara.max[3] = 225;
            gDynPara.delta[0] = 0.35; //(175-0)/2000
            gDynPara.delta[1] = 0.35; //(175-0)/2000
            gDynPara.delta[2] = 0.5; //(250-0)/2000
            gDynPara.delta[3] = 0.0625; //(56-25)/2000
            break;
        case 3:
            gDynPara.fDyn = 0x0C; //1100
            gDynPara.fBrt = 0x04; //0000
            gDynPara.min[2] = 0;
            gDynPara.max[2] = 1000;
            gDynPara.min[3] = 100;
            gDynPara.max[3] = 225;
            gLedRunPara.nCurrentBrt[0] = 0;
            gLedRunPara.nCurrentBrt[1] = 0;
            gDynPara.delta[2] = 0.5; //(250-0)/2000
            gDynPara.delta[3] = 0.0625; //(56-25)/2000
            break;
        case 4:
            gDynPara.fDyn = 0x01; //0001
            gDynPara.fBrt = 0x01; //0001
            gDynPara.min[0] = 0;
            gDynPara.max[0] = 700;
            gLedRunPara.nCurrentBrt[1] = 0;
            gLedRunPara.nCurrentBrt[2] = 1000;
            gLedRunPara.nCurrentBrt[3] = 100;
            gDynPara.delta[0] = 0.35; //(175-0)/2000
            break;
        default:
            break;
    }
    gDynPara.cnt = 2000; //1000*4ms=4s
    updateDynamic();
}

void ledSunrs ( )
{
    unsigned char i;
    unsigned int temp;
    gDynPara.num++;
    for ( i = 0; i < 4; i++ )
    {
        temp = ( unsigned int ) ( gDynPara.delta[i] * gDynPara.num );
        if ( gLedPara.mPara.manualPara.fOn )
        {
            gLedRunPara.nCurrentBrt[i] = gDynPara.min[i] + temp;
        }
        else
        {
            gLedRunPara.nCurrentBrt[i] = gDynPara.max[i] - temp;
        }
    }
    if ( gDynPara.num >= gDynPara.cnt )
    {
        gDynPara.num = 0;
        gDynPara.fDyn = 0;
        gLedPara.mPara.manualPara.fDyn = 0;
        gLedRunPara.fDynamic = 0;
        gLedRunPara.fSave = 1;
        gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
        for ( i = 0; i < CHANNEL_COUNT; i++ )
        {
            gLedRunPara.nCurrentBrt[i] = gLedRunPara.nTargetBrt[i];
        }
    }
    updatePWM();
}

void ledDynamic ( )
{
    unsigned char i;
    unsigned int temp;
    if ( gLedRunPara.fPause )
    {
        return;
    }
    if ( gDynPara.num < gDynPara.cnt )
    {
        gDynPara.num++;
    }
    else
    {
        gDynPara.num = 0;
//        switch ( gLedPara.mPara.manualPara.fDyn )
        switch ( gLedRunPara.fDynamic )
        {
            case DYNAMIC_THUNDER1:
                gDynPara.state++;
                if ( gDynPara.state > 10 )
                {
                    gDynPara.state = 1;
                }
                ledThunder_1();
                break;
            case DYNAMIC_THUNDER2:
                gDynPara.state++;
                if ( gDynPara.state > 74 )
                {
                    gDynPara.state = 0;
                }
                ledThunder_2();
                break;
            case DYNAMIC_THUNDER3:
                gDynPara.state++;
                if ( gDynPara.state > 16 )
                {
                    gDynPara.state = 0;
                }
                ledThunder_3();
                break;
            case DYNAMIC_ALLCOLOR:
                gDynPara.state++;
                if ( gDynPara.state > 4 )
                    gDynPara.state = 0;
                ledAllCOlor();
                break;
            case DYNAMIC_CLOUD1:
            case DYNAMIC_CLOUD2:
            case DYNAMIC_CLOUD3:
            case DYNAMIC_CLOUD4:
            case DYNAMIC_MOON1:
            case DYNAMIC_MOON2:
            case DYNAMIC_MOON3:
                for ( i = 0; i < 4; i++ )
                {
                    if ( gDynPara.fDyn & ( 1 << i ) )
                    {
                        gDynPara.fBrt ^= ( 1 << i );
                    }
                }
                break;
            default:
                break;
        }
    }
    for ( i = 0; i < 4; i++ )
    {
        if ( gDynPara.fDyn & ( 1 << i ) )
        {
            temp = ( unsigned int ) ( gDynPara.num * gDynPara.delta[i] );
            if ( gDynPara.fBrt & ( 1 << i ) )
            {
                gLedRunPara.nCurrentBrt[i] = gDynPara.min[i] + temp;
            }
            else
            {
                gLedRunPara.nCurrentBrt[i] = gDynPara.max[i] - temp;
            }
        }
    }
    updatePWM();
}

void initLed ( )
{
    gLedPara = readLedPara(ADDR_LED_PARA);
    gLedPara.fRsv = 0;
    gLedPara.mPara.manualPara.fRsv = 0;
    for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
    {
        //manual light check
        if ( gLedPara.mPara.manualPara.nBrt[i] > MAX_LED_BRIGHT )
        {
            gLedPara.mPara.manualPara.nBrt[i] = MAX_LED_BRIGHT;
        }
        //custom light check
        for ( unsigned char j = 0; j < 4; j++ )
        {
            if ( gLedPara.mPara.manualPara.nCustomBrt[j][i] > 100 )
            {
                gLedPara.mPara.manualPara.nCustomBrt[j][i] = 100;
            }
        }
        //day light check
        if ( gLedPara.aPara.autoPara.daylight[i] > 100 )
        {
            gLedPara.aPara.autoPara.daylight[i] = 100;
        }
        //night light check
        if ( gLedPara.aPara.autoPara.moonlight[i] > 100 )
        {
            gLedPara.aPara.autoPara.moonlight[i] = 100;
        }
    }
    //sunrise start time check
    if ( gLedPara.aPara.autoPara.sunrise.start.hour > 23 )
    {
        gLedPara.aPara.autoPara.sunrise.start.hour = 0;
    }
    if ( gLedPara.aPara.autoPara.sunrise.start.minute > 59 )
    {
        gLedPara.aPara.autoPara.sunrise.start.minute = 0;
    }
    //sunrise end time check
    if ( gLedPara.aPara.autoPara.sunrise.end.hour > 23 )
    {
        gLedPara.aPara.autoPara.sunrise.end.hour = 0;
    }
    if ( gLedPara.aPara.autoPara.sunrise.end.minute > 59 )
    {
        gLedPara.aPara.autoPara.sunrise.end.minute = 0;
    }
    //sunset start time check
    if ( gLedPara.aPara.autoPara.sunset.start.hour > 23 )
    {
        gLedPara.aPara.autoPara.sunset.start.hour = 0;
    }
    if ( gLedPara.aPara.autoPara.sunset.start.minute > 59 )
    {
        gLedPara.aPara.autoPara.sunset.start.minute = 0;
    }
    //sunset end time check
    if ( gLedPara.aPara.autoPara.sunset.end.hour > 23 )
    {
        gLedPara.aPara.autoPara.sunset.end.hour = 0;
    }
    if ( gLedPara.aPara.autoPara.sunset.end.minute > 59 )
    {
        gLedPara.aPara.autoPara.sunset.end.minute = 0;
    }
    //auto dynamic period check
    if( gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.hour > 23 )
    {
        gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.hour = 0;
    }
    if( gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.minute > 59 )
    {
        gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.start.minute = 0;
    }
    if( gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.hour > 23 )
    {
        gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.hour = 0;
    }
    if( gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.minute > 59 )
    {
        gLedPara.aPara.autoPara.autoDynamic.dynamicPeriod.end.minute = 0;
    }
    if( gLedPara.aPara.autoPara.autoDynamic.dynamicMode >= DYNAMIC_SUNRS )
    {
        gLedPara.aPara.autoPara.autoDynamic.dynamicMode = 0;
        gLedPara.aPara.autoPara.autoDynamic.enable_week = 0;
    }
    
    if ( gLedPara.mPara.manualPara.fDyn >= DYNAMIC_SUNRS )
    {
        gLedPara.mPara.manualPara.fDyn = 0;
    }

    //manual mode, led on
    if ( !gLedPara.fAuto )
    {
        if ( gLedPara.mPara.manualPara.fOn )
        {
            if ( gLedPara.mPara.manualPara.fDyn == 0 )
            {
                turnOnLedRamp();
            }
            else
            {
                gLedRunPara.fDynamic = gLedPara.mPara.manualPara.fDyn;
                initDynamic();
            }
        }
        else
        {
            turnOffLedRamp();
        }
    }
}