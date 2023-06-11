#ifndef pid_data_kun_h
#define pid_data_kun_h
#include "Arduino.h"
class pid_data_kun
{
public:
	float target_val;       //目标值
	float err;              //偏差值
	float err_last;         //上一个偏差值
    float err_last_last;    //上上一个偏差值
	float Kp,Ki,Kd;         //比例、积分、微分系数
	float integral;         //积分值
    float integral_max;     //积分最大值
    float integral_min;     //积分最小值
	float output_val;       //输出值
    float output_val_max;   //输出最大值
    float output_val_min;   //输出最小值
    pid_data_kun(void)
    {
        float target_val=0;       //目标值
        float err=0;              //偏差值
        float err_last=0;         //上一个偏差值
        float err_last_last=0;    //上上一个偏差值
        float Kp=5,Ki=5,Kd=5;         //比例、积分、微分系数
        float integral=0;         //积分值
        float integral_max=1000;     //积分最大值
        float integral_min=1000;     //积分最小值
        float output_val=0;       //输出值
        float output_val_max=1000;   //输出最大值
        float output_val_min=1000;
    }
};
#endif