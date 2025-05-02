/*
 * @Descripttion:
 * @version:
 * @Author: Alan
 * @Date: 2022-06-16 16:05:22
 * @LastEditors: Alan
 * @LastEditTime: 2023-01-30 11:27:16
 */
#ifndef _OS_H_
#define _OS_H_

#include <stdbool.h>
#include <stdio.h>
#include "typedefine.h"
#include "gncdbconstant.h"

//#define TIMING true

extern double time_per_read;
extern double time_per_write;

int byteModeConstrcut();
int osOpenFile(char* fileName, FILE** fp);
int osRead(FILE *file, long seek, int size, BYTE **buf);
int osWrite(FILE *filee, BYTE *buf, long  seek, int size);
int getFileLength(long *len, FILE *file);
bool isFileExist(const char *filename);
int createFile(const char *filename, FILE **file);
int expandFileSize(FILE *file, int size);
int readInt(int *num, BYTE *buf, int *len);
int writeInt(int num, BYTE *buf, int *len);
int readShort(short *num, BYTE *buf, int *len);
int writeShort(short num, BYTE* buf, int *len);
int readChar(char *buf0, BYTE* buf, int *len);
int writeChar(char num, BYTE* buf, int *len);
int readDouble(double *raw_num, BYTE *buf, int *len);
int writeDouble(double num, BYTE* buf, int *len);
int readString(char **str, BYTE *buf, int size, int *len);
int writeString(char *str, BYTE *buf, int *len);
int readBlob(BYTE *blob, BYTE *buf, int size, int *len);
int writeBlob(BYTE *blob, BYTE *buf, int size, int *len);
int writeBlob1(BYTE *blob, BYTE *buf, int size);
int readULong(unsigned long long *num, BYTE *buf, int *len);
int writeULong(unsigned long long num, BYTE *buf, int *len);
int copyFile(char* fileRead, int readSeek, char* fileWrite, int writeSeek);
void getFileName(char* in, char* out, bool remainDot);
#endif
