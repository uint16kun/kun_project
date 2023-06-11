#include "foc_kun.h"
foc_kun::foc_kun(void)
{
}
foc_kun::foc_kun(uint8_t AH_temp, uint8_t AL_temp, uint8_t BH_temp, uint8_t BL_temp, uint8_t CH_temp, uint8_t CL_temp)
{
    AH = AH_temp;
    AL = AL_temp;
    BH = BH_temp;
    BL = BL_temp;
    CH = CH_temp;
    CL = CL_temp;
    pwm_mode = 0;
    pwm_max = 1;
    for (uint8_t i = 0; i < pwm_resolution; i++)
    {
        pwm_max *= 2;
    }
    pwm_max--;
}
void foc_kun::begin(uint8_t AH_channel_temp, uint8_t BH_channel_temp, uint8_t CH_channel_temp)
{
    pwm_mode = 0;
    AH_channel = AH_channel_temp;
    BH_channel = BH_channel_temp;
    CH_channel = CH_channel_temp;
    pinMode(AL, OUTPUT);
    pinMode(BL, OUTPUT);
    pinMode(CL, OUTPUT);
    ledcSetup(AH_channel, pwm_mode, pwm_resolution);
    ledcSetup(BH_channel, pwm_mode, pwm_resolution);
    ledcSetup(CH_channel, pwm_mode, pwm_resolution);
    ledcAttachPin(AH, AH_channel);
    ledcAttachPin(BH, BH_channel);
    ledcAttachPin(CH, CH_channel);
}
void foc_kun::six_step_clear(void)
{
    ledcWrite(AH_channel, 0);
    ledcWrite(BH_channel, 0);
    ledcWrite(CH_channel, 0);
    digitalWrite(BL, LOW);
    digitalWrite(AL, LOW);
    digitalWrite(CL, LOW);
}
void foc_kun::six_step_commutation(uint8_t num)
{
    six_step_clear();
    switch (num)
    {
    case 0:
        six_step_clear();
        ledcWrite(AH_channel, six_step_speed);
        digitalWrite(BL, HIGH);
        break;
    case 1:
        six_step_clear();
        ledcWrite(AH_channel, six_step_speed);
        digitalWrite(CL, HIGH);
        break;
    case 2:
        six_step_clear();
        ledcWrite(BH_channel, six_step_speed);
        digitalWrite(CL, HIGH);
        break;
    case 3:
        six_step_clear();
        ledcWrite(BH_channel, six_step_speed);
        digitalWrite(AL, HIGH);
        break;
    case 4:
        six_step_clear();
        ledcWrite(CH_channel, six_step_speed);
        digitalWrite(AL, HIGH);
        break;
    case 5:
        six_step_clear();
        ledcWrite(CH_channel, six_step_speed);
        digitalWrite(BL, HIGH);
        break;
    default:
        break;
    }
}
void foc_kun::park_inverse_transformation(void)
{
    cosine = cos(theta);
    sine = sin(theta);
    u_alpha = u_d * cosine - u_q * sine;
    u_beta = u_q * cosine + u_d * sine;
}
void foc_kun::clarke_inverse_transformation(void)
{
    u_a = u_alpha;
    u_b = (-1 / 2) * u_alpha + 0.8660254037844386 * u_beta;
    u_c = (-1 / 2) * u_alpha - 0.8660254037844386 * u_beta;
}
void foc_kun::park_transformation(void)
{
    i_d = i_alpha * cosine + i_beta * sine;
    i_q = i_beta * cosine - i_alpha * sine;
}
void foc_kun::clarke_transformation(void)
{
    i_alpha = i_a;
    i_beta = (i_a + i_b * 2) * 0.5773502691896258;
}
void foc_kun::svpwm(void)
{
    ts = 1;
    u1 = u_beta;
    u2 = -0.8660254037844386 * u_alpha - u_beta / 2;
    u3 = 0.8660254037844386 * u_alpha - u_beta / 2;
    uint8_t sector = (u1 > 0.0) + ((u2 > 0.0) << 1) + ((u3 > 0.0) << 2);
    switch (sector)
    {
    case 5:
        t4 = u3;
        t6 = u1;
        t_sum = t4 + t6;
        if (t_sum > ts)
        {
            k_svpwm = ts / t_sum;
            t4 = k_svpwm * t4;
            t6 = k_svpwm * t6;
        }
        t7 = (ts - t4 - t6) / 2;
        t_a = t4 + t6 + t7;
        t_b = t6 + t7;
        t_c = t7;
        break;
    case 1:
        t2 = -u3;
        t6 = -u2;
        t_sum = t2 + t6;
        if (t_sum > ts)
        {
            k_svpwm = ts / t_sum;
            t2 = k_svpwm * t2;
            t6 = k_svpwm * t6;
        }
        t7 = (ts - t2 - t6) / 2;
        t_a = t6 + t7;
        t_b = t2 + t6 + t7;
        t_c = t7;
        break;
    case 3:
        t2 = u1;
        t3 = u2;
        t_sum = t2 + t3;
        if (t_sum > ts)
        {
            k_svpwm = ts / t_sum;
            t2 = k_svpwm * t2;
            t3 = k_svpwm * t3;
        }
        t7 = (ts - t2 - t3) / 2;
        t_a = t7;
        t_b = t2 + t3 + t7;
        t_c = t3 + t7;
        break;
    case 2:
        t1 = -u1;
        t3 = -u3;
        t_sum = t1 + t3;
        if (t_sum > ts)
        {
            k_svpwm = ts / t_sum;
            t1 = k_svpwm * t1;
            t3 = k_svpwm * t3;
        }
        t7 = (ts - t1 - t3) / 2;
        t_a = t7;
        t_b = t3 + t7;
        t_c = t1 + t3 + t7;
        break;
    case 6:
        t1 = u2;
        t5 = u3;
        t_sum = t1 + t5;
        if (t_sum > ts)
        {
            k_svpwm = ts / t_sum;
            t1 = k_svpwm * t1;
            t5 = k_svpwm * t5;
        }
        t7 = (ts - t1 - t5) / 2;
        t_a = t5 + t7;
        t_b = t7;
        t_c = t1 + t5 + t7;
        break;
    case 4:
        t4 = -u2;
        t5 = -u1;
        t_sum = t4 + t5;
        if (t_sum > ts)
        {
            k_svpwm = ts / t_sum;
            t4 = k_svpwm * t4;
            t5 = k_svpwm * t5;
        }
        t7 = (ts - t4 - t5) / 2;
        t_a = t4 + t5 + t7;
        t_b = t7;
        t_c = t5 + t7;
        break;
    default:
        1;
        break;
    }
}
pwm_output foc_kun::turn_to(float angle_temp)
{
    u_d = 0.5;
    u_q = 0;
    theta = angle_temp;
    pwm_output result;
    svpwm();
    park_inverse_transformation();
    result.a = t_a;
    result.b = t_b;
    result.c = t_c;
    return result;
}
void foc_kun::test(float angle_temp)
{
    u_a = cos(angle_temp);
}

