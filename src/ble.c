#include "ble.h"
#include "eusart.h"
#include "rtc.h"
#include "led.h"

#define END_FLASH           8192

#define FRM_HDR             0x68
#define CMD_DATA_AUTO       0x02
#define CMD_DATA_ONOFF      0x03
#define CMD_DATA_CTRL       0x04
#define CMD_DATA_READ       0x05
#define CMD_DATA_CUSTOM     0x06
#define CMD_DATA_CYCLE      0x07
#define CMD_DATA_INCREASE   0x08
#define CMD_DATA_DECREASE   0x09
#define CMD_DATA_DYN        0x0A
#define CMD_DATA_PREVIEW    0x0B
#define CMD_DATA_STOPPREV   0x0C
#define CMD_DATA_READTIME   0x0D
#define CMD_DATA_SYNCTIME   0x0E
#define CMD_DATA_FIND       0x0F
#define CMD_OTA_RESET       0x00

unsigned char getCRC ( unsigned char *pbuf, unsigned char len )
{
    unsigned char result = 0x00;
    for ( unsigned char i = 0; i < len; i++ )
    {
        result ^= *( pbuf + i );
    }
    return result;
}

void BLE_SendCMD ( const unsigned char *pBuf )
{
    unsigned char ack[] = { 'A', 'T', '+', 'O', 'K', '\r', '\n' };
    unsigned char index = 0;
    unsigned int cnt = 0;
    unsigned char rev = RCREG;
    while ( *pBuf != '\0' )
    {
        eusartSendByte(*pBuf++);
    }

    //等待ble应答 并判断指令是否成功
    while ( index < sizeof (ack ) )
    {
//        rev = eusartReadByte();
        if( PIR1bits.RCIF )
        {
            if (RC1STAbits.OERR) 
            {
                RC1STAbits.CREN = 0;
                RC1STAbits.CREN = 1;
            }
            rev = RCREG;
            if ( rev == ack[index] )
            {
                index++;
            }
            else
            {
                index = 0;
            }
        }
        __delay_us(100);
        cnt++;
        if( cnt > 1000 )
        {
            break;
        }
    }
}

unsigned char checkDevID ( )
{
    unsigned char dev[] = DEVICE_ID_VERSION;
    unsigned char index = 0;
    unsigned int cnt = 0;
    unsigned char rev;
    BLE_SendCMD(BLE_CMD_GET_ADV);
    while ( *(dev+index) != '\0' )
    {
//        rev = eusartReadByte();
        if( PIR1bits.RCIF )
        {
            if (RC1STAbits.OERR) 
            {
                RC1STAbits.CREN = 0;
                RC1STAbits.CREN = 1;
            }
            rev = RCREG;
            if ( rev == *(dev+index) )
            {
                index++;
            }
            else
            {
                return 0;
            }
        }
        __delay_us( 100 );
        cnt++;
        if( cnt > 1000 )
        {
            return 0;
        }
    }
    return 1;
}

void bleSendData ( const unsigned char *frame, unsigned char len )
{
    BLE_WKP = 0;
    __delay_us(800);
    while ( len-- )
    {
        eusartSendByte(*frame++);
    }
    //wait for the frame transmission completed
    while ( !TRMT );
    BLE_WKP = 1;
}

void bleSendDeviceData ( )
{
    unsigned char i;
    unsigned char len;
    txBuf[0] = FRM_HDR;
    txBuf[1] = CMD_DATA_READ;
    txBuf[2] = gLedPara.fAuto;
    if ( gLedPara.fAuto )
    {
        len = sizeof (gLedPara.aPara.array );
        for ( i = 0; i < len; i++ )
        {
            txBuf[3 + i] = gLedPara.aPara.array[i];
        }
    }
    else
    {
        len = sizeof (gLedPara.mPara.array );
        for ( i = 0; i < len; i++ )
        {
            txBuf[3 + i] = gLedPara.mPara.array[i];
        }
    }
    txBuf[len + 3] = getCRC(txBuf, len + 3);
    bleSendData(txBuf, len + 4);
}

