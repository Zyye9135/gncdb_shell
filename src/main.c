#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gncdb.h"
#include "callback.h"
#include "util.h"
#include <sys/time.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

// 默认配置
const char *DEFAULT_CONFIG = 
    "version=1.0.0\n"
    "echo=off\n"
    "headers=on\n"
    "output=stdout\n"
    "colseparator=|\n"
    "rowseparator=\\n\n"
    "columnWidth=20\n"
    "timer=off\n"
    "crnl=off\n";

void dot_databases(GNCDB *db);

void read_config(const char *filename);
double get_time_in_seconds();

// 全局变量，数据库文件信息
char *fileName = "";
char *filePath = "";
char config_absolute_path[1024] = {0}; // 配置文件的绝对路径

// 全局变量，控制打印要求
int ifHeaders = 0;
int ifTimer = 0;
int ifTrace = 0;
int ifEcho = 0;
int ifChange = 0;
int ifCrnl = 0;
int ifExcel = 0;
int columnWidth = 15;
char opDir[1024]; // 运行中的目录
char *prompt;
char *onceOption = NULL;
char *colSeparator = "|";  // 列分隔符，默认为制表符
char *rowSeparator = "\n"; // 行分隔符，默认为换行符
extern int headerPrinted;
extern FILE *outputFile;
GNCDB *db = NULL;

// 打印配置信息
void show_config(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open config file: %s\n", filename);
        return;
    }

    char line[256];      // 用于存储每一行的内容
    int line_number = 1; // 记录当前行号

    while (fgets(line, sizeof(line), file))
    {
        // 跳过前1行（只读取第2至第8行）
        if (line_number < 2 || line_number > 8)
        {
            line_number++;
            continue;
        }

        // 去掉行末的换行符
        line[strcspn(line, "\n")] = 0;

        // 解析键值对
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key && value)
        {
            printf("%-*s: %s\n", 14, key, value);
        }

        line_number++;
    }

    fclose(file);
}

// 打印版本信息
void show_first_line(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open config file: %s\n", filename);
        return;
    }

    char line[256]; // 用于存储每一行的内容

    // 读取第一行
    if (fgets(line, sizeof(line), file))
    {
        // 去掉行末的换行符
        line[strcspn(line, "\n")] = 0;

        // 输出第一行的内容
        printf("%s\n", line);
    }
    else
    {
        fprintf(stderr, "Failed to read the first line\n");
    }

    fclose(file);
}

// 生成临时数据库文件名
char* generate_temp_db_name() {
    time_t now;
    time(&now);
    char* temp_name = (char*)malloc(50);
    sprintf(temp_name, "temp_%ld.dat", now);
    return temp_name;
}

// 清理临时数据库文件
void cleanup_temp_dbs() {
    DIR *dir;
    struct dirent *entry;
    char* current_db = NULL;
    
    // 获取当前临时数据库名
    if (fileName && strstr(fileName, "temp_") == fileName) {
        current_db = strdup(fileName);
    }
    
    dir = opendir(".");
    if (dir == NULL) {
        return;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "temp_") == entry->d_name && 
            strstr(entry->d_name, ".dat") != NULL) {
            // 跳过当前使用的临时数据库
            if (current_db && strcmp(entry->d_name, current_db) == 0) {
                continue;
            }
            // 删除其他临时数据库
            remove(entry->d_name);
        }
    }
    
    closedir(dir);
    if (current_db) {
        free(current_db);
    }
}

// 初始化配置文件
void init_config_file() {
    char current_path[1024];
    if (getcwd(current_path, sizeof(current_path)) == NULL) {
        perror("getcwd() error");
        return;
    }
    
    // 构建配置文件的绝对路径
    snprintf(config_absolute_path, sizeof(config_absolute_path), "%s/gncdb_config.ini", current_path);
    
    // 检查配置文件是否存在
    if (access(config_absolute_path, F_OK) == -1) {
        // 如果文件不存在，创建并写入默认配置
        FILE *file = fopen(config_absolute_path, "w");
        if (file == NULL) {
            perror("Error creating config file");
            return;
        }
        
        // 写入默认配置
        fprintf(file, "[output]\n");
        fprintf(file, "format=stdout\n");
        fprintf(file, "headers=1\n");
        fprintf(file, "echo=0\n");
        fprintf(file, "trace=0\n");
        fprintf(file, "excel=0\n");
        fprintf(file, "change=0\n");
        
        fclose(file);
        printf("Created default config file at: %s\n", config_absolute_path);
    }
}

