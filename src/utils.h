#include <soc/rtc.h>

uint32_t get_cpu_freq() {
    rtc_cpu_freq_t  freq = rtc_clk_cpu_freq_get();
    return rtc_clk_cpu_freq_value(freq);
}

void set_cpu_speed_down() {
    Serial.println("=====> set_cpu_speed_down");
    rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
}

void get_cpu_freq_str(char *output, uint32_t freq) {
    int m = freq / 1000000;
    if(m > 0) {
        sprintf(output, "cpu: %d Mhz", m);
    }
}