#include "motor_kun.h"
motor_kun::motor_kun(void):
bit_num(10),
freq(1000),
pwm_max(1023)
{

}
void motor_kun::begin(uint8_t direction_pin_temp,uint8_t pwm_pin_temp,uint8_t channel_temp)
{
    direction_pin=direction_pin_temp;
    pwm_pin=pwm_pin_temp;
    channel=channel_temp;
    pinMode(direction_pin, OUTPUT);
    digitalWrite(direction_pin,LOW);
    ledcSetup(channel, freq, bit_num);
    ledcAttachPin(pwm_pin, channel);
    ledcWrite(channel,0);
}
void motor_kun::motor_run(int speed)
{
    if(speed>=0)
    {
        digitalWrite(direction_pin,LOW);
        ledcWrite(channel,speed);
    }else if(speed<0)
    {
        ledcWrite(channel,pwm_max+speed);
        digitalWrite(direction_pin,HIGH);
    }
}
void  motor_kun::begin_tb6612(uint8_t direction_pin_1_temp,uint8_t direction_pin_2_temp,uint8_t pwm_pin_temp,uint8_t channel_temp)
{
    direction_pin_1=direction_pin_1_temp;
    direction_pin_2=direction_pin_2_temp;
    pwm_pin=pwm_pin_temp;
    channel=channel_temp;
    pinMode(direction_pin_1, OUTPUT);
    digitalWrite(direction_pin_1,LOW);
    pinMode(direction_pin_2, OUTPUT);
    digitalWrite(direction_pin_2,LOW);
    ledcSetup(channel, freq, bit_num);
    ledcAttachPin(pwm_pin, channel);
    ledcWrite(channel,0);
}
void motor_kun::motor_tb6612_run(int speed)
{
    if(speed>=0)
    {
        digitalWrite(direction_pin_1,HIGH);
        digitalWrite(direction_pin_2,LOW);
        ledcWrite(channel,speed);
    }else if(speed<0)
    {
        ledcWrite(channel,-speed);
        digitalWrite(direction_pin_1,LOW);
        digitalWrite(direction_pin_2,HIGH);
    }
}
void motor_kun::set_freq(uint32_t freq_temp)
{
    freq=freq_temp;
    ledcSetup(channel, freq, bit_num);
}

void motor_kun::set_bit_num(uint32_t bit_num_temp)
{
    bit_num=bit_num_temp;
    ledcSetup(channel, freq, bit_num);
}