int main()
{
    int rc;
    char sql[4096] = {0};   // 存储完整的SQL命令
    char input[1024] = {0}; // 每次输入的缓冲区
    
    // 检测并创建 "log" 文件夹
    struct stat statbuf;
    if (stat("log", &statbuf) != 0) { // 检查 "log" 文件夹是否存在
        if (mkdir("log", 0755) != 0) { // 如果不存在，则创建文件夹
            perror("log:mkdir failed");
            return 1; // 返回错误代码
        }
    }
    
    // 初始化配置文件
    init_config_file();
    
    // 生成新的临时数据库名
    fileName = generate_temp_db_name();
    
    // 清理旧的临时数据库
    cleanup_temp_dbs();
    
    update_config_value("output", "stdout");
    // 初始化提示符
    prompt = strdup("AxDB> ");

    // 读取配置文件
    read_config(config_absolute_path);

    // 打开数据库
    rc = GNCDB_open(&db, fileName);
    if (rc == 0)
    {
        printf("GNCDB version 1.0.0 2025-02-18 16:09 (UTF-8 console I/O)\n"
               "Enter \".help\" for usage hints.\n"
               "Use \".open FILENAME\" to reopen on a persistent database.\n"
               "Current temporary database: %s\n", fileName);
        getcwd(opDir, sizeof(opDir));
    }
    else
    {
        printf("Error opening database, return code: %d\n", rc);
        return 1;
    }

    // 命令行交互
    while (1)
    {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break; // 读取失败或 EOF
        }

        // 去除换行符
        input[strcspn(input, "\n")] = 0;

        // 如果 SQL 语句以 '.' 开头，则调用 utils.c 中的函数
        if (input[0] == '.')
        {
            if (strncmp(input, ".open", 5) == 0)
            {
                open_database(input + 6, &db);
                continue;
            }
            else if (strncmp(input, ".prompt", 7) == 0)
            {
                // 处理 .prompt 命令的逻辑
                char *new_prompt = strdup(input + 8);
                if (new_prompt)
                {
                    free(prompt); // 释放之前的提示符字符串
                    prompt = new_prompt;
                    printf("Prompt changed to: %s\n", prompt);
                }
                else
                {
                    printf("Error: Unable to allocate memory for new prompt.\n");
                }
                continue; // 跳过 SQL 处理，直接继续下一次输入
            }
            else
            {
                dot_command(input, db); // 调用 utils.c 中的处理函数
                continue;               // 跳过 SQL 处理，直接继续下一次输入
            }
        }

        // 拼接输入到 SQL 缓冲区
        if (strlen(sql) > 0)
        {
            strcat(sql, " "); // 在每行之间添加空格
        }
        strcat(sql, input);

        // 检查SQL是否结束（检测分号）
        if (strchr(sql, ';') != NULL)
        {
            // 执行 SQL 命令
            set_print_column_names(ifHeaders);
            headerPrinted = 0;
            read_config(config_absolute_path);
            // 记录开始时间
            // 去除 SQL 开头的空格
            char *trimmed_sql = sql;
            while (*trimmed_sql == ' ')
            {
                trimmed_sql++;
            }
            if (ifTrace && strncasecmp(trimmed_sql, "SELECT", 6) == 0)
            {
                printf("%s\n", sql); // 输出执行的 SQL 语句
            }
            if (ifEcho)
            {
                printf("%s\n", sql);
            }
            double start_time = get_time_in_seconds();
            // 执行 SQL 语句
            // 打开文件用于存储查询结果
            if (ifExcel)
            {
                if (open_output_file("output.csv") != 0)
                {
                    printf("Error opening output file.\n");
                    continue;
                }
            }
            if (ifChange)
            {
                set_print_column_names(1);
                char *errmsg = NULL;
                rc = GNCDB_exec(db, sql, callback, NULL, &errmsg);
                set_print_column_names(ifHeaders);
            }
            else
            {
                rc = GNCDB_exec(db, sql, callback_echo_off, NULL, NULL);
            }
            if (ifExcel)
            {
                close_output_file();
                ifExcel = 0;
                update_config_value("output", "stdout");
            }
            set_output_excel(0);
            // 记录结束时间
            double end_time = get_time_in_seconds();
            if (rc == GNCDB_SUCCESS)
            {
                if (ifTimer)
                {
                    printf("SQL execution took: %.6f seconds\n", end_time - start_time);
                }
            }
            else
            {
                // printf("Error executing SQL, return code: %d\n", rc);
            }

            // 清空 SQL 缓冲区
            memset(sql, 0, sizeof(sql));
        }
    }

    // 释放提示符字符串
    free(prompt);

    // 在程序退出前清理临时数据库
    if (fileName && strstr(fileName, "temp_") == fileName) {
        remove(fileName);
        free(fileName);
    }

    return 0;
}

