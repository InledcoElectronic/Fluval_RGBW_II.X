/* 
 * File:   comman.h
 * Author: liruya
 *
 * Created on 2016?11?19?, ??3:54
 */

#ifndef COMMAN_H
#define	COMMAN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
#define INTERRUPT_GlobalInterruptEnable() (INTCONbits.GIE = 1)
#define INTERRUPT_GlobalInterruptDisable() (INTCONbits.GIE = 0)
#define INTERRUPT_PeripheralInterruptEnable() (INTCONbits.PEIE = 1)
#define INTERRUPT_PeripheralInterruptDisable() (INTCONbits.PEIE = 0)
    
#define _XTAL_FREQ  16000000
    
//ble module pins
#define BLE_RST         LATB5
#define BLE_WKP		LATC1
#define BLE_INT		RA2
    
#define VERSION                     "30313032"
#define AQUASKY_600_ID_VERSION      "3031343130313032"
#define AQUASKY_900_ID_VERSION      "3031343230313032"
#define AQUASKY_1200_ID_VERSION     "3031343330313032"
#define AQUASKY_380_ID_VERSION      "3031343430313032"
#define AQUASKY_530_ID_VERSION      "3031343530313032"
#define AQUASKY_835_ID_VERSION      "3031343630313032"
#define AQUASKY_990_ID_VERSION      "3031343730313032"
#define AQUASKY_750_ID_VERSION      "3031343830313032"
#define AQUASKY_1150_ID_VERSION     "3031343930313032"
#define CMD_ADV_600                 "AT+ADV_MFR_SPC=3031343130313032\r\n"
#define CMD_ADV_900                 "AT+ADV_MFR_SPC=3031343230313032\r\n"
#define CMD_ADV_1200                "AT+ADV_MFR_SPC=3031343330313032\r\n"
#define CMD_ADV_380                 "AT+ADV_MFR_SPC=3031343430313032\r\n"
#define CMD_ADV_530                 "AT+ADV_MFR_SPC=3031343530313032\r\n"
#define CMD_ADV_835                 "AT+ADV_MFR_SPC=3031343630313032\r\n"
#define CMD_ADV_990                 "AT+ADV_MFR_SPC=3031343730313032\r\n"
#define CMD_ADV_750                 "AT+ADV_MFR_SPC=3031343830313032\r\n"
#define CMD_ADV_1150                "AT+ADV_MFR_SPC=3031343930313032\r\n"
#define AQUASKY_LENGTH_600          0
#define AQUASKY_LENGTH_900          1
#define AQUASKY_LENGTH_1200         2
#define AQUASKY_LENGTH_380          3
#define AQUASKY_LENGTH_530          4
#define AQUASKY_LENGTH_835          5
#define AQUASKY_LENGTH_990          6
#define AQUASKY_LENGTH_750          7
#define AQUASKY_LENGTH_1150         8
    
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_600
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_900
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_1200
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_380
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_530
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_835
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_990
//#define AQUASKY_LENGTH              AQUASKY_LENGTH_750
#define AQUASKY_LENGTH              AQUASKY_LENGTH_1150

#define BLE_CMD_SLAVE       "AT+SET=1\r\n"
#define BLE_CMD_DATA        "AT+MODE=DATA\r\n"   
#define BLE_CMD_GET_ADV     "AT+ADV_MFR_SPC=?\r\n"       
#define BLE_CMD_ACK_OK      "AT+OK\r\n"	
    
#if AQUASKY_LENGTH == AQUASKY_LENGTH_600
#define DEVICE_ID_VERSION   AQUASKY_600_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_600  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_900
#define DEVICE_ID_VERSION   AQUASKY_900_ID_VERSION  
#define BLE_CMD_SET_ADV     CMD_ADV_900  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_1200
#define DEVICE_ID_VERSION   AQUASKY_1200_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_1200  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_380
#define DEVICE_ID_VERSION   AQUASKY_380_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_380  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_530
#define DEVICE_ID_VERSION   AQUASKY_530_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_530  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_835
#define DEVICE_ID_VERSION   AQUASKY_835_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_835  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_990
#define DEVICE_ID_VERSION   AQUASKY_990_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_990  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_750
#define DEVICE_ID_VERSION   AQUASKY_750_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_750  
#elif AQUASKY_LENGTH == AQUASKY_LENGTH_1150
#define DEVICE_ID_VERSION   AQUASKY_1150_ID_VERSION
#define BLE_CMD_SET_ADV     CMD_ADV_1150  
#else
#define DEVICE_ID_VERSION   AQUASKY_600_ID_VERSION  
#define BLE_CMD_SET_ADV     CMD_ADV_600  
#endif
	
