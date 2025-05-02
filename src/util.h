#ifndef UTILS_H
#define UTILS_H
#include <db.h>
// 声明处理以 '.' 开头的命令的函数
void dot_command(const char *command,GNCDB*);
int open_database(const char *fileName, GNCDB **db);
void update_config_value(const char *key, const char *new_value);
#endif // UTILS_H
