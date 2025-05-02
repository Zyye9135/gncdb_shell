/*
 * @Descripttion: 代码中的状态码和常量
 * @version:
 * @Author: Alan
 * @Date: 2023-01-30 09:19:38
 * @LastEditors: zengqingli 1901227828@qq.com
 * @LastEditTime: 2024-09-07 17:13:03
 */

#ifndef _GNCDBCONSTANT_H_
#define _GNCDBCONSTANT_H_

//#include "oss_type_def.h"
#include <assert.h>
#include "dbLogger.h"
#if defined _WIN32
// #include <windows.h>
#include <time.h>
#endif
#define EPSILON (1E-6)
#define true 1
#define false 0
#define DEBUG 0
/* 根据具体操作系统运行路径设置 */
/*
windows  ..
linux\天脉  .
*/

#if defined _WIN32
#define LOCAL_PATH ".."
#else
#define LOCAL_PATH "."
#define REOPEN_DATEBASE 0
#define USE_NOCONDITION_JOIN 0
#define LOAD_DATA 0
#define USE_NESTED_LOOP_JOIN
// #define USE_SORT_MERGE_JOIN
// #define USE_HASH_JOIN

// #define PINTF_OPERATOR_TREE
// static char* tpccTimeCost = "tpccTimeCostByhashJoin";
// static FILE *fp;
// #define PRINT_TRXS_COST_TIME
// #define PINTF_OPERATOR_TREE 
#endif
//#define USE_LOG 1
// #define SELF_DEFINE_MEMORY 1

#ifndef ASSERT
#define ASSERT(expression, description, ...)                             \
  do {                                                                   \
    if (!(expression)) {                                                 \
      char dbLogStr[256];                                                \
      snprintf(dbLogStr, sizeof(dbLogStr),                               \
               "Assertion failed: (%s), function %s, file %s, line %d. "\
               "Description: " description " ", #expression,            \
               __FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__);         \
      DBLoggerPrint(LOG_TRACE, dbLogStr, __FILE__, __FUNCTION__, __LINE__); \
      assert(expression);                                                \
    }                                                                    \
  } while (0)
#endif  // ASSERT
// TODO: 不支持在子作用域定义变量，需要在函数作用最外层域定义char dbLogStr[256];
// 改成全局变量？

#define LOG_PRINT(logtype, dbLogStr)                                     \
    (DBLoggerPrint(logtype, dbLogStr, __FILE__, __FUNCTION__, __LINE__), DBLoggerPrint)   
 /* int logtype:日志level, format日志内容格式化*/

