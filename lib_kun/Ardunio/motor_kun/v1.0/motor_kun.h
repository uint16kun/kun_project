#ifndef motor_kun_h
#define motor_kun_h
#include "Arduino.h"
class motor_kun
{
private:
    uint8_t direction_pin
    ,direction_pin_1
    ,direction_pin_2
    ,pwm_pin
    ,channel
    ,bit_num;
    uint32_t freq,pwm_max;
public:
    motor_kun(void);
    void begin(uint8_t direction_pin_temp,uint8_t pwm_pin_temp,uint8_t channel_temp);
    void begin_tb6612(uint8_t direction_pin_1_temp,uint8_t direction_pin_2_temp,uint8_t pwm_pin_temp,uint8_t channel_temp);
    void motor_run(int speed);
    void motor_tb6612_run(int speed);
    void set_freq(uint32_t freq_temp);
    void set_bit_num(uint32_t bit_num_temp);
};
#endif