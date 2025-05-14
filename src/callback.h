#ifndef CALLBACK_H
#define CALLBACK_H

// 声明 callback 函数
int callback(void *data, int argc, char **azColName, char **argv);
int callback_echo_off(void *data, int argc, char **azColName, char **argv);
int callback_get_column_type(void *data, int argc, char **azColName, char **argv);
int callback_dump(void *data, int argc, char **azColName, char **argv);
void set_output_excel(int enable);
int open_output_file(const char *fileName);
void close_output_file();
void set_print_column_names(int print);
void set_column_width(int width);
void write_to_file(const char *content);
int enable_once_output(const char *fileName);
void disable_once_output();
#endif
