/*
参考文章:https://blog.csdn.net/qq_35947329/article/details/115483413?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522168621046016800213033417%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=168621046016800213033417&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-2-115483413-null-null.142^v88^control_2,239^v2^insert_chatgpt&utm_term=foc&spm=1018.2226.3001.4187
*/
#ifndef foc_kun_h
#define foc_kun_h
#include <Arduino.h>
    typedef struct{
        float a,b,c;
    } pwm_output;
class foc_kun
{
private:
    uint8_t AH, AL, BH, BL, CH, CL, pwm_mode, pwm_resolution, AH_channel, BH_channel, CH_channel;
    uint32_t pwm_freq, six_step_speed;
    uint32_t pwm_max;
    // float principal_vector_modulus,principal_vector_angle;
    float u_alpha, u_beta, i_alpha, i_beta,
        u_q, u_d, i_d, i_q, theta, sine, cosine,
        i_a, i_b, i_c, u_a, u_b, u_c,u1,u2,u3,
        t_a, t_b, t_c, ts, k_svpwm;
    float t0,t1,t2,t3,t4,t5,t6,t7,t_sum;

public:

    foc_kun(void);
    foc_kun(uint8_t AH_temp, uint8_t AL_temp, uint8_t BH_temp, uint8_t BL_temp, uint8_t CH_temp, uint8_t CL_temp);
    void begin(uint8_t AH_channel_temp, uint8_t BH_channel_temp, uint8_t CH_channel_temp);
    void six_step_clear(void);
    void six_step_commutation(uint8_t num);
    void clarke_transformation(void);
    void park_transformation(void);
    void park_inverse_transformation(void);
    void clarke_inverse_transformation(void);
    void svpwm(void);
    pwm_output turn_to(float angle_temp);
    void test(float angle_temp);
};
#endif
