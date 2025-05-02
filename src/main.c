#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db.h"
#include "callback.h"
#include "util.h"
#include <sys/time.h>
#include <unistd.h>

void dot_databases(GNCDB *db);

void read_config(const char *filename);
double get_time_in_seconds();

// 全局变量，数据库文件信息
char *fileName = "GNCDB.dat";
char *filePath = "";

// 全局变量，控制打印要求
int ifHeaders = 0;
int ifTimer = 0;
int ifTrace = 0;
int ifEcho = 0;
int ifChange = 0;
int ifCrnl = 0;

extern int columnWidth;
char opDir[1024]; // 运行中的目录
char *prompt;
char *onceOption = NULL;
char *colSeparator = "|";  // 列分隔符，默认为制表符
char *rowSeparator = "\n"; // 行分隔符，默认为换行符
extern int headerPrinted;
extern int ifExcel;
extern FILE *outputFile;
GNCDB *db = NULL;

int main()
{
    int rc;
    char sql[4096] = {0};   // 存储完整的SQL命令
    char input[1024] = {0}; // 每次输入的缓冲区
    update_config_value("output", "stdout");
    // 初始化提示符
    prompt = strdup("AxDB> ");

    // 读取配置文件
    read_config("config.ini");

    // 打开数据库
    rc = db_open(fileName, &db);
    if (rc == 0)
    {
        printf("GNCDB version 1.0.0 2025-02-18 16:09 (UTF-8 console I/O)\n"
               "Enter \".help\" for usage hints.\n"
               "Use \".open FILENAME\" to reopen on a persistent database.\n");
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
            read_config("config.ini");
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
                rc = db_exec(db, sql, callback, NULL, NULL);
                set_print_column_names(ifHeaders);
            }
            else
            {
                rc = db_exec(db, sql, callback_echo_off, NULL, NULL);
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

    return 0;
}

// 读取配置文件并解析
void read_config(const char *configname)
{
    FILE *file = fopen(configname, "r");
    if (file == NULL)
    {
        perror("Unable to open config file");
        return;
    }

    char line[256]; // 用于存储每行内容
    int line_number = 0;

    // 逐行读取配置文件
    while (fgets(line, sizeof(line), file))
    {
        line_number++;

        // 当读取到第二行时，解析echo
        if (line_number == 2)
        {
            // 去掉换行符
            line[strcspn(line, "\n")] = 0;

            // 根据第二行的内容设置ifEcho
            if (strcmp(line, "echo=off") == 0)
            {
                ifEcho = 0; // 不回显
            }
            else if (strcmp(line, "echo=on") == 0)
            {
                ifEcho = 1; // 回显
            }
            continue;
        }
        // 当读取到第三行时，解析headers
        if (line_number == 3)
        {
            // 去掉换行符
            line[strcspn(line, "\n")] = 0;

            // 根据第三行的内容设置ifHeaders
            if (strcmp(line, "headers=off") == 0)
            {
                ifHeaders = 0; // 不打印列名
            }
            else if (strcmp(line, "headers=on") == 0)
            {
                ifHeaders = 1; // 打印列名
            }
            continue;
        }
        // 读到第5行解析output
        if (line_number == 5)
        {
            if (strstr(line, "output=") != NULL)
            {
                char *outputValue = strstr(line, "=") + 1;
                // 去除换行符
                size_t len = strlen(outputValue);
                if (len > 0 && outputValue[len - 1] == '\n')
                {
                    outputValue[len - 1] = '\0';
                }
                if (strcmp(outputValue, "stdout") == 0)
                {
                    outputFile = NULL;
                    ifExcel = 0;
                }else if(strcmp(outputValue, "excel") == 0)
                {
                    outputFile = fopen("output.csv", "w");
                    ifExcel = 1;
                }
                else
                {
                    outputFile = fopen(outputValue, "w");
                    ifExcel = 1;
                }
            }
        }
        // 读到第6行解析colSeparator
        if (line_number == 6)
        {
            if (strstr(line, "colseparator=") != NULL)
            {
                char *colSeparatorValue = strstr(line, "=") + 1;
                // 去除换行符
                size_t len = strlen(colSeparatorValue);
                if (len > 0 && colSeparatorValue[len - 1] == '\n')
                {
                    colSeparatorValue[len - 1] = '\0';
                }
                colSeparator = strdup(colSeparatorValue);
                if (strcmp(colSeparatorValue, "\\n") == 0)
                {
                    if (ifCrnl)
                    {
                        colSeparator = "\r\n";
                    } // 转换换行符
                    else
                        colSeparator = "\n";
                }
                else if (strcmp(colSeparatorValue, "\\t") == 0)
                {
                    colSeparator = "\t";
                }
                else
                {
                    colSeparator = strdup(colSeparatorValue);
                }
            }
        }
        // 读到第7行解析rowSeparator
        if (line_number == 7)
        {
            if (strstr(line, "rowseparator=") != NULL)
            {
                char *rowSeparatorValue = strstr(line, "=") + 1;
                // 去除换行符
                size_t len = strlen(rowSeparatorValue);
                if (len > 0 && rowSeparatorValue[len - 1] == '\n')
                {
                    rowSeparatorValue[len - 1] = '\0';
                }

                rowSeparator = strdup(rowSeparatorValue);
                if (strcmp(rowSeparatorValue, "\\n") == 0)
                {
                    if (ifCrnl)
                    {
                        rowSeparator = "\r\n";
                    } // 转换换行符
                    else
                        rowSeparator = "\n";
                }
                else if (strcmp(rowSeparatorValue, "\\t") == 0)
                {
                    rowSeparator = "\t";
                }
                else
                {
                    rowSeparator = strdup(rowSeparatorValue);
                }
            }
        }
        // 读到第8行读取columnWidth
        if (line_number == 8)
        {
            if (strstr(line, "columnWidth=") != NULL)
            {
                char *columnWidthValue = strstr(line, "=") + 1;
                // 去除换行符
                size_t len = strlen(columnWidthValue);
                if (len > 0 && columnWidthValue[len - 1] == '\n')
                {
                    columnWidthValue[len - 1] = '\0';
                }
                columnWidth = atoi(columnWidthValue);
            }
        }
        // 读到第9行解析timer
        if (line_number == 9)
        {
            // 去掉换行符6
            line[strcspn(line, "\n")] = 0;

            // 根据第九行的内容设置ifTimer
            if (strcmp(line, "timer=off") == 0)
            {
                ifTimer = 0; // 不打印时间
            }
            else if (strcmp(line, "timer=on") == 0)
            {
                ifTimer = 1; // 打印时间
            }
            continue;
        }
        // 读到第10行解析crnl
        if (line_number == 10)
        {
            // 去掉换行符
            line[strcspn(line, "\n")] = 0;

            // 根据第十行的内容设置ifCrnl
            if (strcmp(line, "crnl=off") == 0)
            {
                ifCrnl = 0; // 不转换换行符
            }
            else if (strcmp(line, "crnl=on") == 0)
            {
                ifCrnl = 1; // 转换换行符
            }
            continue;
        }
    }

    fclose(file);
}

// 获取当前时间戳
double get_time_in_seconds()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}