#ifndef STRING_TOOL_H
#define STRING_TOOL_H
#include "value.h"
bool isBlank(const char *s);
void valuetoString(Value* value, char** str);
char* strConcat(const char* str1, const char* str2);
void FillfieldNameValue(Value* value, char* Name, char** filedName, char** fieldValue);

char* strrc(int rc);

char** deepCopy2DArray(char** source, int rows);
void init2DArray(char** array, int num);
void reset2DArray(char** array, int num);
void free2DArray(char*** array, int num);

/* 字符串move */
char* strMove(char** str);
#endif