// 读取配置文件并解析
void read_config(const char *configPath) {
    FILE *file = fopen(configPath, "r");
    if (file == NULL) {
        perror("Error opening config file");
        return;
    }
    
    char line[256];
    char section[64] = "";
    char key[64];
    char value[256];
    
    while (fgets(line, sizeof(line), file)) {
        // 去除行末的换行符
        line[strcspn(line, "\n")] = 0;
        
        // 跳过空行
        if (strlen(line) == 0) continue;
        
        // 处理节名
        if (line[0] == '[' && line[strlen(line)-1] == ']') {
            strncpy(section, line+1, strlen(line)-2);
            section[strlen(line)-2] = '\0';
            continue;
        }
        
        // 处理键值对
        if (sscanf(line, "%[^=]=%s", key, value) == 2) {
            if (strcmp(section, "output") == 0) {
                if (strcmp(key, "format") == 0) {
                    if (strcmp(value, "excel") == 0) {
                        set_output_excel(1);
                    } else {
                        set_output_excel(0);
                    }
                } else if (strcmp(key, "headers") == 0) {
                    set_print_column_names(atoi(value));
                } else if (strcmp(key, "echo") == 0) {
                    ifEcho = atoi(value);
                } else if (strcmp(key, "trace") == 0) {
                    ifTrace = atoi(value);
                } else if (strcmp(key, "excel") == 0) {
                    ifExcel = atoi(value);
                } else if (strcmp(key, "change") == 0) {
                    ifChange = atoi(value);
                }
            }
        }
    }
    
    fclose(file);
}

// 更新配置文件中的值
void update_config_value(const char *key, const char *value) {
    FILE *file = fopen(config_absolute_path, "r+");
    if (file == NULL) {
        perror("Error opening config file for update");
        return;
    }
    
    // 读取整个文件内容
    char content[4096] = "";
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        strcat(content, line);
    }
    
    // 查找并替换键值对
    char *pos = strstr(content, key);
    if (pos != NULL) {
        // 找到键，替换值
        char *value_start = strchr(pos, '=');
        if (value_start != NULL) {
            value_start++; // 移动到值的位置
            char *value_end = strchr(value_start, '\n');
            if (value_end != NULL) {
                // 替换值
                int value_len = strlen(value);
                int old_value_len = value_end - value_start;
                memmove(value_start + value_len, value_end, strlen(value_end) + 1);
                memcpy(value_start, value, value_len);
            }
        }
    }
    
    // 写回文件
    rewind(file);
    fputs(content, file);
    fclose(file);
}

// 获取当前时间戳
double get_time_in_seconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}