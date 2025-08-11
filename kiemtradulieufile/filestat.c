#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;

    // Kiểm tra tham số
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // Lấy thông tin file bằng lstat
    if (lstat(argv[1], &fileStat) == -1) {
        perror("lstat");
        return 1;
    }

    // In thông tin
    printf("File Path: %s\n", argv[1]);

    // Loại file
    printf("File Type: ");
    if (S_ISREG(fileStat.st_mode))
        printf("Regular File\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("Directory\n");
    else if (S_ISLNK(fileStat.st_mode))
        printf("Symbolic Link\n");
    else
        printf("Other\n");

    // Kích thước
    printf("Size: %ld bytes\n", fileStat.st_size);

    // Thời gian sửa đổi cuối
    char timeBuf[100];
    struct tm *timeinfo = localtime(&fileStat.st_mtime);
    strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified: %s\n", timeBuf);

    return 0;
}
