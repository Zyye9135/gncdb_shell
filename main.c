#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "db.h"

// #include <stdio.h>
// #include <string.h>
// #include "db.h"

// int callback(void *data, int argc, char **azColName, char **argv) {
//     static int headerPrinted = 0;

//     if (!headerPrinted) {
//         for (int i = 0; i < argc; i++) {
//             if (strcmp(azColName[i], "createTime") == 0 || strcmp(azColName[i], "updateTime") == 0) {
//                 continue;
//             }
//             printf("%-15s", azColName[i]);
//         }
//         printf("\n");
//         for (int i = 0; i < argc; i++) {
//             if (strcmp(azColName[i], "createTime") == 0 || strcmp(azColName[i], "updateTime") == 0) {
//                 continue;
//             }
//             printf("----------------");
//         }
//         printf("\n");
//         headerPrinted = 1;
//     }

//     for (int i = 0; i < argc; i++) {
//         if (strcmp(azColName[i], "createTime") == 0 || strcmp(azColName[i], "updateTime") == 0) {
//             continue;
//         }
//         printf("%-15s", argv[i] ? argv[i] : "NULL");
//     }
//     printf("\n");
//     return 0;
// }

int main() {
    int rc;
    char* filename = "GNCDB.dat";
    GNCDB* db = NULL;
    char* input = NULL;
    char sql[4096] = {0};

    // 打开数据库
    rc = db_open(filename, &db);
    if (rc == 0) {
        printf("Database opened successfully.\n");
    } else {
        printf("Error opening database, return code: %d\n", rc);
        return 1;
    }

    // 命令行交互
    while (1) {
        input = readline("Enter SQL command (or 'exit' to quit): ");
        if (!input) {
            break; // 读取失败或 EOF
        }

        // 如果输入不为空，添加到历史记录
        if (strlen(input) > 0) {
            add_history(input);
        }

        // 检查退出命令
        if (strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // 拼接输入到 SQL 缓冲区
        if (strlen(sql) > 0) {
            strcat(sql, " "); // 在每行之间添加空格
        }
        strcat(sql, input);

        // 检查SQL是否结束（检测分号）
        if (strchr(sql, ';') != NULL) {
            // 执行 SQL 命令
            rc = db_exec(db, sql, callback, NULL, NULL);
            if (rc == GNCDB_SUCCESS) {
                printf("SQL executed successfully.\n");
            } else {
                printf("Error executing SQL, return code: %d\n", rc);
            }

            // 清空 SQL 缓冲区
            memset(sql, 0, sizeof(sql));
        }

        free(input);
    }

    // 关闭数据库
    rc = db_close(&db);
    if (rc == 0) {
        printf("Database closed successfully.\n");
    } else {
        printf("Error closing database, return code: %d\n", rc);
    }

    return 0;
}