#ifdef USE_LOG
  #define LOG(logtype, format, ...)                                       \
  do{                                                                     \
      char dbLogStr[100] = {0};                                            \
      sprintf(dbLogStr, format ,##__VA_ARGS__);                           \
      DBLoggerPrint(logtype, dbLogStr, __builtin_FILE(), __FUNCTION__, __LINE__); \
  }while(0)
#else
  #define LOG(logtype, format, ...)                                       \
  do{                                                                     \
  }while(0) 
#endif

#ifdef SELF_DEFINE_MEMORY
  #define my_malloc_init(buffer, size) s_maes_init(buffer, size)
  #define my_free(p)				s_maes_free(p)
  #define my_malloc(size)			s_maes_malloc(size)
  #define my_realloc(p,size)		s_maes_realloc(p,size)
#else
  #define my_free(p)				free(p)
  #define my_malloc(size)			malloc(size)
  #define my_realloc(p,size)		realloc(p,size)
#endif

#define MAX_TRANSACTIONS		100						/* 最大事务数*/
#define PAGE_SIZE               1024					/* 页大小*/
#define PAGE_HEAD_SIZE          13						/* 页头字节大小*/
#define OVERFLOWPAGE_HEAD_SIZE	5						/* 溢出页头字节大小*/
#define FILE_HEADER_SIZE		PAGE_SIZE					/* 文件头大小*/ 
#define BYTES32					32						/* 32字节*/
#define BYTES64				    64						/* 32字节*/
#define BYTES256				256						/* 256字节*/
#define BYTES_POINTER           sizeof(void*)			/* 指针类型占4字节内存*/
#define MAXTABLE				10000					/* 最多有10000张表*/
#define MAXINDEX				5						/* 一个表最多有5个索引*/
#define MAXCOLNUM				32						/* 一个表最多有32列*/
#define MASTERCOLNUM			11						/* master有11列*/
#define SCHEMACOLNUM			11						/* schema有11列*/
#define MASTERNAME				"master"				/* master表名*/
#define SCHEMANAME				"schema"				/* schema表名*/
#define MAX_PAGE_NUM			(2*1024)
#define OVERVIEW_LEN			5						/* 数据库概述*/
#define VERSION_LEN				2						/* 版本号长度*/
#define MASTER_ROOT_PID			2	
#define SCHEMA_ROOT_PID			3
#define MASTERTWOCOLUMN			1
#define MASTERFORECOLUMN		4
#define MASTERFIVECOLUMN		5
#define MAIN_TID				(-1)
#define TABLENAME_FIELD_MAXLEN			20				/* 表名和属性的最大长度限制 */
#define FILENAME_FIELD_MAXLEN			20				  /* 数据名最大长度限制 */
#define LOGFILE_MAXSIZE         10485760000				/* 日志文件最大暂定为10MB */
#define MAX_LOGGER              300000
#define LOGGER_MIN_SIZE         21
#define COND_COUNT              200


#define INT_SIZE sizeof(int)
#define DOUBLE_SIZE sizeof(double)
#define TYPE_SIZE 1


#define COND_COUNT              200

/* 日志宏模块 */
#define LOG_TRACE 1001
#define LOG_DEBUG 1002
#define LOG_INFO 1003
#define LOG_WARNING 1004
#define LOG_ERROR 1005

#define EPSILON (1E-6)
#define GNCDB_SUCCESS			0						/* 成功 */
#define GNCDB_MEM				-1						/* malloc失败 */
#define GNCDB_FILEISNULL		-2						/* 文件为空 */
#define GNCDB_PARAMNULL			-3						/* 输入参数为空 */
#define GNCDB_SPACE_LACK		-4						/* 空间不足 */
#define GNCDB_NOT_FOUND			-5						/* 未找到 */ 
#define GNCDB_TABLE_NOT_FOUND	-6						/* 表未找到 */
#define GNCDB_NO_PAGE			-7						/* 没有这个页 */
#define GNCDB_FLUSH_FAILED		-8						/* 刷新失败 */
#define GNCDB_READ_FAILED		-9						/* 读取失败 */
#define GNCDB_NOT_OPEN			-10						/* 不能打开 */
#define GNCDB_NO_VALID			-11						/* 数据库不存在 */
#define GNCDB_CREATE_FALSE		-12						/* 数据库创建失败 */
#define GNCDB_PARAM_INVALID     -13						/* 输入参数不合法 */
#define GNCDB_TABLE_EXIST		-14						/* table存在 */
#define GNCDB_DUPLICATE_PRIMARY_KEY -15					/* 插入tuple时，主键值重复 */
#define GNCDB_PRIMARY_KEY_IMMUTABLE -16					/* 主键值不可修改 */
#define GNCDB_CAPOVERFLOW		-17
#define GNCDB_NO_REMOVE			-18						/* 不能删除 */
#define GNCDB_COLUMN_NOT_FOUND  -19						/* 列找不到 */
#define GNCDB_ARRAY_ADD_FALSE	-20						/* array插入失败 */
#define GNCDB_PRIMARYKEYINDEXMAP_CREATE_FALSE	-21		/* 主键列号map创建失败 */
#define GNCDB_PRIMARYKEYTYPEMAP_CREATE_FALSE	-22		/* 主键类型map创建失败 */
#define GNCDB_TABLESCHEMAMAP_CREATE_FALSE		-23		/* tableSchemaMap创建失败 */
#define GNCDB_MASTER_TS_CREATE_FALSE			-24		/* masterTableSchema创建失败 */
#define GNCDB_SCHEMA_TS_CREATE_FALSE			-25		/* schemaTableSchema创建失败 */
#define GNCDB_MASTERTABLE_CREATE_FALSE			-26		/* masterTable构造失败 */
#define GNCDB_SCHEMATABLE_CREATE_FALSE			-27		/* schemaTable构造失败 */
#define GNCDB_TABLEMAP_CREATE_FALSE				-28		/* tableMap构造失败 */
#define GNCDB_BTC_CREATE_FALSE					-29		/* btreeCursor构造失败 */
#define GNCDB_ARRAY_CREATE_FALSE				-30		/* vararray创建失败 */
#define GNCDB_MASTERFIELDARRAY_NOT_FOUND		-31		/* masterTuple的fieldArray找不到 */
#define GNCDB_ARRAY_GETPOINTER_FALSE			-32		/* array查找失败 */
#define GNCDB_CONDITION_CREATE_FALSE			-33		/* condition构造失败 */
#define GNCDB_SCHEMATUPLE_NOT_FOUND				-34		/* schemaTuple没有找到 */
#define GNCDB_COLUMNCONSTRAINT_CREATE_FALSE		-35		/* columnconstraint构造失败 */
#define GNCDB_COLUMN_CREATE_FALSE				-36		/* column构造失败 */
#define	GNCDB_TABLESCHEMA_CREATE_FALSE			-37		/* tableSchema构造失败 */
#define GNCDB_BTREETABLE_CREATE_FALSE			-38		/* btreeTable构造失败 */
#define GNCDB_BTREEDFS_FALSE					-39		/* DFS失败 */
#define GNCDB_LEAFTUPLE_CREATE_FALSE			-40		/* tuple构造失败 */
#define GNCDB_INTFIELD_CREATE_FALSE				-41		/* intfield构造失败 */
#define GNCDB_LEAFTUPLE_ADD_FALSE				-42		/* tuple添加field失败 */
#define GNCDB_VARCHARFIELD_CREATE_FALSE			-43		/* varcharField构造失败 */
#define GNCDB_INSERTTTUPLE_FALSE				-44		/* btreeTableInsertTuple失败 */
#define GNCDB_REALFIELD_FALSE					-45		/* realField构造失败 */
#define GNCDB_MASTERTUPLE_NOT_FOUND				-46		/* masterTuple找不到 */
#define GNCDB_FIELD_NOT_EXIST					-47		/* 属性不存在 */
#define GNCDB_MAP_CREATE_FALSE					-48		/* map创建失败 */
#define GNCDB_STATUS_NOT_FOUND					-49		/* pagestatus找不到 */
#define GNCDB_MAP_GET_FALSE						-50		/* map查找失败 */
#define GNCDB_ARRAY_GET_FALSE					-51		/* ARRAY的get失败 */
#define GNCDB_BTG_CREATE_FALSE					-52		/* btreePage构造失败 */
#define GNCDB_FREEPAGE_CREATE_FALSE				-53		/* freePage构造失败 */
#define GNCDB_OVERFLOWPAGE_CREATE_FALSE			-54		/* overflow构造失败 */
#define GNCDB_ARRAY_REMOVE_FALSE				-55		/* array删除失败 */
#define GNCDB_MAP_PUT_FALSE						-56		/* MAP的插入失败 */
#define GNCDB_MAP_REMOVE_FALSE					-57		/* MAP的删除失败 */
#define GNCDB_STATUS_CREATE_FALSE				-58		/* pageStatus构造失败 */
#define GNCDB_TOBYTE_FALSE						-59		/* 转化字节流失败 */
#define GNCDB_MAP_ITERATOR_FALSE				-60		/* map迭代器创建失败 */
#define GNCDB_MAP_NEXT_NOT_FOUND				-61		/* map的下一个找不到 */
#define GNCDB_PAGETYPE_NOT_FOUND				-62		/* pageType错误 */
#define GNCDB_TABLE_PARAM_FALSE					-63		/* 表只能读，不能写 */
#define GNCDB_DEEPCOPY_FAIL						-64		/* 深拷贝失败 */
#define GNCDB_LEAFPAGE_NOT_FOUND				-65		/* 获取叶子页失败 */
#define GNCDB_NOT_FOUND_PAGE					-66		/* 找不到指定的页 */
#define GNCDB_PRIMARYKEY_NOTNULL				-67     /* 主键值不能为空 */
#define GNCDB_WAS_CLOSED						-68		/* 数据库已经关闭 */
#define GNCDB_AIIPAGE_IS_PIN					-69		/* 所有的页均被钉住 */
#define GNCDB_LOCK_FAIL							-70		/* 申请锁失败 */
#define GNCDB_UN_JOIN							-71		/* tuple不满足条件无法join */
#define GNCDB_ROWS_OVERFLOW						-72		/* 表已经达到最大行数 */
#define GNCDB_LOG_READ_ERROR					-73     /* log日志读取失败 */
#define GNCDB_FILE_NOT_FOUND					-74     /* 数据库文件不存在 */
#define GNCDB_BLOB_EXIST                        -75     /* blob文件已存在 */
#define GNCDB_BLOB_NO_DELETE                    -76     /* tuple中存在blob无法删除 */
#define GNCDB_SYSTEMTABLE_NOTREMOVE             -77     /* 系统表不能删除 */
#define GNCDB_NOT_REFACTOR                        -78     /* master和schema禁止插入 */
#define GNCDB_TABLESCHEMA_NOT_FOUND				-79		/* tableSchema找不到 */
#define GNCDB_WRITE_FILE_FAILED                 -80     /* 写文件失败 */
#define GNCDB_OLD_PAGE_EXIST                -81     /* 页已备份 */
#define GNCDB_BLOB_NOT_EXIST                -82     /* tuple无大对象 */
#define GNCDB_WRITE_FILE_FAILED                 -80     /* 写文件失败 */
#define GNCDB_OLD_PAGE_EXIST                -81     /* 页已备份 */
/* query_processing部分 */ 
#define GNCDB_PARSE_FALSE -82                /*parse 解析失败*/
#define GNCDB_INTERNAL -83                   /*内部错误状态码*/
#define GNCDB_SQL_SYNTAX -84                 /*sql语法错误*/
#define GNCDB_UNIMPLENMENT -85               /*暂未实现*/
#define GNCDB_SCHEMA_NUM_MISMATCH -86        /*表schema数量不匹配*/
#define GNCDB_SCHEMA_FIELD_TYPE_MISMATCH -87 /*表schema类型不匹配*/
#define GNCDB_SCHEMA_FIELD_MISSING -88       /*无效字段名*/
#define GNCDB_NEXT_EOF -89                   /*next结束*/
#define GNCDB_INSERT_FAILED -90              /*插入失败*/
#define GNCDB_TUPLE_NOT_FOUND -91            /*tuple未找到*/
#define GNCDB_EXPR_EVAL_FAILED -92           /*表达式求值失败*/
#define GNCDB_JOIN_KEY_NOT_FOUND -93         /*join key未找到*/
#define GNCDB_DATE_TYPE_INVALID -94          /*日期类型无效*/
#define GNCDB_ORDER_BY_INVALID -95           /*order by无效*/
#define GNCDB_DATETIME_TYPE_INVALID -96      /*datetime类型无效*/
#define GNCDB_FIELD_NOT_ALLOW_NULL -97               /*字段不允许为空*/
#define GNCDB_TEXT_LENGTH_EXCEED -98                /*文本长度超出限制*/
#define GNCDB_ROW_DONE  -99                         /*row结束*/
#define GNCDB_GET_TABLE_ROWNUM_FAILED -100           /*获取表行数失败*/
#define GNCDB_VARARRAYLIST_NULL -101                 /*varArrayList为空*/
#define GNCDB_TYPE_CAST_INVALID -102              /*类型转换无效*/
#define GNCDB_PREDICATE_PUSHDOWN_FAILED -103      /*谓词下推失败*/
#define GNCDB_SORT_MERGE_NO_CONDITION -104   /*sort merge join没有连接条件*/
#define GNCDB_CONDITION_INVALID -105        /*条件无效*/
#define GNCDB_SQLFILE_INVALID -106          /*sql文件无效*/
#define GNCDB_JOINLIST_NULL -107            /*joinList为空*/
#define GNCDB_PARENTPAGEID_NOT_EXIST -108

// static const int CHECK_MINSIZE = LOGGER_MIN_SIZE * MAX_LOGGER;
// static const char TXN_BEGIN = 0;
// static const char TXN_COMMIT = 1;
// static const char TXN_ABORT = 2;
// static const char LOG_UPDATE = 3;
// static const char CHECK = 4;
// static const int TYPE_SIZE = 1;
// static const int ID_SIZE = 4;
// static const int PAGEID_SIZE = 4;
// static const int OFFSET_SIZE = 4;
// static const int LSN_SIZE = 4;
// static const int BEGIN_SIZE = 21;
// static const int COMMIT_SIZE = 21;
// static const int ABORT_SIZE = 21;
// static const int UPDATE_SIZE = 1049;
// static const int CHECK_SIZE = 10;
// static const int INT_SIZE = sizeof(int);
// static const int DOUBLE_SIZE = sizeof(double);
// static const int MAX_CACHED_NUM = 500;
// static const int INIT_MAX_PAGE = 1000000;
// static const int LRU_K = 20;
static const int DATE_SIZE = sizeof(int);
static const int SYS_FIELD_NUM = 3;
static const int MAX_TEXT_LENGTH = 65535;
static const int FLOAT_SIZE = sizeof(float);
static const int DATETIME_SIZE = 19;
static const int CHECK_MINSIZE = LOGGER_MIN_SIZE * MAX_LOGGER;
static const char TXN_BEGIN = 0;
static const char TXN_COMMIT = 1;
static const char TXN_ABORT = 2;
static const char LOG_UPDATE = 3;
static const char CHECK = 4;
// static const int TYPE_SIZE = 1;
static const int ID_SIZE = 4;
static const int PAGEID_SIZE = 4;
static const int OFFSET_SIZE = 4;
static const int LSN_SIZE = 4;
// static const int INT_SIZE = sizeof(int);
// static const int DOUBLE_SIZE = sizeof(double);
static const int MAX_CACHED_NUM = 200;
static const int INIT_MAX_PAGE = 1000000;
static const int LRU_K = 20;
static const int BEGIN_SIZE = 5 * INT_SIZE + TYPE_SIZE;  // 21
static const int COMMIT_SIZE = 5 * INT_SIZE + TYPE_SIZE; // 21
static const int ABORT_SIZE = 5 * INT_SIZE + TYPE_SIZE;  // 21
static const int UPDATE_SIZE = PAGE_SIZE + 6 * INT_SIZE + TYPE_SIZE; // 1024 + 24 + 1 = 1049
static const int CHECK_SIZE = 2 * INT_SIZE + 2 * TYPE_SIZE; // 10
#endif  
