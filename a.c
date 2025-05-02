#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

// 模拟当前打开的数据库文件名
const char *current_db_file = "current_database.db";

// 备份数据库文件的函数
int backup_database(const char *sourceFileName, const char *backupFileName) {
    if (sourceFileName == NULL || backupFileName == NULL) {
        printf("Error: Invalid file names for backup.\n");
        return -1;
    }

    // 打开源数据库文件
    FILE *sourceFile = fopen(sourceFileName, "rb");
    if (sourceFile == NULL) {
        perror("Error opening source database file");
        return -1;
    }

    // 打开备份文件
    FILE *backupFile = fopen(backupFileName, "wb");
    if (backupFile == NULL) {
        perror("Error opening backup file");
        fclose(sourceFile);
        return -1;
    }

    // 进行文件复制
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0) {
        fwrite(buffer, 1, bytesRead, backupFile);
    }

    // 关闭文件
    fclose(sourceFile);
    fclose(backupFile);

    printf("Database backup created successfully: %s -> %s\n", sourceFileName, backupFileName);
    return 0;
}

// 解析并处理 .backup 命令
int process_backup_command(const char *command) {
    char *commandCopy = strdup(command);
    char *token = strtok(commandCopy, " ");  // 获取第一个参数

    // 忽略 .backup 前缀
    token = strtok(NULL, " ");

    // 获取 .backup 命令后的参数
    char *sourceFileName = NULL;
    char *backupFileName = NULL;

    if (token != NULL) {
        sourceFileName = token;  // 获取第一个文件名
        token = strtok(NULL, " "); // 获取第二个文件名
        if (token != NULL) {
            backupFileName = token;  // 获取第二个文件名
        }
    }

    // 判断备份文件数目
    if (sourceFileName == NULL) {
        // 如果没有指定源文件，则使用当前数据库文件
        sourceFileName = current_db_file;
    }

    if (backupFileName == NULL) {
        // 如果没有指定备份文件，则使用默认备份文件名（如添加时间戳）
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char defaultBackupFile[256];
        snprintf(defaultBackupFile, sizeof(defaultBackupFile), "%s_backup_%d-%02d-%02d_%02d-%02d-%02d.db",
                 sourceFileName, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
                 tm.tm_hour, tm.tm_min, tm.tm_sec);
        backupFileName = defaultBackupFile; // 设定备份文件名
    }

    // 执行备份
    int result = backup_database(sourceFileName, backupFileName);
    free(commandCopy); // 释放复制的命令字符串
    return result;
}
