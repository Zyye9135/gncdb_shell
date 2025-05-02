#ifndef VALUE_H
#define VALUE_H
#include <stdbool.h>
// 结构体声明
typedef struct Expression Expression;
typedef struct Tuple      Tuple;

// 枚举类型：属性类型
typedef enum AttrType
{
  UNDEFINED,  ///< 未定义
  INTS,       ///< 整数类型(4字节)
  DOUBLES,    ///< 浮点数类型(8字节)
  CHARS,      ///< 字符串类型
  BLOB,       ///< 未实现
  DATES,      ///< 日期类型
  DATETIMES,  ///< 日期时间类型
  TEXTS,      ///< 文本类型
  NULLS,      ///< 空值(当前仅用于exists_op的左值)
  BOOLEANS,   ///< boolean类型，程序内部使用
} AttrType;

// 结构体：日期时间类型
typedef struct DateTime
{
  int date;  ///< 日期
  int time;  ///< 时间
} DateTime;

// 结构体：文本信息类型
typedef struct TextInfo
{
  int    overFlowPageId;  ///< 溢出页ID
  int    tupleIndex;      ///< 元组索引
  Tuple *tuple;           ///< 元组指针
} TextInfo;

// 结构体：值类型
typedef struct Value
{
  AttrType attrType;  ///< 属性类型
  int      length;    ///< 长度
  union
  {
    int      intValue;       ///< 整数值
    double   doubleValue;    ///< 浮点数值
    bool     boolValue;      ///< 布尔值
    DateTime datetimeValue;  ///< 日期时间值
    TextInfo textValue;      ///< 文本信息值
  } numValue;
  char *strValue;  ///< 字符串值

  // 是否内存由Value管理，目前主要是字符串类型
  bool isMalloc;
} Value;

// 函数声明：类型转换
const char *attrTypeToString(AttrType type);  ///< 将属性类型转换为字符串
AttrType    stringTOattrType(const char *s);  ///< 将字符串转换为属性类型

// 函数声明：Value设置函数
void valueSet(Value *dest, void *data);                   ///< 设置Value的值
void valueSetType(Value *value, AttrType type);           ///< 设置Value的类型
void valueSetData(Value *value, char *data, int length);  ///< 设置Value的数据
void valueSetInt(Value *value, int val);                  ///< 设置Value的整数值
void valueSetDate(Value *value, int val);                 ///< 设置Value的日期值
void valueSetDouble(Value *value, double val);            ///< 设置Value的浮点数值
void valueSetBoolean(Value *value, int val);              ///< 设置Value的布尔值
void valueSetString(Value *value, char *s);               ///< 设置Value的字符串值
void valueSetDatetime(Value *value, DateTime val);        ///< 设置Value的日期时间值
void valueSetNull(Value *value);                          ///< 设置Value为空值
void valueSetBlob(Value *value);                          ///< 设置Value的Blob值(待完善)
void valueSetText(Value *value, char *str);               ///< 设置Value的文本值

// 函数声明：Value获取函数
char *valueToString(const Value *value);    ///< 将Value转换为字符串（未实现）
int      valueGetInt(const Value *value);      ///< 获取Value的整数值
float    valueGetFloat(const Value *value);    ///< 获取Value的浮点数值
char    *valueGetString(const Value *value);   ///< 获取Value的字符串值
int      valueGetBoolean(const Value *value);  ///< 获取Value的布尔值
TextInfo valueGetText(Value *value);           ///< 获取Value的文本信息

// 函数声明：Value类型转换函数
int valueTypeCast(Value *value, AttrType type);  ///< 将Value的类型转换为指定类型

// 函数声明：打印属性类型
void printAttrType(AttrType type);  ///< 打印属性类型

/*Value比较函数*/
int valueCompareInt(Value *left, Value *right);    ///< 比较整数类型Value
int valueCompareFloat(Value *left, Value *right);  ///< 比较浮点类型Value
int valueCompareChar(Value *left, Value *right);   ///< 比较字符类型Value
int valueCompare(Value *left, Value *right);       ///< 比较Value

// 函数声明：Value计算函数
Value *valueAdd(Value *left, Value *right);  ///< Value加法
Value *valueDiv(Value *value, int cnt);      ///< Value除法

/*date类型函数*/
bool  checkDate(int year, int month, int day);  ///< 检查日期是否合法
int   stringToDate(char *str, int *date);       ///< 字符串转换为日期
char *dateToString(int date);                   ///< 日期转换为字符串

/*datetime类型函数*/
int   stringToDatetime(char *str, DateTime *datetime);   ///< 字符串转换为日期时间
char *datetimeToString(const DateTime *datetime);        ///< 日期时间转换为字符串
int   datetimeCompare(DateTime *left, DateTime *right);  ///< 比较日期时间
int   datetimeStringCompare(char *left, char *right);    ///< 比较日期时间字符串

/* 检查插入的exprvalue是否合法 */
bool insertExprToValue(Expression *insert_expr, Value *value);

/* value的销毁函数 */
void valuePointerDestroy(void *data);  ///< 销毁Value指针

/* 创建空的value */
Value *valueCreate();  ///< 创建Value

/* value销毁函数 */
void valueDestroy(Value **value);  ///< 销毁Value

/* valueMove */
Value *valueMove(Value **value);  ///< 移动Value

/* value reset函数 */
void valueReset(Value *value);  ///< 重置Value

/* value拷贝函数 */
Value *valueCopy(Value *value);               ///< 拷贝Value
void   copyValueTo(Value *src, Value *dest);  ///< 拷贝Value到目标Value

/* 提取value类型对应类型的指针(不需要malloc和free) */
void *valueGetPointer(Value *value);  ///< 获取Value的指针

#endif /* VALUE_H */
