#include "DHT22.h"
#include "Test_Service.h"

#define FILENAME_MAX_LENGTH 100

void menu()
{
    printf("\n=== DHT22 SENSOR SIMULATION ===\n");
    printf("1. Create test data file\n");
    printf("2. Read data from file\n");
    printf("3. Exit\n");
    printf("Choose an option (1-3): ");
}
int main(void)
{   
    int mode;
    char filename[FILENAME_MAX_LENGTH];
    
    while (1) 
    {
        if (menu(), scanf("%d", &mode) != 1 || mode < 1 || mode > 3) 
        {
            while (getchar() != '\n'); 
            printf("Invalid input. Please enter a number between 1 and 3.\n");
            continue;
        }
    
    if (mode == 1) 
    {
        float temp, humidity;
        
        printf("Name the data file: ");
        scanf("%99s", filename);

        while (1) 
        {
            printf("Set temperature (-40...80)C: ");
            if (scanf("%f", &temp) == 1 && temp >= -40 && temp <= 80) 
                break;  
            else 
                printf("Invalid value, please try again.\n");
        }

        while (1) 
        {
            printf("Set humidity (0...100)%%: ");
            if (scanf("%f", &humidity) == 1 && humidity >= 0 && humidity <= 100) 
                break;  
            else 
                printf("Invalid value, please try again.\n");
        }

        Create_Data_Test(filename, temp, humidity);
        printf("Test data file '%s' created with Temperature: %.1f C, Humidity: %.1f%%\n", filename, temp, humidity);
    }
        else if (mode == 2)   
        {
            printf("Data file to read from: ");
            scanf("%s", filename);
        
            printf("[MCU] Sent Start Signal to DHT22\n");
            printf("[MCU] Reading 40 bits of data from %s\n", filename);
            DHT_Init(filename);

            float readTemp, readHumidity;
            if (DHT_Read_Temperature(&readTemp) && DHT_Read_Humidity(&readHumidity)) 
            {
                printf("Data read successfully!\n");
                printf("Temperature: %.1f C\n", readTemp);
                printf("Humidity: %.1f%%\n", readHumidity);
            } 
            else 
            {
                printf("Failed to read temperature and humidity\n");
            }
        }
    else 
    {
        printf("Exiting program.\n");
        break;
    } 
    
    }
    return 0;
}
