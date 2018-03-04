#ifndef RTC_DS1307_H
#define RTC_DS1307_H

class RtcDS1307 {
    public:
        int init();
        
        const char * timeStr();
        const char *dateStr();
};

#endif