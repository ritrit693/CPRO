#ifndef SENSORS_H
#define SENSORS_H

#include "config.h"

void sensors_init(void);
void read_sensors(sensor_data_t* data);
bool is_data_valid(const sensor_data_t* data);

#endif