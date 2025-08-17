#include "watering.h"
#include "actuators.h"
#include "sensors.h"

void process_auto_watering(const sensor_data_t* sensors, system_state_t* state) 
{
    if (state->is_watering) 
    {
        if (sensors->soil_moisture >= MAX_MOISTURE) 
        {
            printf("Do am du (%.1f%% >= %.0f%%), dung tuoi\n", 
                   sensors->soil_moisture, MAX_MOISTURE);
            pump_off();
            state->pump = PUMP_OFF;
            state->is_watering = false;
        }
        else if (time(NULL) - state->watering_start >= MAX_WATERING_TIME) 
        {
            printf("Het thoi gian tuoi (%d giay), dung tuoi\n", MAX_WATERING_TIME);
            pump_off();
            state->pump = PUMP_OFF;
            state->is_watering = false;
        }
        else 
        {
            printf("Dang tuoi... (%.1f%% < %.0f%%)\n", 
            sensors->soil_moisture, MAX_MOISTURE);
        }
    }

    else 
    {
        if (sensors->soil_moisture < MIN_MOISTURE) 
        {
            printf("Do am thap (%.1f%% < %.0f%%), bat dau tuoi\n", 
            sensors->soil_moisture, MIN_MOISTURE);
            pump_on();
            state->pump = PUMP_ON;
            state->is_watering = true;
            state->watering_start = time(NULL);
        }
        else 
        {
            printf("Do am binh thuong (%.1f%% >= %.0f%%)\n", 
            sensors->soil_moisture, MIN_MOISTURE);
        }
    }
}

void process_manual_watering(system_state_t* state) 
{
    if (!state->is_watering) 
    {
        printf("Bat dau tuoi thu cong (%d giay)\n", MANUAL_TIME);
        pump_on();
        state->pump = PUMP_ON;
        state->is_watering = true;

        for (int i = 1; i <= MANUAL_TIME; i++) 
        {
            printf("Tuoi thu cong: %d/%d giay\n", i, MANUAL_TIME);
            sleep(1);
        }
        
        pump_off();
        state->pump = PUMP_OFF;
        state->is_watering = false;
        printf("Hoan thanh tuoi thu cong\n");
    } 
    else 
    {
        printf("He thong dang tuoi, khong the tuoi thu cong\n");
    }
}

led_state_t get_led_state(const sensor_data_t* sensors, const system_state_t* state) 
{
    if (!is_data_valid(sensors)) 
    {
        return LED_ERROR;
    }

    if (state->is_watering) 
    {
        return LED_WATERING;
    }

    if (sensors->soil_moisture < MIN_MOISTURE) 
    {
        return LED_LOW_MOISTURE;
    }
    return LED_NORMAL;
}