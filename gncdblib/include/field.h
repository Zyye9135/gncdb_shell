/**
 * @file field.h
 * @author vera
 * @brief  定义元组的字段类型：整数型、浮点型、字符串型、Blob型,以及字段不同类型相关操作
 * @version 0.1
 * @date 2023-01-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _GNCDB_FIELD_H_
#define _GNCDB_FIELD_H_

#include <stdbool.h>
#include "utils.h"
#include "gncdbConstant.h"
#include "varArrayList.h"
#include "typeDefine.h"

typedef struct Field {
	FieldType fieldType;
	int fieldSize;
}Field;

typedef struct IntField {
	Field baseInfo;
	int value;
}IntField;

typedef struct DateField {
	Field baseInfo;
	int value;
}DateField;

typedef struct DateTimeField {
	Field baseInfo;
	int dateValue;
	int timeValue;
}DateTimeField;

typedef struct RealField {
	Field baseInfo;
	double value;
}RealField;

typedef struct VarCharField {
	Field baseInfo;
	char* value;
}VarCharField;

typedef struct BlobField {
	Field baseInfo;
	int overflowPageId;
	int size;
}BlobField;

typedef struct TextField {
	Field baseInfo;
	int overflowPageId;
	int size;
}TextField;



/* 七种字段类型的构造 */
struct IntField* intFieldConstruct(int value);
struct DateField* dateFieldConstruct(int value);

struct RealField* realFieldConstruct(double value);
struct VarCharField* varCharFieldConstruct(char* value);
struct BlobField* blobFieldConstruct(int overflowPageId,int size);
struct DateTimeField* datetimeFieldConstruct(int dateValue,int timeValue);
struct 	TextField* textFieldConstruct(int overflowPageId,int size);
// struct Field* nullFieldConstruct(FieldType fieldType);


/* 七种字段类型的销毁操作 */
void intFieldDestroy(struct IntField** intField);
void dateFieldDestroy(struct DateField** dateField);
void realFieldDestroy(struct RealField** realField);
void varCharFieldDestroy(struct VarCharField** varCharField);
void blobFieldDestroy(struct BlobField** blobField);
void datetimeFieldDestroy(struct DateTimeField** datetimeField);
void textFieldDestroy(struct TextField** textField);
void fieldDestroy(void* data);
void keyValueDestroy(void* data);



/* todo? 下面的两个函数暂时没有使用到 */
/* 字符串转化成对应类型的field */
int stringToField(const char* string, void* result);	
/* 判断两个字段是否满足predicate运算符的关系 */
bool fieldIsMatch(void* fieldFirst, void* fieldSecond, Predicate predicate);	

/* DateTime字段比较函数 */
int DateTimeFieldCompare(void* fieldFirst, void* fieldSecond);

/* 将DateTimeField内容转换成字符串 */
char* DateTimeFieldToString(DateTimeField* dateTimeField);
#endif /* _GNCDB_FIELD_H_ */
