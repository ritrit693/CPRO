#include "actuators.h"

void actuators_init(void) 
{
    printf("[ACTUATORS] Khoi tao bom va LED RGB\n");
    printf("LED: Xanh=Binh thuong, Vang=Dang tuoi, Do nhap nhay=Do am thap, Do=Loi\n");
}

void pump_on(void) 
{
    printf("[PUMP] BAT bom nuoc\n");
}

void pump_off(void) {
    printf("[PUMP] TAT bom nuoc\n");
}

void led_update(led_state_t state) 
{
    switch (state) 
    {
        case LED_NORMAL:
            printf("[LED] XANH - Binh thuong\n");
            break;
        case LED_WATERING:
            printf("[LED] VANG - Dang tuoi\n");
            break;
        case LED_LOW_MOISTURE:
            printf("[LED] DO NHAP NHAY - Do am thap (canh bao)\n");
            
            for (int i = 0; i < 3; i++) 
            {
                printf("        LED: DO SANG... ");
                fflush(stdout);
                usleep(300000);
                printf("TAT... ");
                fflush(stdout);
                usleep(300000);
            }
            printf("NHAP NHAY\n");
            break;
        case LED_ERROR:
            printf("[LED] DO - Loi cam bien\n");
            break;
    }
}