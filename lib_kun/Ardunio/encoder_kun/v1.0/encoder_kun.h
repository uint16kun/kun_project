#ifndef encoder_kun_h
#define encoder_kun_h
#include <Arduino.h>
class encoder_kun
{
    private:
        // uint8_t encoder_1_A,encoder_1_B,encoder_2_A,encoder_2_B,encoder_1,encoder_2;
        // int encoder_1_num,encoder_2_num;

    public:
        uint8_t encoder_1_A,encoder_1_B,encoder_2_A,encoder_2_B,encoder_1,encoder_2;
        int encoder_1_num,encoder_2_num;
        encoder_kun(void);
        void begin(uint8_t encoder_1_A_temp,uint8_t encoder_1_B_temp,uint8_t encoder_2_A_temp,uint8_t encoder_2_B_temp);
        int get_speed(uint8_t temp);
        int read_num(uint8_t temp);
        void clear_num(uint8_t temp);
};
void IRAM_ATTR encoder_1_A_inter(void);
void IRAM_ATTR encoder_1_B_inter(void);
void IRAM_ATTR encoder_2_A_inter(void);
void IRAM_ATTR encoder_2_B_inter(void);
extern encoder_kun encoder;
#endif