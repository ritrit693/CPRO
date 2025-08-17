#include "config.h"
#include "sensors.h"
#include "actuators.h"
#include "buttons.h"
#include "watering.h"

sensor_data_t g_sensors;
system_state_t g_state;

void show_status(void) 
{
    printf("\n=== TRANG THAI HE THONG ===\n");
    printf("Che do: %s\n", (g_state.mode == MODE_AUTO) ? "TU DONG" : "THU CONG");
    printf("Do am dat: %.1f%%\n", g_sensors.soil_moisture);
    printf("Nhiet do: %.1f°C\n", g_sensors.temperature);
    printf("Bom nuoc: %s\n", (g_state.pump == PUMP_ON) ? "BAT" : "TAT");
    printf("Trang thai: %s\n", g_state.is_watering ? "DANG TUOI" : "KHONG TUOI");

    switch (g_state.led) 
    {
        case LED_NORMAL:
            printf("LED: XANH (Binh thuong)\n");
            break;
        case LED_WATERING:
            printf("LED: VANG (Dang tuoi)\n");
            break;
        case LED_LOW_MOISTURE:
            printf("LED: DO NHAP NHAY (Canh bao do am thap!)\n");
            break;
        case LED_ERROR:
            printf("LED: DO (Loi cam bien!)\n");
            break;
    }
    printf("===========================\n");
}

void handle_buttons(void) 
{
    printf("\n=== DIEU KHIEN NUT NHAN ===\n");
    printf("Che do hien tai: %s\n", (g_state.mode == MODE_AUTO) ? "TU DONG" : "THU CONG");
    
    int button = check_buttons();
    
    if (button == 1) 
    {
        if (g_state.mode == MODE_AUTO) 
        {
            g_state.mode = MODE_MANUAL;
            printf("==> DA CHUYEN SANG CHE DO THU CONG\n");
            if (g_state.is_watering) 
            {
                pump_off();
                g_state.pump = PUMP_OFF;
                g_state.is_watering = false;
                printf("==> DA DUNG TUOI TU DONG\n");
            }
        } 
        else 
        {
            g_state.mode = MODE_AUTO;
            printf("==> DA CHUYEN SANG CHE DO TU DONG\n");
        }
        
    } else if (button == 2) 
    {
        if (g_state.mode == MODE_MANUAL) 
        {
            printf("==> BAT DAU TUOI THU CONG\n");
            process_manual_watering(&g_state);
        } 
        else 
        {
            printf("==> LOI: Nut 2 chi hoat dong o che do THU CONG\n");
            printf("    Hien tai dang o che do TU DONG\n");
        }
    }
    
    printf("===========================\n");
}

void main_cycle(void) 
{
    read_sensors(&g_sensors);

    if (!is_data_valid(&g_sensors)) 
    {
        printf("ERROR: Du lieu cam bien khong hop le!\n");
        g_state.led = LED_ERROR;
        led_update(g_state.led);
        return;
    }

    if (g_state.mode == MODE_AUTO) 
    {
        printf("\n>> CHE DO TU DONG HOAT DONG\n");
        process_auto_watering(&g_sensors, &g_state);
    } 
    else 
    {
        printf("\n>> CHE DO THU CONG\n");
        printf("Cho lenh dieu khien tu nguoi dung...\n");
    }

    led_state_t new_led = get_led_state(&g_sensors, &g_state);
    if (new_led != g_state.led) 
    {
        g_state.led = new_led;
        led_update(g_state.led);
    }

    show_status();

    handle_buttons();

    printf("\n>> KIEM TRA LAI SAU KHI XU LY NUT NHAN...\n");
    if (g_state.mode == MODE_AUTO) 
    {
        printf(">> XU LY LAI CHE DO TU DONG\n");
        process_auto_watering(&g_sensors, &g_state);

        led_state_t final_led = get_led_state(&g_sensors, &g_state);
        if (final_led != g_state.led) 
        {
            g_state.led = final_led;
            led_update(g_state.led);
        }

        show_status();
    }
    
    printf("\n>> CHU KY HOAN THANH!\n");
}

void system_init(void) 
{
    printf("================================================\n");
    printf("  SPWS - Smart Plant Watering System\n");
    printf("  He thong tuoi cay thong minh\n");
    printf("================================================\n");

    sensors_init();
    actuators_init();
    buttons_init();

    g_state.mode = MODE_AUTO;
    g_state.pump = PUMP_OFF;
    g_state.led = LED_NORMAL;
    g_state.is_watering = false;
    g_state.watering_start = 0;
    
    printf("\nCau hinh he thong:\n");
    printf("- Nguong tuoi: %.0f%% (do am thap)\n", MIN_MOISTURE);
    printf("- Nguong dung: %.0f%% (do am du)\n", MAX_MOISTURE);
    printf("- Thoi gian tuoi toi da: %d giay\n", MAX_WATERING_TIME);
    printf("- Thoi gian tuoi thu cong: %d giay\n", MANUAL_TIME);
    printf("\nMau sac LED:\n");
    printf("- XANH: He thong binh thuong\n");
    printf("- VANG: Dang tuoi nuoc\n");
    printf("- DO NHAP NHAY: Canh bao do am thap\n");
    printf("- DO: Loi cam bien\n");
    printf("================================================\n");
    printf("He thong da san sang hoat dong!\n");
    printf("================================================\n");
}

int main(void) 
{
    system_init();
    
    int cycle = 1;
    while (1) 
    {
        printf("\n************* CHU KY %d *************\n", cycle++);
        main_cycle();
        
        printf("\n[SYSTEM] Nhan Enter de tiep tuc chu ky tiep theo...\n");
        char temp[10];
        fgets(temp, sizeof(temp), stdin);

        if (cycle > 15) 
        {
            printf("\n[SYSTEM] Demo ket thuc sau 15 chu ky\n");
            break;
        }
    }
    
    pump_off();
    printf("[SYSTEM] He thong da tat an toan\n");
    return 0;
}