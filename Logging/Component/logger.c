#include "logger.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
//local data type
// Giữ trạng thái module bằng static biến
static LogLevel s_min_level = LOG_INFO;
static FILE *s_log_file = NULL;

// Các chuỗi tương ứng mức log
static const char* LOG_LEVEL_NAMES[] = {
    "EMERGENCY", "ALERT", "CRITICAL", "ERROR",
    "WARNING",   "NOTICE", "INFO", "DEBUG"
};
// local function prototype
// Hàm lấy chuỗi timestamp [YYYY-MM-DD HH:MM:SS]
static void get_timestamp(char *buf, size_t len) {
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    strftime(buf, len, "%Y-%m-%d %H:%M:%S", lt);
}

static bool is_error_log(LogLevel level) {
    return level <= LOG_ERROR;
}

// global function definition
// Init logger: thiết lập mức log tối thiểu và mở file log (nếu có)
bool logger_init(LogLevel min_level, const char *log_filename) {
    s_min_level = min_level;
    if (log_filename != NULL) {
        s_log_file = fopen(log_filename, "a");
        if (!s_log_file) {
            // Nếu mở file thất bại, báo lỗi ra stderr
            fprintf(stderr, "Failed to open log file %s\n", log_filename);
            return false;
        }
    }
    return true;
}

// Đổi mức lọc log tại runtime
void logger_set_level(LogLevel min_level) {
    s_min_level = min_level;
}

// Đóng logger, đóng file nếu có
void logger_close(void) {
    if (s_log_file) {
        fclose(s_log_file);
        s_log_file = NULL;
    }
}

// Hàm ghi log chính
void logger_log(LogLevel level, const char *file, int line, const char *fmt, ...) {
    // Lọc theo level
    if (level > s_min_level) return;
    char timestamp[20];
    get_timestamp(timestamp, sizeof(timestamp));

    char message[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof(message), fmt, args);
    va_end(args);

    // Định dạng log
    char log_line[1200];
    snprintf(log_line, sizeof(log_line), "[%s] [%s] [%s:%d] - %s\n",
        timestamp, LOG_LEVEL_NAMES[level], file, line, message);

    // Ghi ra console: stderr cho error trở lên, stdout cho mức thấp hơn
    if (is_error_log(level))
        fprintf(stderr, "%s", log_line);
    else
        fprintf(stdout, "%s", log_line);

    // Ghi vào file nếu có
    if (s_log_file) {
        fprintf(s_log_file, "%s", log_line);
        fflush(s_log_file); // Đảm bảo ghi ngay
    }
}
