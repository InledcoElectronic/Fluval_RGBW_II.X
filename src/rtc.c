#include "rtc.h"

#define BASE_YEAR               2000
#define NORMAL_YEAR_FEBRUARY    28
#define LEAP_YEAR_FEBRUARY      29

volatile DateTime_t gCurrentTime;

unsigned char MONTH_DAY[12] = {31, NORMAL_YEAR_FEBRUARY, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
 * check if this is a leap year
 * @param year  the year to be check
 * @return 1-yes 0-false
 */
static unsigned char checkIsYearLeap(unsigned int year)
{
    if (year&0x03) 
    {
        if (year%100 == 0) 
        {
            if (year%400 == 0) 
            {
                return 1;
            }
        } 
        else 
        {
            return 1;
        }
    }
    return 0;
}

/**
 * init real time 
 */
void initRTC()
{
    gCurrentTime.datetime.second = 0;
    gCurrentTime.datetime.minute = 0;
    gCurrentTime.datetime.hour = 0;
    gCurrentTime.datetime.wk = 0;
    gCurrentTime.datetime.day = 1;
    gCurrentTime.datetime.month = 1;
    gCurrentTime.datetime.year = 0;
}

/**
 *  rtc run
 */
void runRTC()
{
    gCurrentTime.datetime.second++;
    if (gCurrentTime.datetime.second >= 60) 
    {
        gCurrentTime.datetime.second = 0;
        gCurrentTime.datetime.minute++;
        if (gCurrentTime.datetime.minute >= 60) 
        {
            gCurrentTime.datetime.minute = 0;
            gCurrentTime.datetime.hour++;
            if (gCurrentTime.datetime.hour >= 24) 
            {
                gCurrentTime.datetime.hour = 0;
                gCurrentTime.datetime.day++;
                gCurrentTime.datetime.wk++;
                if (gCurrentTime.datetime.wk > 6) 
                {
                    gCurrentTime.datetime.wk = 0;
                }
                if (checkIsYearLeap(gCurrentTime.datetime.year+BASE_YEAR)) 
                {
                    MONTH_DAY[1] = LEAP_YEAR_FEBRUARY;
                }
                else
                {
                    MONTH_DAY[1] = NORMAL_YEAR_FEBRUARY;
                }
                if (gCurrentTime.datetime.month <= 12 && gCurrentTime.datetime.month > 0) 
                {
                    if (gCurrentTime.datetime.day > MONTH_DAY[gCurrentTime.datetime.month-1]) 
                    {
                        gCurrentTime.datetime.day = 1;
                        gCurrentTime.datetime.month++;
                        if (gCurrentTime.datetime.month > 12) 
                        {
                            gCurrentTime.datetime.month = 1;
                            gCurrentTime.datetime.year++;
                        }
                    }
                } 
            }
        }
    }
    gLedRunPara.fSec = 1;
}
