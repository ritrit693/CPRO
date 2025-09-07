#include "DHT22.h"

static FILE *fp = NULL;
static uint8_t rawData[DATA_BYTES];
static bool data_valid = false;

bool DHT_Init(const char *filename)
{
    fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        perror("Failed to open file");
        return false;
    }

    for (int i = 0; i < DATA_BYTES; i++) 
    {
        rawData[i] = 0;
        for (int j = 7; j >= 0; j--) 
        {
            int ch = fgetc(fp);
            while (ch == '\n')
            ch = fgetc(fp);
            rawData[i] |= (ch == '1') << j;
        }
    }
    fclose(fp);

    uint8_t checksum = (rawData[0] + rawData[1] + rawData[2] + rawData[3]);
    data_valid = (checksum == rawData[4]);

    if (!data_valid)
        printf("Checksum error: calc %02X, recv %02X\n", checksum, rawData[4]);

    return data_valid;
}

bool DHT_Read_Temperature(float *temp)
{
    if(!temp || !data_valid) return false;

    uint16_t rawTemp = (rawData[2] & 0x7F) << 8 | rawData[3];
    *temp = rawTemp / 10.0f;
    if (rawData[2] & 0x80) *temp = -*temp;
    
    return true;
}

bool DHT_Read_Humidity(float *humidity)
{
    if(!humidity || !data_valid) return false;
    uint16_t rawHumidity = (rawData[0] << 8) | rawData[1];
    *humidity = rawHumidity / 10.0f;
    return true;
}
