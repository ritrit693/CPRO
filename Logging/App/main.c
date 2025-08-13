// main.c
#include "logger.h"

int main(void) {
    // Khởi tạo logger: chỉ log từ LOG_INFO trở lên, ghi ra file "myapp.log"
    logger_init(LOG_INFO, "myapp.log");

    log_message(LOG_DEBUG, "Debug message: var=%d", 42); // Sẽ bị lọc vì < LOG_INFO
    log_message(LOG_INFO, "Info message: app started");
    log_message(LOG_ERROR, "Error message: cannot connect to DB");
    log_message(LOG_EMERGENCY, "System failure!");

    // Đổi mức lọc cho phép debug
    logger_set_level(LOG_DEBUG);
    log_message(LOG_DEBUG, "Debug is now enabled");

    logger_close();
    return 0;
}
