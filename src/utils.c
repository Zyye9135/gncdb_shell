#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "callback.h"
#include <unistd.h>
#include <sys/stat.h>
#include "gncdb.h"
#include "help.h"

// 声明外部变量
extern char config_absolute_path[1024];
extern int ifHeaders;
extern int ifTimer;
extern int ifTrace;
extern int ifEcho;
extern int ifChange;
extern int ifCrnl;
extern int ifExcel;
extern FILE *outputFile;
extern char *colSeparator;
extern char *rowSeparator;
extern int columnWidth;

// 声明外部函数
void read_config();
void update_config_value(const char *key, const char *value);
void show_config(const char *filename);
void show_first_line(const char *filename);

// 函数前向声明
void handle_dump_command(const char *command, GNCDB *db);
void handle_indexes_command(const char *command, GNCDB *db);

// extern int ifHeaders;
extern int printColumnNames; // 默认为1，表示打印列名
extern GNCDB *db;
extern char *fileName;
extern char *workPath;
extern char *onceOption;
extern char opDir[1024];
char *workPath = NULL;

void dot_databases(GNCDB *db);
int dot_clone(const char *command, int g);
#define MAX_KEY_LENGTH 14 // 假设最大键名长度为 12 字符

// 读取文本中的SQL并执行
void read_sql_from_file(const char *filename, GNCDB *db)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    char sql[1024];
    while (fgets(sql, sizeof(sql), file) != NULL)
    {
        // 去掉行末的换行符
        sql[strcspn(sql, "\n")] = 0;

        // 跳过空行或注释行
        if (strlen(sql) == 0 || sql[0] == '#')
        {
            continue;
        }

        // 执行 SQL 命令
        int rc = GNCDB_exec(db, sql, callback, NULL, NULL);
        if (rc == GNCDB_SUCCESS)
        {
            printf("SQL executed successfully: %s\n", sql);
        }
        else
        {
            printf("Error executing SQL: %s\n", sql);
        }
    }

    fclose(file);
}

#define CONFIG_FILE "gncdb_config.ini"
// 修改配置文件中的配置项
// void update_config_value(const char *key, const char *new_value)
// {
//     FILE *file = fopen(CONFIG_FILE, "r+");
//     if (file == NULL)
//     {
//         printf("Error opening file %s\n", CONFIG_FILE);
//         return;
//     }

//     // 创建一个临时文件来存储更新后的内容
//     FILE *temp_file = tmpfile();
//     if (temp_file == NULL)
//     {
//         printf("Error creating temporary file.\n");
//         fclose(file);
//         return;
//     }

//     char line[256];
//     int found = 0;

//     // 逐行读取文件并更新内容
//     while (fgets(line, sizeof(line), file) != NULL)
//     {
//         char *delimiter = strchr(line, '=');
//         if (delimiter)
//         {
//             *delimiter = '\0'; // 分隔符处截断，得到 key
//             if (strcmp(line, key) == 0)
//             {
//                 // 找到匹配的 key，修改该行
//                 fprintf(temp_file, "%s=%s\n", key, new_value);
//                 found = 1;
//             }
//             else
//             {
//                 // 未找到匹配的 key，写原始内容
//                 fprintf(temp_file, "%s=%s", line, delimiter + 1);
//             }
//         }
//         else
//         {
//             // 如果这一行没有找到 '=', 直接写入
//             fprintf(temp_file, "%s", line);
//         }
//     }

//     if (!found)
//     {
//         printf("Key '%s' not found in the config file.\n", key);
//     }
//     else
//     {
//         // printf("Updated %s to %s in gncdb_config.ini\n", key, new_value);
//     }

//     // 清空原文件并将更新后的内容写回
//     freopen(CONFIG_FILE, "w", file);
//     fseek(temp_file, 0, SEEK_SET);

//     // 将临时文件内容写回原文件
//     while (fgets(line, sizeof(line), temp_file) != NULL)
//     {
//         fprintf(file, "%s", line);
//     }

