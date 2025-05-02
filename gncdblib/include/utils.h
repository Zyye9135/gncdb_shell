#ifndef _GNCDB_UTILS_H_
#define _GNCDB_UTILS_H_

#include <stdbool.h>

/* 分割字符串 */
int split_string(char* str, char** tokens);
/* 判断字符串中是否有符号"." */
int hasOneDots(char* str);

/* 找出字符串在原字符串中的起始位置 */
int find_str(char* str, char* sub_str);
/* 复制子字符串，要求从指定位置开始，并具有指定的长度。如果没有指定长度_Count或_Count + _Off超出了源字符串的长度，则子字符串将延续到源字符串的结尾 */
char* sub_str(char* str, int pos, int len);
/* 只负责截取字符串，不负责分配内存 */
void swap_str(char* str1, char* str2);
/* 判断两个int值是否相等 */
bool isEqualOfInt(void* key1, void* key2);
/* 判断两个字符串是否相等 */
bool isEqualOfString(void* key1, void* key2);

#endif
