#include "Test_Service.h"

uint8_t dhtData[DHTDATA];

void Create_Data_Test(const char *filename, float temp, float humidity)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
    {
        perror("Failed to open file");
        return;
    } 
    uint16_t raw_humidity = (uint16_t)(humidity * 10);
    dhtData[0] = (raw_humidity >> 8) & 0xFF;
    dhtData[1] = raw_humidity & 0xFF;
    
    int16_t sign = (temp < 0);
    if (temp < 0) temp = -temp;
    int16_t raw_temp = (int16_t)((temp) * 10);
    dhtData[2] = (raw_temp >> 8) & 0x7F;
    if (sign) dhtData[2] |= 0x80;
    dhtData[3] = raw_temp & 0xFF;
    
    dhtData[4] = (dhtData[0] + dhtData[1] + dhtData[2] + dhtData[3]) & 0xFF;

    for (int i = 0; i < DHTDATA; i++) 
    {
        for (int j = 7; j >= 0; j--) 
        {
            uint8_t bit = (dhtData[i] >> j) & 0x01;
            fprintf(file, "%u\n", bit);
        }
    }
    fclose(file);
}    