//     fclose(file);
//     fclose(temp_file);
// }
int close_tag = 0;
int open_database(char *fileName, GNCDB **db)
{
    // 打印尝试打开的数据库文件名
    printf("Attempting to open database file: '%s'\n", fileName);

    // 关闭当前数据库（如果有的话）
    if (*db != NULL && close_tag != 0)
    {
        close_tag = GNCDB_close(db); // 假设 GNCDB_close 已经正确处理指针
        if (close_tag != 0)
        {
            printf("Error closing previous database, return code: %d\n", close_tag);
        }
    }

    // 检测并创建 "log" 文件夹
    struct stat statbuf;
    if (stat("log", &statbuf) != 0)
    { // 检查 "log" 文件夹是否存在
        if (mkdir("log", 0755) != 0)
        { // 如果不存在，则创建文件夹
            perror("mkdir failed");
            return -1; // 返回错误代码
        }
    }

    // 打开新的数据库文件
    int rc = GNCDB_open(db, fileName);
    if (rc == 0)
    {
        printf("Database opened successfully.\n");

        // 复制文件名，避免直接指向外部字符串
        (*db)->fileName = strdup(fileName); // 使用 strdup 复制文件名

        // 获取当前路径并保存
        getcwd(opDir, sizeof(opDir));

        close_tag = 1;
    }
    else
    {
        printf("Error opening database, return code: %d\n", rc);
    }

    return rc;
}

