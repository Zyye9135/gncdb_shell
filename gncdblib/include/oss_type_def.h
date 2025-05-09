#ifndef _OSS_TYPE_DEF_H_
#define _OSS_TYPE_DEF_H_

#define M_C_TRUE    1
#define M_C_FALSE   0

#ifndef _WIN32
//#define _WIN32
#endif

typedef char               DT_SCHAR8;
typedef unsigned char	   DT_UCHAR8;
typedef short              DT_SINT16;
typedef unsigned short     DT_UINT16;
typedef int                DT_SINT32;
typedef unsigned int       DT_UINT32;
typedef unsigned long long DT_UINT64;
typedef long long          DT_SINT64;
typedef float              DT_FLOAT32;
typedef double             DT_FLOAT64;
typedef unsigned int       DT_BOOL;

#define DT_VOID  void

#define M_C_PI    (3.141592653589793)
#define M_C_GLB_R (6.378245e6)
#define M_C_GLB_E (3.352891869237e-3)
#define M_C_DEG_TO_RAD (1.74532925e-2)    /* �Ƕ�ת���� */
#define M_C_RAD_TO_DEG (57.2957795131)    /* ����ת�Ƕ� */

#endif