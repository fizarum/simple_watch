#include "rtc_DS1307.h"

// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

int RtcDS1307::init() {
    if (! rtc.begin()) {
        return 1;
    } else {
        if (! rtc.isrunning()) {
            // following line sets the RTC to the date & time this sketch was compiled
            // This line sets the RTC with an explicit date & time, for example to set
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
        return 0;
    }
}

const char * RtcDS1307::timeStr() {
    DateTime now = rtc.now();
    String s = String(now.hour(), DEC) + ':' + String(now.minute(), DEC);
    char *result = new char[s.length()];
    strcpy(result, s.c_str());
    return (const char *)result;
}

const char *RtcDS1307::dateStr() {
    DateTime now = rtc.now();
    String s = String(now.year(), DEC) + '/' +String(now.month(), DEC) + '/' + String(now.day(), DEC);
    char *result = new char[s.length()];
    strcpy(result, s.c_str());
    return (const char *)result;
}