void bleSendDeviceTime ( )
{
    unsigned char len = sizeof (gCurrentTime.array );
    txBuf[0] = FRM_HDR;
    txBuf[1] = CMD_DATA_READTIME;
    for ( unsigned char i = 0; i < len; i++ )
    {
        txBuf[2 + i] = gCurrentTime.array[i];
    }
    txBuf[9] = getCRC(txBuf, len + 2);
    bleSendData(txBuf, len + 3);
}

void DecodeDATA ( )
{
    if ( gLedRunPara.find || rxBuf[0] != FRM_HDR )
    {
        return;
    }
    switch ( rxBuf[1] )
    {
        case CMD_DATA_AUTO:
            if ( !gLedRunPara.fPrev && getCRC(rxBuf, 4) == 0x00 )
            {
                if ( gLedPara.mPara.manualPara.fDyn == DYNAMIC_SUNRS )
                {
                    gLedPara.mPara.manualPara.fDyn = 0;
                }
                gLedRunPara.fDynamic = 0;
                if ( rxBuf[2] == 0x00 )
                {
                    gLedPara.fAuto = 0;
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
                else if ( rxBuf[2] == 0x01 )
                {
                    gLedPara.fAuto = 1;
                }
                gLedRunPara.fPause = 0;
                gLedRunPara.fStep = 0;
                gLedRunPara.fSave = 1;
                gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
                bleSendDeviceData();
            }
            break;

        case CMD_DATA_ONOFF:
            if ( !gLedPara.fAuto )
            {
                if ( getCRC(rxBuf, 4) == 0x00 )
                {
                    if ( gLedPara.mPara.manualPara.fDyn == DYNAMIC_SUNRS )
                    {
                        gLedPara.mPara.manualPara.fDyn = 0;
                        gLedRunPara.fDynamic = 0;
                    }
                    if ( rxBuf[2] == 0x00 )
                    {
                        gLedPara.mPara.manualPara.fOn = 0;
                        gLedRunPara.fDynamic = 0;
                        turnOffLedRamp();
                    }
                    else if ( rxBuf[2] == 0x01 )
                    {
                        gLedPara.mPara.manualPara.fOn = 1;
                        if ( gLedPara.mPara.manualPara.fDyn == 0 )
                        {
                            gLedRunPara.fDynamic = 0;
                            turnOnLedRamp();
                        }
                        else
                        {
                            gLedRunPara.fDynamic = gLedPara.mPara.manualPara.fDyn;
                            initDynamic();
                        }
                    }
                    gLedRunPara.fPause = 0;
                    gLedRunPara.fStep = 0;
                    gLedRunPara.fSave = 1;
                    gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
                    bleSendDeviceData();
                }
            }
            break;

        case CMD_DATA_CTRL:
            if ( gLedPara.mPara.manualPara.fOn && ( !gLedPara.fAuto ) )
            {
                gLedPara.mPara.manualPara.fDyn = 0;
                unsigned char len = 3 + 2 * CHANNEL_COUNT;
                if ( getCRC(rxBuf, len) == 0x00 )
                {
                    for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
                    {
                        unsigned int val = ( rxBuf[2 + 2 * i] << 8 ) | rxBuf[3 + 2 * i];
                        if ( val <= MAX_LED_BRIGHT )
                        {
                            gLedPara.mPara.manualPara.nBrt[i] = val;
                            gLedRunPara.nTargetBrt[i] = val;
                        }
                    }
                    gLedRunPara.fDynamic = 0;
                    gLedRunPara.fPause = 0;
                    gLedRunPara.fStep = 0;
                    gLedRunPara.fSave = 1;
                    gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
                }
            }
            break;

        case CMD_DATA_READ:
            if ( rxBuf[0] ^ rxBuf[1] == rxBuf[2] )
            {
                bleSendDeviceData();
            }
            break;

        case CMD_DATA_CUSTOM:
            if ( rxBuf[2] < CUSTOM_COUNT && getCRC(rxBuf, 4) == 0x00 )
            {
                unsigned char idx = rxBuf[2];
                for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
                {
                    gLedPara.mPara.manualPara.nCustomBrt[idx][i] = gLedRunPara.nCurrentBrt[i] / 10;
                }
                gLedRunPara.fPause = 0;
                gLedRunPara.fStep = 0;
                gLedRunPara.fSave = 1;
                gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
                bleSendDeviceData();
            }
            break;

        case CMD_DATA_CYCLE:
            if ( !gLedRunPara.fPrev && getCRC(rxBuf, sizeof(gLedPara.aPara.array) + 3) == 0x00 )
            {
                unsigned char len = sizeof (gLedPara.aPara.array);
                for ( unsigned char i = 0; i < len; i++ )
                {
                    gLedPara.aPara.array[i] = rxBuf[2 + i];
                }
                gLedRunPara.fPause = 0;
                gLedRunPara.fStep = 0;
                gLedRunPara.fSave = 1;
                gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
                bleSendDeviceData();
            }
            break;

        case CMD_DATA_INCREASE:
            if ( gLedPara.mPara.manualPara.fOn && getCRC(rxBuf, 5) == 0x00 && rxBuf[2] < CHANNEL_COUNT )
            {
                unsigned char idx = rxBuf[2];
                if ( gLedPara.mPara.manualPara.nBrt[idx] + rxBuf[3] < MAX_LED_BRIGHT )
                {
                    gLedPara.mPara.manualPara.nBrt[idx] += rxBuf[3];
                    gLedRunPara.nTargetBrt[idx] = gLedPara.mPara.manualPara.nBrt[idx];
                }
                else
                {
                    gLedPara.mPara.manualPara.nBrt[idx] = MAX_LED_BRIGHT;
                    gLedRunPara.nTargetBrt[idx] = MAX_LED_BRIGHT;
                }
                gLedRunPara.fPause = 0;
                gLedRunPara.fStep = 1;
                gLedRunPara.fSave = 1;
                gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
            }
            break;

        case CMD_DATA_DECREASE:
            if ( gLedPara.mPara.manualPara.fOn && getCRC(rxBuf, 5) == 0x00 && rxBuf[2] < CHANNEL_COUNT )
            {
                unsigned char idx = rxBuf[2];
                if ( gLedPara.mPara.manualPara.nBrt[idx] > rxBuf[3] )
                {
                    gLedPara.mPara.manualPara.nBrt[idx] -= rxBuf[3];
                    gLedRunPara.nTargetBrt[idx] = gLedPara.mPara.manualPara.nBrt[idx];
                }
                else
                {
                    gLedPara.mPara.manualPara.nBrt[idx] = 0;
                    gLedRunPara.nTargetBrt[idx] = 0;
                }
                gLedRunPara.fPause = 0;
                gLedRunPara.fStep = 1;
                gLedRunPara.fSave = 1;
                gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
            }
            break;

        case CMD_DATA_DYN:
            if ( getCRC(rxBuf, 4) == 0x00 )
            {
                if ( rxBuf[2] == DYNAMIC_SUNRS || ( gLedPara.mPara.manualPara.fOn && rxBuf[2] <= DYNAMIC_SUNRS ) )
                {
                    gLedPara.mPara.manualPara.fDyn = rxBuf[2];
                    gLedRunPara.fDynamic = rxBuf[2];
                    initDynamic();
                    gLedRunPara.fPause = 0;
                    gLedRunPara.fStep = 0;
                    gLedRunPara.fSave = 1;
                    gLedRunPara.nSaveDelayCount = PARA_SAVE_DELAY;
                    bleSendDeviceData();
                }
                else if ( rxBuf[2] == DYNAMIC_PAUSE && gLedPara.mPara.manualPara.fOn && gLedPara.mPara.manualPara.fDyn )
                {
                    gLedRunPara.fPause = !gLedRunPara.fPause;
                }
            }
            break;

        case CMD_DATA_PREVIEW:
            if ( gLedPara.fAuto )
            {
                unsigned char len = 3 + 2 * CHANNEL_COUNT;
                if ( getCRC(rxBuf, len) == 0x00 )
                {
                    for ( unsigned char i = 0; i < CHANNEL_COUNT; i++ )
                    {
                        unsigned int val = ( rxBuf[2 + 2 * i] << 8 ) | rxBuf[3 + 2 * i];
                        if ( val <= MAX_LED_BRIGHT )
                        {
                            gLedRunPara.nCurrentBrt[i] = val;
                        }
                    }
                    updatePWM();
                    gLedRunPara.fPause = 0;
                    gLedRunPara.fStep = 0;
                    gLedRunPara.fPrev = 1;
                    gLedRunPara.nPrevCount = PREVIEW_COUNT;
                }
            }
            break;

        case CMD_DATA_STOPPREV:
            if ( FRM_HDR ^ CMD_DATA_STOPPREV == rxBuf[2] )
            {
                gLedRunPara.fPause = 0;
                gLedRunPara.fStep = 0;
                gLedRunPara.fPrev = 0;
                gLedRunPara.nPrevCount = 0;
            }
            break;

        case CMD_DATA_READTIME:
            if ( FRM_HDR ^ CMD_DATA_READTIME == rxBuf[2] )
            {
                bleSendDeviceTime();
            }
            break;

        case CMD_DATA_SYNCTIME:
            if ( getCRC(rxBuf, 10) == 0x00 )
            {
                INTERRUPT_GlobalInterruptDisable();
                gCurrentTime.datetime.year = rxBuf[2];
                gCurrentTime.datetime.month = rxBuf[3];
                gCurrentTime.datetime.day = rxBuf[4];
                gCurrentTime.datetime.wk = rxBuf[5];
                gCurrentTime.datetime.hour = rxBuf[6];
                gCurrentTime.datetime.minute = rxBuf[7];
                gCurrentTime.datetime.second = rxBuf[8];
                INTERRUPT_GlobalInterruptEnable();
                bleSendDeviceData();
            }
            break;

        case CMD_DATA_FIND:
            if ( FRM_HDR ^ CMD_DATA_FIND == rxBuf[2] )
            {
                gLedRunPara.find = 1;
                gLedRunPara.nFlashCount = FIND_FLASH_COUNT;
            }
            break;

        case CMD_OTA_RESET:
            if ( getCRC(rxBuf, 5) == 0x00 )
            {
                NVMADR = END_FLASH - 1;
                NVMCON1 = 0x94;
                NVMCON2 = 0x55;
                NVMCON2 = 0xAA;
                NVMCON1bits.WR = 1;
                NOP();
                NOP();
                while ( NVMCON1bits.WR );
                NVMCON1bits.WREN = 0;
                bleSendData(rxBuf, 5);
                __delay_ms(96);
                RESET();
            }
            break;

        default:
            break;
    }
}

void initBLE ( )
{
    BLE_WKP = 0;
    BLE_RST = 0;
    __delay_ms(20);
    BLE_RST = 1; //release from reset
    __delay_ms(240); //delay 200ms after power on

//    BLE_SendCMD("AT+SETUP=?\r\n");
//    __delay_ms(20);
    //检查设备id version是否写入蓝牙模块广播数据
    if ( checkDevID() == 0 )
    {
        __delay_ms(40);
        BLE_SendCMD(BLE_CMD_SET_ADV);
    }
    __delay_ms(40);
    //设置ble从机模式
    BLE_SendCMD(BLE_CMD_SLAVE);
    __delay_ms(40);
    //设置ble透传模式
    BLE_SendCMD(BLE_CMD_DATA);
    __delay_ms(20);
    BLE_WKP = 1;
}
