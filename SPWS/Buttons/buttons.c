#include "buttons.h"

void buttons_init(void) 
{
    printf("[BUTTONS] Khoi tao nut nhan\n");
    printf("Nut 1: Chuyen che do\n");
    printf("Nut 2: Tuoi thu cong\n");
}

int check_buttons(void) 
{
    char input[10];
    printf("\nNhan [1] chuyen che do, [2] tuoi thu cong, [Enter] bo qua: ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) 
    {
        input[strcspn(input, "\n")] = '\0';
        
        if (strcmp(input, "1") == 0) {
            printf("-> Nut 1 duoc nhan!\n");
            return 1;
        } else if (strcmp(input, "2") == 0) {
            printf("-> Nut 2 duoc nhan!\n");
            return 2;
        } else if (strlen(input) == 0) {
            return 0;
        } else {
            printf("-> Nut khong hop le, bo qua\n");
            return 0;
        }
    }
    return 0;
}