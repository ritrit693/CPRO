#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define MIN_MOISTURE 30.0f
#define MAX_MOISTURE 70.0f
#define MAX_WATERING_TIME 60
#define MANUAL_TIME 10

typedef enum {
    MODE_AUTO,
    MODE_MANUAL
} system_mode_t;

typedef enum {
    PUMP_OFF,
    PUMP_ON
} pump_state_t;

typedef enum {
    LED_NORMAL,
    LED_WATERING,
    LED_LOW_MOISTURE,
    LED_ERROR
} led_state_t;

typedef struct {
    float soil_moisture;
    float temperature;
} sensor_data_t;

typedef struct {
    system_mode_t mode;
    pump_state_t pump;
    led_state_t led;
    bool is_watering;
    time_t watering_start;
} system_state_t;

#endif