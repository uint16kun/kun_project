#include "encoder_kun.h"
encoder_kun encoder;
encoder_kun::encoder_kun(void):
encoder_1(1),
encoder_2(2)
{

} 
void encoder_kun::begin(uint8_t encoder_1_A_temp,uint8_t encoder_1_B_temp,uint8_t encoder_2_A_temp,uint8_t encoder_2_B_temp)
{
    encoder_1_A=encoder_1_A_temp;
    encoder_1_B=encoder_1_B_temp;
    encoder_2_A=encoder_2_A_temp;
    encoder_2_B=encoder_2_B_temp;
    pinMode(encoder_1_A, INPUT_PULLDOWN);
    pinMode(encoder_1_B, INPUT_PULLDOWN);
    pinMode(encoder_2_B, INPUT_PULLDOWN);
    pinMode(encoder_2_A, INPUT_PULLDOWN);
    attachInterrupt(encoder_1_A,encoder_1_A_inter,CHANGE);
    attachInterrupt(encoder_1_B,encoder_1_B_inter,CHANGE);
    attachInterrupt(encoder_2_A,encoder_2_A_inter,CHANGE);
    attachInterrupt(encoder_2_B,encoder_2_B_inter,CHANGE);
}
int encoder_kun:: get_speed(uint8_t temp)
{
    int speed_temp;
    switch(temp)
    {
        case 1:speed_temp=encoder_1_num;break;
        case 2:speed_temp=encoder_2_num;break;
    }
    clear_num(temp);
    return speed_temp;
}
int encoder_kun:: read_num(uint8_t temp)
{
    int num_temp;
    switch(temp)
    {
        case 1:num_temp=encoder_1_num;break;
        case 2:num_temp=encoder_2_num;break;
    }
    return num_temp;
}
void encoder_kun:: clear_num(uint8_t temp)
{
    switch(temp)
    {
        case 1:encoder_1_num=0;break;
        case 2:encoder_2_num=0;break;
    }
}
uint8_t encoder_1_A_temp,encoder_1_B_temp,encoder_2_A_temp,encoder_2_B_temp;
void IRAM_ATTR encoder_1_A_inter(void)
{
    static int lastA = 0;
    encoder_1_B_temp=digitalRead(encoder.encoder_1_B);
    encoder_1_A_temp=digitalRead(encoder.encoder_1_A);
    if(encoder_1_A_temp!=lastA)
    {
        if(encoder_1_A_temp==encoder_1_B_temp)
        {
            encoder.encoder_1_num--;
        }
        else if(encoder_1_A_temp!=encoder_1_B_temp)
        {
            encoder.encoder_1_num++;
        }
        lastA=encoder_1_A_temp;
    }
}
void IRAM_ATTR  encoder_1_B_inter(void)
{
    static int lastA = 0;
    encoder_1_A_temp=digitalRead(encoder.encoder_1_A);
    encoder_1_B_temp=digitalRead(encoder.encoder_1_B);
    if(encoder_1_B_temp!=lastA)
    {
        if(encoder_1_A_temp==encoder_1_B_temp)
        {
            encoder.encoder_1_num++;
        }
        else
        {
            encoder.encoder_1_num--;
        }
        lastA=encoder_1_B_temp;
    }
}
void IRAM_ATTR  encoder_2_A_inter(void)
{
    static int lastA = 0;
    encoder_2_A_temp=digitalRead(encoder.encoder_2_A);
    encoder_2_B_temp=digitalRead(encoder.encoder_2_B);
    if(encoder_2_A_temp!=lastA)
    {
        if(encoder_2_A_temp==encoder_2_B_temp)
        {
            encoder.encoder_2_num--;
        }
        else
        {
            encoder.encoder_2_num++;
        }
        lastA=encoder_2_A_temp;
    }
}
void IRAM_ATTR  encoder_2_B_inter(void)
{    
    static int lastA = 0;
    encoder_2_A_temp=digitalRead(encoder.encoder_2_A);
    encoder_2_B_temp=digitalRead(encoder.encoder_2_B);
    if(encoder_2_B_temp!=lastA)
    {
        if(encoder_2_A_temp==encoder_2_B_temp)
        {
            encoder.encoder_2_num++;
        }
        else
        {
            encoder.encoder_2_num--;
        }
        lastA=encoder_2_B_temp;
    }
}
