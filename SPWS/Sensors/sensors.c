#include "sensors.h"

void sensors_init(void) 
{
    printf("[SENSORS] Khoi tao cam bien\n");
}

void read_sensors(sensor_data_t* data) 
{
    printf("\n=== DOC CAM BIEN ===\n");
    
    printf("Nhap do am dat (0-100%%): ");
    scanf("%f", &data->soil_moisture);
    
    printf("Nhap nhiet do (C): ");
    scanf("%f", &data->temperature);
    
    // Clear input buffer after scanf
    while (getchar() != '\n');
    
    printf("Do am: %.1f%%, Nhiet do: %.1f C\n", 
           data->soil_moisture, data->temperature);
    printf("===================\n");
}

bool is_data_valid(const sensor_data_t* data) 
{
    return (data->soil_moisture >= 0 && data->soil_moisture <= 100);
}