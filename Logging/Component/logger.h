#ifndef LOGGER_H
#define LOGGER_H
// include header files
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

//  Data type
typedef enum {
    LOG_EMERGENCY = 0,
    LOG_ALERT     = 1,
    LOG_CRITICAL  = 2,
    LOG_ERROR     = 3,
    LOG_WARNING   = 4,
    LOG_NOTICE    = 5,
    LOG_INFO      = 6,
    LOG_DEBUG     = 7
} LogLevel;
// Function prototype
// Khởi tạo logger, chỉ định mức log tối thiểu và tên file log (NULL nếu không lưu file)
bool logger_init(LogLevel min_level, const char *log_filename);

// Đóng logger (giải phóng tài nguyên)
void logger_close(void);

// Đổi mức lọc log động
void logger_set_level(LogLevel min_level);

// Hàm ghi log chính với đầy đủ tham số
void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...);

// Macro tiện lợi tự động truyền FILE và LINE
#define log_message(level, fmt, ...) \
    logger_log(level, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif // LOGGER_H
