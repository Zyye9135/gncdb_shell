#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  // access() 用于检查文件读写权限
#include "db.h"

// 定义一个全局配置变量，控制是否打印列名
int printColumnNames = 1; // 默认为1，表示打印列名
int headerPrinted = 0;
int ifExcel = 0;  // 控制是否以电子表格格式输出（CSV）
FILE *outputFile = NULL; // 文件指针，初始化为NULL
char * colSeparator = "\t";  // 列分隔符，默认为制表符
char * rowSeparator = "\n";  // 行分隔符，默认为换行符


// 提供一个接口函数用于修改配置
void set_print_column_names(int print) {
    printColumnNames = print;
}

// 控制输出是否为电子表格格式（CSV）
void set_output_excel(int enable) {
    ifExcel = enable;  // 启用或禁用电子表格格式输出
}

// 打开输出文件
int open_output_file(const char *fileName) {
    // 检查文件是否存在，如果不存在则创建文件
    outputFile = fopen(fileName, "w"); // 以写入模式打开文件，如果文件不存在会创建
    if (outputFile == NULL) {
        perror("Error opening file");
        return -1;
    }
    printf("File opened/created successfully: %s\n", fileName);
    return 0;
}

// 写入输出文件
void write_to_file(const char *content) {
    if (outputFile != NULL) {
        fprintf(outputFile, "%s", content);
    }
    else {
        printf("Error: No output file opened.\n");
    }
}

// 关闭输出文件
void close_output_file() {
    if (outputFile != NULL) {
        fclose(outputFile);
        printf("File closed successfully.\n");
        outputFile = NULL;
    }
    else {
        printf("Error: No output file to close.\n");
    }
}

// 标准输出的打印
int callback(void *data, int argc, char **azColName, char **argv) {
    // 如果需要以电子表格格式输出
    if (ifExcel) {
        if (headerPrinted == 0) {
            // 打印列名
            for (int i = 0; i < argc; i++) {
                printf("\"%s\"", azColName[i]);
                if (i < argc - 1) {
                    printf(",");  // 用逗号分隔列名
                }
            }
            printf("\n");  // 列名后换行
            headerPrinted = 1;

            // 如果文件输出已启用，将列名写入文件
            if (outputFile != NULL) {
                for (int i = 0; i < argc; i++) {
                    fprintf(outputFile, "\"%s\"", azColName[i]);
                    if (i < argc - 1) {
                        fprintf(outputFile, ",");
                    }
                }
                fprintf(outputFile, "\n");
            }
        }

        // 打印数据
        for (int i = 0; i < argc; i++) {
            printf("\"%s\"", argv[i] ? argv[i] : "NULL");
            if (i < argc - 1) {
                printf(",");  // 用逗号分隔列数据
            }
        }
        printf("\n");

        // 如果文件输出已启用，将数据写入文件
        if (outputFile != NULL) {
            for (int i = 0; i < argc; i++) {
                fprintf(outputFile, "\"%s\"", argv[i] ? argv[i] : "NULL");
                if (i < argc - 1) {
                    fprintf(outputFile, ",");
                }
            }
            fprintf(outputFile, "\n");
        }
    }
    else {
        // 普通输出（不为电子表格格式）
        if (printColumnNames && !headerPrinted) {
            for (int i = 0; i < argc; i++) {
                if (strcmp(azColName[i], "createTime") == 0 ||
                    strcmp(azColName[i], "updateTime") == 0 ||
                    strcmp(azColName[i], "rowId") == 0) {
                    continue;
                }
                printf("%s\t", azColName[i]);
            }
            printf("\n");

            for (int i = 0; i < argc; i++) {
                if (strcmp(azColName[i], "createTime") == 0 ||
                    strcmp(azColName[i], "updateTime") == 0 ||
                    strcmp(azColName[i], "rowId") == 0) {
                    continue;
                }
                printf("------\t");
            }
            printf("\n");

            headerPrinted = 1;
        }

        for (int i = 0; i < argc; i++) {
            if (strcmp(azColName[i], "createTime") == 0 ||
                strcmp(azColName[i], "updateTime") == 0 ||
                strcmp(azColName[i], "rowId") == 0) {
                continue;
            }
            printf("%s\t", argv[i] ? argv[i] : "NULL");
        }
        printf("\n");

        // 如果文件输出已启用，将数据写入文件
        if (outputFile != NULL) {
            for (int i = 0; i < argc; i++) {
                fprintf(outputFile, "%s\t", argv[i] ? argv[i] : "NULL");
            }
            fprintf(outputFile, "\n");
        }
    }
    return 0;
}

