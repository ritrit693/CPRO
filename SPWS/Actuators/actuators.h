#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "config.h"

void actuators_init(void);
void pump_on(void);
void pump_off(void);
void led_update(led_state_t state);

#endif