#define	OVERTIME		30			//unit 4ms
#define	RESENDCOUNT		3
#define	RCVINTERVAL		15			//unit 4ms

#define PWM1		LATC5
#define PWM2		LATC4
#define PWM3		LATC3
#define PWM4		LATC6

#define CHANNEL_COUNT   4
#define CUSTOM_COUNT    4
  
//para defines
#define EEPROM_START_ADDR   0x7000          //eeprom start addr
#define ADDR_LED_PARA       0x10            //led para saved offset addr
#define PARA_SAVE_DELAY     3               //para saved delay if there is no para changed
 
typedef struct{
    unsigned char hour;
    unsigned char minute;
}Time_t;

typedef union{
    struct{
        unsigned char year;
        unsigned char month;
        unsigned char day;
        unsigned char wk;
        unsigned char hour;
        unsigned char minute;
        unsigned char second;
    }datetime;
    unsigned char array[7];
}DateTime_t;

typedef struct{
    Time_t start;
    Time_t end;
}TimeRamp_t;

typedef struct{
    union
    {
        struct{
            unsigned sun : 1;
            unsigned mon : 1;
            unsigned tue : 1;
            unsigned wed : 1;
            unsigned thu : 1;
            unsigned fri : 1;
            unsigned sat : 1;
            unsigned enable : 1;      
        };
        unsigned char enable_week;
    };    
    TimeRamp_t dynamicPeriod;
    unsigned char dynamicMode;
}AutoDynamic_t;


typedef union{
    struct{
        unsigned fOn : 1;
        unsigned fRsv : 7;
        unsigned char fDyn;
        unsigned int nBrt[CHANNEL_COUNT];
        unsigned char nCustomBrt[4][CHANNEL_COUNT];
    }manualPara;
    unsigned char array[6*CHANNEL_COUNT+2];
}ManualPara_t;

typedef union{
    struct{
        TimeRamp_t sunrise;
        unsigned char daylight[CHANNEL_COUNT];
        TimeRamp_t sunset;
        unsigned char moonlight[CHANNEL_COUNT];
        AutoDynamic_t autoDynamic;
    }autoPara;
    unsigned char array[2*CHANNEL_COUNT+14];
}AutoPara_t;

//typedef union{
//    struct{
//        TimeRamp_t sunrise;
//        unsigned char daylight[CHANNEL_COUNT];
//        TimeRamp_t sunset;
//        unsigned char moonlight[CHANNEL_COUNT];
//    }autoPara;
//    unsigned char array[2*CHANNEL_COUNT+8];
//}AutoPara_t;

typedef struct{
    unsigned fAuto : 1;
    unsigned fRsv : 7;
    ManualPara_t mPara;
    AutoPara_t aPara;
}LedPara_t;

typedef struct{
    unsigned find : 1;
    unsigned fSec : 1;
    unsigned fSave : 1;
    unsigned fPrev : 1;
    unsigned fPause : 1;
    unsigned fStep : 1;
    unsigned fRsv : 2;
        
    unsigned char fDynamic;
    unsigned char nFlashCount;
    unsigned char nSaveDelayCount;
    unsigned char nPrevCount;
    unsigned int nTargetBrt[CHANNEL_COUNT];
    unsigned int nCurrentBrt[CHANNEL_COUNT];       
}LedRunPara_t;

typedef struct{
    unsigned fDyn : 4;
    unsigned fBrt : 4;
    unsigned int min[CHANNEL_COUNT];
    unsigned int max[CHANNEL_COUNT];
    float delta[CHANNEL_COUNT];
    unsigned int cnt;
    unsigned char state;
    unsigned int num;
}LedDynamicPara_t;

extern volatile LedPara_t gLedPara;
extern volatile LedRunPara_t gLedRunPara;
extern volatile LedDynamicPara_t gDynPara;

extern  void SYSTEM_Initialize();

#ifdef	__cplusplus
}
#endif

#endif	/* COMMAN_H */