// callback_echo_off 函数：打印列名和数据行（不回显数据）
int callback_echo_off(void *data, int argc, char **azColName, char **argv) {
    for(int i = 0; i < argc; i++) {
        if(strcmp(azColName[i], "UPDATE COUNT") == 0 ||
           strcmp(azColName[i], "DELETE COUNT") == 0 ||
           strcmp(azColName[i], "DELETE COUNT") == 0) {
           return 0;
        }
    }
    if (ifExcel) {
        // 以电子表格格式输出（CSV）
        if (headerPrinted == 0) {
            // 打印列名
            for (int i = 0; i < argc; i++) {
                printf("\"%s\"", azColName[i]);
                if (i < argc - 1) {
                    printf(",");  // 用逗号分隔列名
                }
            }
            printf("\n");  // 列名后换行
            headerPrinted = 1;

            // 如果文件输出已启用，将列名写入文件
            if (outputFile != NULL) {
                for (int i = 0; i < argc; i++) {
                    fprintf(outputFile, "\"%s\"", azColName[i]);
                    if (i < argc - 1) {
                        fprintf(outputFile, ",");
                    }
                }
                fprintf(outputFile, "\n");
            }
        }

        // 打印数据
        for (int i = 0; i < argc; i++) {
            printf("\"%s\"", argv[i] ? argv[i] : "NULL");
            if (i < argc - 1) {
                printf(",");  // 用逗号分隔列数据
            }
        }
        printf("\n");

        // 如果文件输出已启用，将数据写入文件
        if (outputFile != NULL) {
            for (int i = 0; i < argc; i++) {
                fprintf(outputFile, "\"%s\"", argv[i] ? argv[i] : "NULL");
                if (i < argc - 1) {
                    fprintf(outputFile, ",");
                }
            }
            fprintf(outputFile, "\n");
        }
    }
    else {
        // 普通输出（不为电子表格格式）
        if (printColumnNames && !headerPrinted) {
            for (int i = 0; i < argc; i++) {
                
                if (strcmp(azColName[i], "createTime") == 0 ||
                    strcmp(azColName[i], "updateTime") == 0 ||
                    strcmp(azColName[i], "rowId") == 0) {
                    continue;
                }
                printf("%s\t", azColName[i]);
            }
            printf("\n");

            for (int i = 0; i < argc; i++) {
                if (strcmp(azColName[i], "createTime") == 0 ||
                    strcmp(azColName[i], "updateTime") == 0 ||
                    strcmp(azColName[i], "rowId") == 0) {
                    continue;
                }
                printf("------\t");
            }
            printf("\n");

            headerPrinted = 1;
        }

        for (int i = 0; i < argc; i++) {
            if (strcmp(azColName[i], "createTime") == 0 ||
                strcmp(azColName[i], "updateTime") == 0 ||
                strcmp(azColName[i], "rowId") == 0) {
                continue;
            }
            printf("%s\t", argv[i] ? argv[i] : "NULL");
        }
        printf("\n");

        // 如果文件输出已启用，将数据写入文件
        if (outputFile != NULL) {
            for (int i = 0; i < argc; i++) {
                fprintf(outputFile, "%s\t", argv[i] ? argv[i] : "NULL");
            }
            fprintf(outputFile, "\n");
        }
    }
    return 0;
}