// dot_command 处理函数，根据命令输出帮助信息或处理命令
void dot_command(char *command, GNCDB *db)
{
    if (command == NULL)
    {
        printf("请输入命令\n");
    }
    if (strncmp(command, ".help", 5) == 0)
    {
        // print_help_from_file("help.txt");
        print_help(command);
    }
    else if (strncmp(command, ".tables", 7) == 0)
    {
        // 处理 .tables 命令，执行 select * from master;
        if (db == NULL)
        {
            printf("Error: No database is currently open.\n");
        }
        GNCDB_exec(db, "select tableName from master", callback, NULL, NULL);
    }
    else if (strncmp(command, ".schema", 7) == 0)
    {
        // 处理 .tables 命令，执行 select sql from schema;
        if (db == NULL)
        {
            printf("Error: No database is currently open.\n");
        }
        GNCDB_exec(db, "select sql from master", callback, NULL, NULL);
    }
    else if (strncmp(command, ".cd", 3) == 0)
    {
        // 处理 .cd 命令的逻辑
        workPath = (char *)(command + 4);

        // 改变工作目录
        if (chdir(workPath) != 0)
        {
            perror("chdir failed"); // 如果失败，打印错误
            // exit(1);
        }

        // 检查当前工作目录
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("Current working directory: %s\n", cwd); // 打印当前工作目录
        }
        else
        {
            perror("getcwd failed");
        }
    }
    else if (strncmp(command, ".show", 5) == 0)
    {
        // 处理 .show 命令的逻辑
        show_config(config_absolute_path);
    }
    else if (strncmp(command, ".crnl", 5) == 0)
    {
        // 处理 .crnl 命令的逻辑
        if (command[6] == 'o' && command[7] == 'n')
        {
            update_config_value("crnl", "on");
        }
        else if (command[6] == 'o' && command[7] == 'f' && command[8] == 'f')
        {
            update_config_value("crnl", "off");
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".save", 5) == 0)
    {
        // 处理 .save 命令的逻辑
        int result = dot_clone(command, 2);
    }
    else if (strncmp(command, ".echo", 5) == 0)
    {
        // 处理 .echo 命令的逻辑
        if (command[6] == 'o' && command[7] == 'n')
        {
            update_config_value("echo", "on");
        }
        else if (command[6] == 'o' && command[7] == 'f' && command[8] == 'f')
        {
            update_config_value("echo", "off");
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".width", 6) == 0)
    {
        // 处理 .width 命令的逻辑
        char *commandCopy = strdup(command + 7);
        char *width = strtok(commandCopy, " ");
        if (width)
        {
            update_config_value("width", width);
        }
        free(commandCopy);
    }
    else if (strncmp(command, ".timer", 6) == 0)
    {
        // 处理 .timer 命令的逻辑
        if (command[7] == 'o' && command[8] == 'n')
        {
            update_config_value("timer", "on");
        }
        else if (command[7] == 'o' && command[8] == 'f' && command[9] == 'f')
        {
            update_config_value("timer", "off");
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".trace", 6) == 0)
    {
        // 处理 .trace 命令的逻辑
        if (command[7] == 'o' && command[8] == 'n')
        {
            ifTrace = 1;
        }
        else if (command[7] == 'o' && command[8] == 'f' && command[9] == 'f')
        {
            ifTrace = 0;
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".separator", 10) == 0)
    {
        // 处理 .separator 命令的逻辑
        char *commandCopy = strdup(command + 11); // 跳过 ".separator "
        char *colseparator = strtok(commandCopy, " ");
        char *rowseparator = strtok(NULL, " ");

        if (colseparator)
        {
            update_config_value("colseparator", colseparator);
        }
        if (rowseparator)
        {
            update_config_value("rowseparator", rowseparator);
        }

        free(commandCopy);
    }
    else if (strncmp(command, ".databases", 10) == 0)
    {
        // 调用 .databases 命令的处理函数
        dot_databases(db);
    }
    else if (strncmp(command, ".once", 5) == 0)
    {
        // 处理 .once 命令的逻辑
        onceOption = command + 6;
    }
    else if (strncmp(command, ".excel", 6) == 0)
    {
        // 处理 .excel 命令的逻辑
        // set_output_excel(1);
        update_config_value("output", "excel");
    }
    else if (strncmp(command, ".output", 7) == 0)
    {
        // 处理 .output 命令的逻辑
        update_config_value("output", command + 8);
        if (strlen(command) == 7)
        {
            update_config_value("output", "stdout");
        }
    }
    else if (strncmp(command, ".changes", 8) == 0)
    {
        // 处理 .changes 命令的逻辑
        if (command[9] == 'o' && command[10] == 'n')
        {
            ifChange = 1;
        }
        else if (command[9] == 'o' && command[10] == 'f' && command[11] == 'f')
        {
            ifChange = 0;
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".quit", 5) == 0)
    {
        //  关闭数据库
        int closetag = 1;
        closetag = GNCDB_close(&db);
        if (closetag == 0)
        {
            printf("Database closed successfully.\n");
        }
        else
        {
            printf("Error closing database, return code: %d\n", closetag);
        }
        exit(0);
        // 退出程序的逻辑
    }
    else if (strncmp(command, ".read ", 6) == 0)
    {
        // 处理 .read FILE 命令
        const char *filename = command + 6; // 获取文件名
        read_sql_from_file(filename, db);   // 从文件中读取 SQL 并执行
    }
    else if (strncmp(command, ".timer ", 7) == 0)
    {
        // 处理 .timer 命令
        if (command[7] == 'o' && command[8] == 'n')
        {
            ifTimer = 1;
            printf("timer is on\n");
        }
        else if (command[7] == 'o' && command[8] == 'f' && command[9] == 'f')
        {
            ifTimer = 0;
            printf("timer is off\n");
        }
    }
    else if (strncmp(command, ".clone", 6) == 0)
    { // 处理 .clone 命令
        int result = dot_clone(command, 1);
        if (result == 0)
        {
            // printf("clone successful.\n");
        }
        else
        {
            // printf("clone failed.\n");
        }
    }
    else if (strncmp(command, ".version", 8) == 0)
    {
        // 处理 .version 命令的逻辑
        show_first_line("gncdb_config.ini");
    }
    else if (strncmp(command, ".headers", 8) == 0)
    {
        // 处理 .header 命令的逻辑
        if (command[9] == 'o' && command[10] == 'n')
        {
            update_config_value("headers", "on");
        }
        else if (command[9] == 'o' && command[10] == 'f' && command[11] == 'f')
        {
            update_config_value("headers", "off");
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    } // 修改headers的配置
    else if (strncmp(command, ".echo", 5) == 0)
    { // 处理 .echo 命令的逻辑
        if (command[6] == 'o' && command[7] == 'n')
        {
            update_config_value("echo", "on");
        }
        else if (command[6] == 'o' && command[7] == 'f' && command[8] == 'f')
        {
            update_config_value("echo", "off");
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".output", 7) == 0)
    { // 处理 .output 命令的逻辑
        update_config_value("output", command + 8);
        if (strlen(command) == 7)
        {
            update_config_value("output", "stdout");
        }
    }
    else if (strncmp(command, ".changes", 8) == 0)
    { // 处理 .changes 命令的逻辑
        if (command[9] == 'o' && command[10] == 'n')
        {
            ifChange = 1;
        }
        else if (command[9] == 'o' && command[10] == 'f' && command[11] == 'f')
        {
            ifChange = 0;
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".indexes", 8) == 0)
    {
        // 处理 .indexes 命令的逻辑
        handle_indexes_command(command, db);
    }
    else if (strncmp(command, ".quit", 5) == 0)
    {
        // printf("退出命令处理\n");
        //  关闭数据库
        int closetag = 1;
        closetag = GNCDB_close(&db);
        if (closetag == 0)
        {
            printf("Database closed successfully.\n");
        }
        else
        {
            printf("Error closing database, return code: %d\n", closetag);
        }
        exit(0);
        // 退出程序的逻辑
    }
    else if (strncmp(command, ".read ", 6) == 0)
    {
        // 处理 .read FILE 命令
        const char *filename = command + 6; // 获取文件名
        read_sql_from_file(filename, db);   // 从文件中读取 SQL 并执行
    }
    else if (strncmp(command, ".timer ", 7) == 0)
    {
        // 处理 .timer 命令
        if (command[7] == 'o' && command[8] == 'n')
        {
            ifTimer = 1;
            printf("timer is on\n");
        }
        else if (command[7] == 'o' && command[8] == 'f' && command[9] == 'f')
        {
            ifTimer = 0;
            printf("timer is off\n");
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else if (strncmp(command, ".dump", 5) == 0)
    {
        handle_dump_command(command, db);
    }
    else if (strncmp(command, ".trace ", 7) == 0)
    {
        if (command[7] == 'o' && command[8] == 'n')
        {
            ifTrace = 1;
        }
        else if (command[7] == 'o' && command[8] == 'f' && command[9] == 'f')
        {
            ifTrace = 0;
        }
        else
        {
            printf("Error: Invalid command\n");
        }
    }
    else
    {
        printf("未识别的命令: %s\n", command);
    }
}

// 获取数据库情况
void dot_databases(GNCDB *db)
{
    // 检查当前数据库是否有效
    if (db != NULL && db->fileName[0] != '\0')
    {
        // 获取数据库文件路径
        printf("main: %s/%s ", opDir, db->fileName);
        char dbPath[2048];
        snprintf(dbPath, sizeof(dbPath), "%s/%s", opDir, db->fileName);
        // 检查文件的读写权限
        if (access(dbPath, R_OK) == 0 && access(dbPath, W_OK) == 0)
        {
            printf("r/w\n");
        }
        else if (access(dbPath, R_OK) == 0)
        {
            printf("r\n");
        }
        else if (access(dbPath, W_OK) == 0)
        {
            printf("w\n");
        }
        else
        {
            printf("no access\n");
        }
    }
    else
    {
        printf("No database opened.\n");
    }
}

// 备份数据库文件的函数
int clone_database(const char *sourceFileName, const char *targetFileName)
{
    if (sourceFileName == NULL || targetFileName == NULL)
    {
        printf("Error: Invalid file names for clone.\n");
        return -1;
    }

    // 打开源数据库文件
    FILE *sourceFile = fopen(sourceFileName, "rb");
    if (sourceFile == NULL)
    {
        perror("Error opening source database file");
        return -1;
    }

    // 打开备份文件
    FILE *cloneFile = fopen(targetFileName, "wb");
    if (cloneFile == NULL)
    {
        perror("Error opening target file");
        fclose(sourceFile);
        return -1;
    }

    // 进行文件复制
    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), sourceFile)) > 0)
    {
        fwrite(buffer, 1, bytesRead, cloneFile);
    }

    // 关闭文件
    fclose(sourceFile);
    fclose(cloneFile);

    // printf("Database clone created successfully: %s -> %s\n", sourceFileName, targetFileName);
    return 0;
}
// 解析并处理 .clone 命令
int dot_clone(const char *command, int g)
{
    char *commandCopy = strdup(command);
    char *token = strtok(commandCopy, " "); // 获取第一个参数

    // 忽略 .clone 前缀
    token = strtok(NULL, " ");

    // 如果没有指定文件名，输出错误提示
    if (token == NULL && g == 1)
    {
        printf(".clone missing FILENAME argument on .clone\n");
        free(commandCopy);
        return -1;
    }
    if (token == NULL && g == 2)
    {
        printf(".save missing FILENAME argument on .clone\n");
        free(commandCopy);
        return -1;
    }

    // 获取源文件名和目标文件名
    char *sourceFileName = db->fileName; // 默认当前数据库文件为源文件
    char *targetFileName = token;        // 第二个文件名是目标文件

    // 如果提供了第二个文件名（例如 .clone a b），则将第一个文件备份为第二个文件
    token = strtok(NULL, " ");
    if (token != NULL)
    {
        sourceFileName = targetFileName; // 第一个参数作为源文件
        targetFileName = token;          // 第二个参数作为目标文件
    }

    // 执行备份
    int result = clone_database(sourceFileName, targetFileName);

    if (result == 0)
    {
        switch (g)
        {
        case 1:
            printf("Database clone created successfully: %s -> %s\n", sourceFileName, targetFileName);
            break;
        case 2:
            printf("Database save created successfully: %s -> %s\n", sourceFileName, targetFileName);
            break;
        }
    }
    free(commandCopy); // 释放复制的命令字符串
    return result;
}

