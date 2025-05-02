#ifndef VALUE_H
#define VALUE_H
#include <stdbool.h>
typedef struct Expression Expression;
typedef struct Tuple Tuple;

typedef enum AttrType{
  UNDEFINED,
  INTS,           ///< 整数类型(4字节)
  DOUBLES,         ///< 浮点数类型(8字节)
  CHARS,          ///< 字符串类型
  BLOB,           ///< 未实现
  DATES,          ///< 日期类型
  DATETIMES,      ///< 日期时间类型()
  TEXTS,          ///< 文本类型
  NULLS,          ///< 空值(当前仅用于exists_op的左值)
  BOOLEANS,       ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
} AttrType;

const char *attrTypeToString(AttrType type);
AttrType stringTOattrType(const char *s);

typedef struct DateTime {
  int date;
  int time;
} DateTime;
typedef struct TextInfo{
  int overFlowPageId;
  int tupleIndex;
  Tuple* tuple;
} TextInfo;

typedef struct Value {
  AttrType attrType;
  int length;
  union {
    int intValue;
    double doubleValue;
    bool boolValue;
    // double doubleValue;
    DateTime datetimeValue;
    TextInfo textValue;
  } numValue;
  char *strValue;
} Value;

Value* createValue(AttrType* type, void* val);
void valueSet(Value *dest, void *data);
void valueSetType(Value *value, AttrType type);
void valueSetData(Value *value, char *data, int length);
void valueSetInt(Value *value, int val);
void valueSetDate(Value *value, int val);
void valueSetDouble(Value *value, double val);
void valueSetBoolean(Value *value, int val);
void valueSetString(Value *value, char *s);
void valueSetDatetime(Value *value, DateTime val);
void valueSetNull(Value *value);
const char *valueToString(const Value *value);
// int valueCompare(const Value *value1, const Value *value2);
int valueGetInt(const Value *value);
float valueGetFloat(const Value *value);
char *valueGetString(const Value *value);
int valueGetBoolean(const Value *value);
int valueTypeCast(Value *value, AttrType type);

void print_AttrType(AttrType type);

/*value的比较函数*/
int valueCompareInt(Value* left, Value* right);
int valueCompareFloat(Value* left, Value* right);
int valueCompareChar(Value* left, Value* right);
int valueCompare(Value* left, Value* right);

Value* valueAdd(Value* left, Value* right);
Value* valueDiv(Value* value, int cnt);

/* date类型 */
bool checkDate(int year, int month, int day);
int stringToDate(char* str,int* date);
char* dateToString(int date);


/* datetime类型 */
int stringToDatetime(char* str, DateTime* datetime);
char* datetimeToString(const DateTime* datetime);
int datetimeCompare(DateTime* left, DateTime* right);
int datetimeStringCompare(char* left, char* right);


/* TEXT类型 */
void valueSetText(Value *value, char* str);
TextInfo valueGetText(Value *value);


/* 检查插入的exprvalue是否合法 */
bool insertExprToValue(Expression*insert_expr ,Value *value);


void valuePointerDestroy(void* data);
/* value创建函数 */
Value* valueCreate(AttrType type, void* val);

/* 创建空的value */
Value* valueCreateEmpty();

/* value销毁函数 */
void valueDestroy(Value* value);

/* valueMove */
Value* valueMove(Value** value);

/* value拷贝函数 */
Value* valueCopy(Value* value);
void copyValueTo(Value* src,Value* dest);

#endif /* VALUE_H */
