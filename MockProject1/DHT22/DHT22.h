#ifndef DHT22_H
#define DHT22_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define DATA_BYTES  5

bool DHT_Init(const char *filename);
bool DHT_Read_Humidity(float *humidity);
bool DHT_Read_Temperature(float *temp);

#endif 