// 处理.dump命令
void handle_dump_command(const char *command, GNCDB *db) {
    char *commandCopy = strdup(command);
    char *token = strtok(commandCopy, " ");
    
    // 跳过".dump"命令
    token = strtok(NULL, " ");
    
    if (!token) {
        printf("Usage: .dump [table_name]\n");
        free(commandCopy);
        return;
    }

    // 输出PRAGMA和BEGIN TRANSACTION
    printf("BEGIN TRANSACTION;\n");

    // 保存当前的printColumnNames值
    int tempHeaders = printColumnNames;
    printColumnNames = 0;

    // 构建查询语句获取CREATE TABLE语句
    char query[1024];
    snprintf(query, sizeof(query), "SELECT sql FROM master WHERE tableName=\"%s\";", token);

    // 执行查询获取表的创建语句
    char *errmsg = NULL;
    int rc = GNCDB_exec(db, query, callback_echo_off, NULL, NULL);
    if (rc != 0) {
        printf("Error: Failed to execute query. Return code: %d\n", rc);
        if (errmsg) {
            printf("Error message: %s\n", errmsg);
            free(errmsg);
        }
        free(commandCopy);
        printColumnNames = tempHeaders;
        return;
    }

    // 构建查询数据的SQL
    snprintf(query, sizeof(query), "SELECT * FROM %s", token);
    
    // 执行查询获取表数据
    rc = GNCDB_exec(db, query, (CallBack2)callback_dump, (void*)token, &errmsg);
    
    if (rc != 0) {
        printf("Error: Failed to execute query. Return code: %d\n", rc);
        if (errmsg) {
            printf("Error message: %s\n", errmsg);
            free(errmsg);
        }
        free(commandCopy);
        printColumnNames = tempHeaders;
        return;
    }

    // 输出COMMIT
    printf("COMMIT;\n");

    // 恢复原始的printColumnNames值
    printColumnNames = tempHeaders;
    free(commandCopy);
}

