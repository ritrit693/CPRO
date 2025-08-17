#ifndef WATERING_H
#define WATERING_H

#include "config.h"

void process_auto_watering(const sensor_data_t* sensors, system_state_t* state);
void process_manual_watering(system_state_t* state);
led_state_t get_led_state(const sensor_data_t* sensors, const system_state_t* state);

#endif