void handle_indexes_command(const char *command, GNCDB *db) {
    // 复制命令字符串以便解析
    char *commandCopy = strdup(command);
    if (!commandCopy) {
        printf("Error: Memory allocation failed\n");
        return;
    }

    // 解析命令
    char *token = strtok(commandCopy, " ");
    if (!token) {
        printf("Error: Invalid command format\n");
        free(commandCopy);
        return;
    }

    // 跳过".indexes"命令
    token = strtok(NULL, " ");

    // 保存当前的printColumnNames值
    int tempHeaders = printColumnNames;
    printColumnNames = 0;

    char *errmsg = NULL;
    int rc;

    if (token == NULL) {
        // 如果没有指定表名，显示所有索引
        rc = GNCDB_exec(db, "SELECT id, tableName FROM master;", callback_echo_off, NULL, &errmsg);
    } else {
        // 显示指定表的索引
        char query[1024];
        snprintf(query, sizeof(query), "SELECT id FROM master WHERE tableName=\"%s\";", token);
        rc = GNCDB_exec(db, query, callback_echo_off, NULL, &errmsg);
    }

    if (rc != 0) {
        printf("Error: Failed to execute query. Return code: %d\n", rc);
        if (errmsg) {
            printf("Error message: %s\n", errmsg);
            free(errmsg);
        }
    }

    // 恢复原始的printColumnNames值
    printColumnNames = tempHeaders;
    free(commandCopy);
}